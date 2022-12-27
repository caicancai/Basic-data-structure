# include<stdio.h>
# include<stdlib.h>
#include<time.h>

#define COLOR(a,b) "\033[" #b "m" a "0\033[0m"


#define GREEN(a) COLOR(a,32)
#define RED(a) COLOR(a,31)

typedef int Type;//定义一个别名 

typedef struct Vector{
	Type *data;
	int size,length;
}Vec;

Vec *init(int n){
	Vec *v=(Vec *)malloc(sizeof(Vec)); 
	 
	v->data=(Type *)malloc(sizeof(Type)*n);
	v->size=n;
	v->length=0;
	return v; 
}

void clear(Vec *v){
	if(v==NULL) return ;
	free(v->data);
	free(v);
	return ;
}
 
int expand(Vec *v){
	int extr_size = v->size;
	Type *p;
	while(extr_size){
		p=(Type *)realloc(v->data,sizeof(Type)*(v->size+extr_size));
		if(p!=NULL) break;
		extr_size >>= 1;	
	} 
	if(p==NULL){
		printf(RED("(fail to expand!\n)"));
	}
	v->size +=extr_size;
	v->data=p;
	printf(GREEN("success to expand the new size=%d\n"),v->size);
	return 1;
}

int insert(Vec *v,int ind,Type val){
	if(v==NULL) return 0;
	if(ind < 0 || ind > v->length) return 0;
	if(v->length==v->size){
		if(!expand(v)) return 0;
	} 
	for(int i=v->length; i>ind; i--){
		v->data[i]=v->data[i-1];
	}
	v->data[ind]=val;
	v->length+=1;
	return 1;
} 

int erase(Vec *v,int ind){
	if(v==NULL) return 0;
	if(ind < 0 || ind>=v->length ) return 0;
	for(int i=ind+1; i<v->length; i++){
		v->data[i-1]=v->data[i];
	}
	v->length-=1;
	return 1;
}

void output(Vec *v){
	if(v==NULL) return ;
	printf("Vector(%d) : [",v->length);
	for(int i=0; i<v->length; i++){
		i && printf(", ");
		printf("%d",v->data[i]);
	}
	printf("]\n");
	return ;
}

int main(){
	#define MAX_N 20
	Vec *v=init(MAX_N+5);
	srand(time(0));
	for(int i=0; i<MAX_N; i++){
		int op=rand()%4;
		int ind=rand()% (v->length+3);
		int val=rand()%100;
		switch(op){
			case 1:
			case 2:
			case 0:{
				printf("insert %d at %d to Vector=%d\n",val,ind,insert(v,ind,val));
			}break;
			case 3:{
				printf("erase a iterm at %d from Vector=%d\n",ind,erase(v,ind));
			}break;
		}
		output((v)),printf("\n"); 
		
	}
	#undef MAX_N
	clear(v);
	
	return 0;
} 
