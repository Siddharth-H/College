#include<stdio.h>
#include<math.h>
void customSort(int[],int[],int,int);
void swap(int,int,int[],int[]);
void merging(int[],int[],int,int,int);
int len=0;
int main(){
	printf("enter the size of array:: ");
	scanf("%d",&len);
	
	int n2[len];
	int w2[len];
	int num[len];
	int weight[len];
	printf("Enter the Inputs with their weight::\n");
	int i=0;
	for(i;i<len;i++){
		printf("\nnum[%d]--> ",i);
		scanf("%d",&num[i]);
		printf("\tweight of %d --> ",num[i]);
		scanf("%d",&weight[i]);		
	}
	for(i=0;i<len;i++){
		printf("num[%d]-->%d, w-->%d\n",i,num[i],weight[i]);
	}
	customSort(num,weight,0,len);
	printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n\n");
	printf("After customSort::\n");
	for(i=0;i<len;i++){
		printf("num[%d]-->%d, w-->%d\n",i,num[i],weight[i]);
	}
}
void customSort(int num[],int w[],int start,int end){
	int mid;
	if(start<end){
	mid = (start+end)/2;
	customSort(num,w,start,mid);
	customSort(num,w,mid+1,end);
	merging(num,w,start,mid,end);		
		
	}
	
}
void merging(int num[],int w[],int low, int mid, int high) {
   int l1, l2, i;
	int n2[len];
	int w2[len];
   for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
      if(w[l1] >= w[l2]){
         if(w[l1]==w[l2]){
         	if(num[l1]>num[l2]){
         		
				 break;
			 }
		 }
		 n2[i] = num[l1++];
         w2[i] = w[l1++];
	  }
      else{
         n2[i] = num[l2++];
         w2[i] = w[l2++];
	  }
   }
   
   while(l1 <= mid){
      n2[i++] = num[l1++];
      w2[i++] = w[l1++];
   }    

   while(l2 <= high){
      n2[i++] = num[l2++];
      w2[i++] = w[l2++];
   }   

   for(i = low; i <= high; i++){
      num[i] = n2[i];
      w[i] = w2[i];
   }
}

/*void sort(int low, int high) {
   int mid;
   
   if(low < high) {
      mid = (low + high) / 2;
      sort(low, mid);
      sort(mid+1, high);
      merging(num,w,low, mid, high);
   } else { 
      return;
   }   
}*/

void swap(int i, int j,int n[],int w[])
{
	int x;
	x = w[i];
	w[i]=w[j];
	w[j] = x;
	
	x = n[i];
	n[i]=n[j];
	n[j] = x;
}
