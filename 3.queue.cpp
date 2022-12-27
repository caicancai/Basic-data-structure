# include<stdio.h>
# include<stdlib.h>
# include<time.h>

typedef struct Queue{
	int *data;
	int head,tail;
	int length,count;
}Queue;

Queue *init(int n){
	Queue *q=(Queue *)malloc(sizeof(Queue));
	q->data=(int *)malloc(sizeof(int) *n);
	q->head=0;
	q->tail=0;
	q->count=0;
	q->length=n;
	return q;
}

int empty(Queue *q){
	return q->count==0;
}

int front(Queue *q){
	return q->data[q->head];
}

int push(Queue *q,int val){
	if(q==NULL) return 0;
	if(q->count == q->length) return 0;
	q->data[q->tail++]=val;
	if(q->tail == q->length) q->tail=0;
	q->count +=1;
	return 1;
}

int pop(Queue *q){
	if(q == NULL) return 0;
	if(empty(q)) return 0;
	q->head +=1;
	if(q->head==q->length) q->head=0;
	q->count-=1;
	return 1;
}

void clear(Queue *q){
	if(q==NULL) return ;
	free(q->data);
	free(q);
	return ;
}

void output(Queue *q){
	if(q==NULL) return ;
	printf("Queue(%d %d): ",q->length,q->count);
	for(int i=q->head, j=0; j<q->count; j++){
		j && printf(" ");
		printf("%d",q->data[(i+j)%q->length]);
	}
	printf("\n");
	return ;
}
int main(){
	srand(time(0));
	#define MAX_OP 20
	Queue *q=init(10);
	for(int i=0; i<MAX_OP; i++){
		int op=rand()%4;
		int val=rand()%100;
		switch(op){
			case 0:
			case 1:
			case 2:{
				printf("push %d to the Queue=%d\n",val,push(q,val));
			}break;
			case 3:{
				if(!empty(q)){
					printf("pop %d from the Queue= \n",front(q));
					printf("%d\n",pop(q));
				}
			}break;
		}
		output(q),printf("\n");
	}
	#undef MAX_OP
	clear(q);
	return 0;
} 
