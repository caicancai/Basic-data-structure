# include<stdio.h>

#define P(func){\
	printf("%s : %d",#func,func);\
}
int binary_search(int *arr,int n,int x){
	int head=0,tail=n-1,mid;
	while(head<=tail){
		mid=(head+tail)>>1;
		if(arr[mid]==x) return mid;
		if(arr[mid]<x) head=mid+1;
		else tail=mid-1;
	}
	return -1;
}

//1111110000
int binary_search1(int *arr,int n){
	int head=-1,tail=n-1,mid;
	while(head<tail){
		mid=(head+tail+1)>>1;
		if(arr[mid]==1) head=mid;
		else tail=mid-1;
		printf("%d %d\n",head,tail);
	}
	return head;
}

//00000001111
int binary_search2(int *arr,int n){
	int head=-1,tail=n-1,mid;
	while(head<tail){
		mid=(head+tail+1)>>1;
		if(arr[mid]==1) head=mid;
		else tail=mid-1;
		printf("%d %d\n",head,tail);
	}
	return head;
}

int main(){
	int arr1[10]={1,3,5,7,9,11,13,17,19,21};
	int arr2[10]={1,1,1,1,0,0,0,0,0,0};
	P(binary_search(arr1,10,7));
	P(binary_search1(arr2,10));
	return 0;
} 
