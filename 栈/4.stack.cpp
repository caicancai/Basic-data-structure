# include<stdio.h>
# include<stdlib.h>
# include<time.h>

typedef struct Stack{
	int *data;
	int size,top;
}Stack;

Stack *init(int n){
	Stack *s=(Stack *)malloc(sizeof(Stack));
	s->data=(int *)malloc(sizeof(int) *n);
	s->size=n;
	s->top=-1;
	return s;
}

int empty(Stack *s){
	return s->top==-1;
}

int top(Stack *s){
	return s->data[s->top];
}

void clear(Stack *s){
	if(s==NULL) return ;
	free(s->data);
	free(s);
	return ;
}

int expand(Stack *s){
	int extr_size=s->size;
	int *p;
	while(extr_size){
		p=(int *)realloc(s->data,sizeof(int)*(s->size+extr_size));
		if(p!=NULL) break;
		extr_size >>=1;
	}
	if(p==NULL) return 0;
	s->data=p;
	s->size+=extr_size;
	return 1;
}

int push(Stack *s,int val){
	if(s==NULL) return 0;
	if(s->top==s->size-1){
		if(!expand(s)){
			printf("fail to expand\n");
			return 0;
		}
		printf("success\n");
	}
	s->data[++(s->top)]=val;
	return 1;
}

int pop(Stack *s){
	if(s==NULL) return 0;
	if(empty(s)) return 0;
	s->top-=1;
	return 1;
}

void output(Stack *s){
	if(s==NULL) return ;
	printf("Stack(%d):[",s->size);
	for(int i=s->top; i>=0; i--){
		printf("%d",s->data[i]);
		i && printf(" ");
	}
	printf("]\n");
	return ;
}
int main(){
	srand(time(0));
	#define MAX_OP 20
	Stack *s=init(1);
	for(int i=0; i<MAX_OP; i++){
		int val=rand()%100;
		int op=rand()%4;
		switch(op){
			case 0:
			case 1:
			case 2:{
				printf("push %d to the Stack=%d\n",val,push(s,val));
			}break;
			case 3:{
				if(!empty(s)){
					printf("pop %d from the Stack=",top(s));
					printf("%d\n",pop(s));
				}break;
			}
		}
		output(s),printf("\n");
	}
	#undef MAX_OP
	clear(s);
	return 0;
}
