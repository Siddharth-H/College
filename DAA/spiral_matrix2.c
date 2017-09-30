#include<stdio.h>
#include<math.h>
#include<time.h>
# define order 2000
int len;
int mid_i;
int mid_j;
void arrange(int,int);
void goDown(int ,int);
void goLeft(int ,int);
void goRight(int ,int);
void goUp(int ,int);
int a[order][order];
int run_again=1;
int main(){
	int i,j;
	//printf("Enter the order of matrix:: ");
	//scanf("%d",&len);
	len = order;
	int num =1;
	//printf("Enter the Inputs:: ");
	
	for(i=0;i<len;i++){
		for(j=0;j<len;j++){
			a[i][j] = num;
			num++;
		}
	}
/*	for(i=0;i<len;i++){
		for(j=0;j<len;j++){
			printf("%d\t",a[i][j]);
		}
		printf("\n");
	}
		printf("\n");
*/	clock_t begin = clock();
	mid_i = len/2;
	if(len%2==0){
		mid_j=len/2-1;
	}
	else{
		mid_j=len/2;
	}
	i=0;
	j=0;
	//printf("mid i =%d, mid j =%d\n",mid_i,mid_j);
	arrange(i,j);
	clock_t end = clock();
		printf("\nExecution Time  = %lf\n",(double)(end-begin)/CLOCKS_PER_SEC);

}
void arrange(int i,int j){
	if(run_again){
		if(i==mid_j && j==mid_j)
		{	
			run_again =0;
//			printf("STOP\n");
		}
			
		goRight(i,j);
		arrange(i+1,j+1);
			
		
	}
}
void goRight(int i,int j){
	int n = len-1-j;
	for(j;j<=n;j++){
//		printf("i-%d j-%d => %d-R \n",i,j,a[i][j]);
		printf("%d ",a[i][j]);
	}
	j--;
	goDown(i+1,j);
}
void goDown(int i,int j){
	int m = len-1-i;
	while(i<=j){
//		printf("i-%d j-%d => %d-D \n",i,j,a[i][j]);
		printf("%d ",a[i][j]);
		i++;
	}
	goLeft(i-1,j-1);
}
void goLeft(int i,int j){
	int h = len-1-j-1;
//	printf("--h= %d--\n",h);
	for(j;j>=h;j--){
//		printf("i-%d j-%d => %d-L \n",i,j,a[i][j]);
		printf("%d ",a[i][j]);
	}
//	printf("Go Up\n");
	goUp(i-1,h);
}
void goUp(int i,int j){
	int h = len-1-i;
	
	for(i;i>=h;i--){
//		printf("i-%d j-%d => %d-U \n",i,j,a[i][j]);
		printf("%d ",a[i][j]);
	}

}
