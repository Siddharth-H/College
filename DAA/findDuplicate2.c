#include<stdio.h>
#include<time.h>
#define true 1
#define false 0
int compare(int,int);
int main(){
	printf("Enter the Size: ");
	int n=0;
	scanf("%d",&n);
	int i = 0,j,k=0;
	int a[n];
	for(i;i<n;i++){
		scanf("%d",&a[i]);
		//a[n-i]=j;
	}
	clock_t begin = clock();
	i=0,j=1;
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			k=compare(a[i],a[j]);
			if(k==false){
				continue;
			}
			
			k=1;
			break;
			 
		}
		if(k==1){
			break;
		}
	}
	clock_t end = clock();
	printf("\nExecution Time  = %lf\n",(double)(end-begin)/CLOCKS_PER_SEC);
		printf("a[%d]-->%d\n",i,a[i]);
		printf("a[%d]-->%d\n",j,a[j]);
}
int compare(int i,int j){
	if(i==j){
		return true;
	
	}
	return false;
}
