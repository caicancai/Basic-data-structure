# include<stdio.h>
# include<time.h>
# include<stdlib.h>
# include<string.h>

#define swap(a,b){\
	__typeof(a)__temp=a;\
	a=b; b=__temp;\
}


#define TEST(arr,n,func,args...){\
	int *num=(int *)malloc(sizeof(int)*n);\
	memcpy(num,arr,sizeof(int)*n);\
	output(num,n);\
	printf("%s=",#func);\
	func(args);\
	output(num,n);\
	free(num);\
	printf("\n");\
}


void select_sort(int *num,int n){
	for(int i=0; i<n-1; i++){
		int ind=i;
		for(int j=i+1; j<n; j++){
			if(num[ind]>num[j]) ind=j;
		}
		swap(num[ind],num[i]);
	}
	return ;
}

void quick_sort(int *num,int l,int r){
	if(l>r) return ;
	int x=l,y=r,z=num[l];
	while(x<y){
		while(x<y && num[y]>z) y--;
		if(x<y) num[x++]=num[y];
		while(x<y && num[x]<z) x++;
		if(x<y) num[y--]=num[x];
	}
	num[x]=z;
	quick_sort(num,l,x-1);
	quick_sort(num,x+1,r);
	return ;
}

void randint(int *arr,int n){
	while(n--) arr[n]=rand()%100;
	return ;
}

void output(int *arr,int n){
	for(int i=0; i<n; i++){
		i&&printf(" ");
		printf("%d",arr[i]);
	}
	printf("\n");
	return ;
}

int main(){
	srand(time(0));
	#define MAX_N 20
	int arr[MAX_N];
	randint(arr,MAX_N);
	TEST(arr,MAX_N,select_sort,num,MAX_N);
	TEST(arr,MAX_N,quick_sort,num,0,MAX_N-1);
	#undef MAX_N
	return 0;
}
