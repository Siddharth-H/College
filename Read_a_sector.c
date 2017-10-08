#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <stdio.h>
#include <winioctl.h>
 
#define READ_CYL_TRK_SEK 1001
#define READ_BYTES 1002
#define FINDINDEXOFFILE 1003
#define QUIT 1004
 
int ReadSectorsFromDisk(int disk, DISK_GEOMETRY dg, DWORD dMode, HANDLE hDrive);
 
BOOL gQuit = false;
 
int main(){
    DWORD dMode;
    int disk;
    char dname;
    DISK_GEOMETRY dg;
    DWORD dJunk;
     
    while(!gQuit){
        printf("What would you like to do?\n");
        printf("1. Read from disk by index of cylinder/track/sector.\n");
        printf("2. Read from disk by index of first byte of file.\n");
        printf("3. Find first-byte index of file.\n");
        printf("4. Quit.\n");
         
        scanf("%d", &dMode);
        dMode += 1000;
        if(dMode == QUIT) break;
        printf("\nPhysical disk number: ");
        scanf("%d", &disk);
        fflush(stdin);
        printf("\tDrive letter: ");
        scanf("%c", &dname);
        char physdisk[24];
        wsprintf(physdisk, "\\\\.\\PhysicalDrive%d", disk);
        HANDLE hDrive = CreateFile(physdisk, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
        if (!DeviceIoControl(hDrive, IOCTL_DISK_GET_DRIVE_GEOMETRY, NULL, 0, &dg, sizeof(dg), &dJunk, (LPOVERLAPPED)NULL)){
           MessageBox(NULL, "deviceiocontrol failed", NULL, MB_OK);
        }
        CloseHandle(hDrive);
        ZeroMemory(physdisk, 24);
        wsprintf(physdisk, "\\\\.\\%c:", dname);
        hDrive = CreateFile(physdisk, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
        ReadSectorsFromDisk(disk, dg, dMode, hDrive);
        printf("\n\n\n");
    }
    return 0;
}
 
int ReadSectorsFromDisk(int disk, DISK_GEOMETRY dg, DWORD dMode, HANDLE hDrive){
    DWORD dCylinders, dTracksPerCylinder, dSectorsPerTrack, dBytesPerSector;
    DWORD dCylinder, dTrack, dSector;
    DWORD dNoOfSectors = 1;
    DWORD dReadOffset = 0;
    DWORD dJunk;
    BOOL quit = false;
    char *sData;
    dCylinders = dg.Cylinders.QuadPart;
    dTracksPerCylinder = dg.TracksPerCylinder;
    dSectorsPerTrack = dg.SectorsPerTrack;
    dBytesPerSector = dg.BytesPerSector;
    DWORD dNumberOfBytesToRead = dBytesPerSector;
     
    while(!quit){
        printf("\n\n\n");
        printf("Volume Information:\n");
        printf("Cylinders: %d\nTracks Per Cylinder: %d\nBytes Per Sector: %d\n\n", dCylinders, dTracksPerCylinder, dBytesPerSector);
        if(dMode == FINDINDEXOFFILE){
            dNumberOfBytesToRead = 0;
            char sFile[1024];
            ZeroMemory(sFile, 1024);
            fflush(stdin);
            printf("\nEnter full path of file: ");
            fgets(sFile, 1024, stdin);
            sFile[strlen(sFile)-1] = '\0';
            HANDLE hFile = CreateFile(sFile, FILE_READ_ATTRIBUTES, (FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE), NULL, OPEN_EXISTING, 0, 0);
            DWORD bytesPerSector, sectorsPerCluster;
            char szDrive[10];
            ZeroMemory(szDrive, 10);
            wsprintf(szDrive, "%c:", *sFile);
            GetDiskFreeSpace(szDrive, &sectorsPerCluster, &bytesPerSector, NULL, NULL);
            DWORD dClusterSize = (bytesPerSector * sectorsPerCluster);
            DWORD dLCN;
            DWORD dIndexOfFile;
            if(hFile){
                PRETRIEVAL_POINTERS_BUFFER rpt = (PRETRIEVAL_POINTERS_BUFFER) new BYTE[sizeof(RETRIEVAL_POINTERS_BUFFER)];
                STARTING_VCN_INPUT_BUFFER svib = {0};
                if(DeviceIoControl(hFile, FSCTL_GET_RETRIEVAL_POINTERS, &svib, sizeof(svib), rpt, 2048, &dJunk, NULL)){
                    dLCN = rpt->Extents[0].Lcn.LowPart;
                    dIndexOfFile = dLCN * dClusterSize;
                    printf("Index of file: %d\n", dIndexOfFile);
                }else{
                    printf("error = %d", GetLastError());
                    MessageBox(NULL, "DeviceIoControl failed!", NULL, MB_OK);
                }
            }else{
                MessageBox(NULL, "hFile == NULL", NULL, MB_OK);
            }
        }else if(dMode == READ_CYL_TRK_SEK){
            printf("Cylinder: ");
            scanf("%d", &dCylinder);
            printf("Track: ");
            scanf("%d", &dTrack);
            printf("Sector: ");
            scanf("%d", &dSector);
            printf("Number of Sectors to Read: ");
            scanf("%d", &dNoOfSectors);
            dNumberOfBytesToRead *= dNoOfSectors;
            dReadOffset = ((dCylinder * dTracksPerCylinder + dTrack) * dSectorsPerTrack + dSector) * dBytesPerSector;
        }else if(dMode == READ_BYTES){
            printf("Enter starting byte: ");
            scanf("%d", &dReadOffset);
            printf("Enter number of bytes to read: ");
            scanf("%d", &dNumberOfBytesToRead);
        }
        if(dMode != FINDINDEXOFFILE){
            printf("\ndReadOffset = %d\n", dReadOffset);
            LARGE_INTEGER liOffset = {dReadOffset};
            sData = (char*) malloc(dNumberOfBytesToRead);
            if(dReadOffset != 0){
                if(!SetFilePointer(hDrive, (liOffset.LowPart), &liOffset.HighPart, FILE_BEGIN)){
                    MessageBox(NULL, "SetFilePointer failed", NULL, MB_OK);
                    printf("%d", GetLastError());
                }
            }
             
            if(!ReadFile(hDrive, sData, dNumberOfBytesToRead, &dJunk, NULL)){
                MessageBox(NULL, "readfile failed!", NULL, MB_OK);
                printf("error = %d", GetLastError());
                return 0;
            }
        }
 
        BOOL slQuit = false;
        while(!slQuit){
            printf("\n\n\n");
            printf("Finished selected task.\n\n");
            printf("What would you like to do now?\n");
            printf("1. Record result to file.\n");
            printf("2. Display result.\n");
            printf("3. Begin a new operation in the same mode.\n");
            printf("4. Return to main menu.\n");
            DWORD dFunc;
            scanf("%d", &dFunc);
            if(dFunc == 1){
                char sDest[1024];
                fflush(stdin);
                printf("Enter full path of file to write to (if exists will overwrite): ");
                fgets(sDest, 1024, stdin);
                sDest[strlen(sDest)-1] = '\0';
                HANDLE hDest = CreateFile(sDest, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, 0);
                if(hDest){
                    if(!WriteFile(hDest, sData, dNumberOfBytesToRead, &dJunk, NULL)){
                        MessageBox(NULL, "WriteFile failed!", NULL, MB_OK);
                        printf("error: %d\n", GetLastError());
                        return 0;
                    }
                }else{
                    MessageBox(NULL, "hDest == NULL", NULL, MB_OK);
                }
                CloseHandle(hDest);
            }else if(dFunc == 3){
                slQuit = true;
            }else if(dFunc == 2){
                for(int i=0; i<=dNumberOfBytesToRead; i++){
                    printf("%c", sData[i]);
                }
            }
            else{
                slQuit = true;
                quit = true;
                break;
            }
        }
    }
    CloseHandle(hDrive);
    return 0;
}
