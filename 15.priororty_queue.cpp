# include<stdio.h>
# include<stdlib.h>
# include<time.h>

#define swap(a,b){\
	typeof(a)__temp=a;\
	a=b;b=__temp;\
}

typedef struct prioroty_queue{
	int *data;
	int cnt,size;//cnt：元素个数，size：堆的容量 
}prioroty_queue;

prioroty_queue *init(int n){
	prioroty_queue *q=(prioroty_queue *)malloc(sizeof(prioroty_queue));
	q->data=(int *)malloc(sizeof(int)*(n+1));
	q->size=n;
	q->cnt=0;
	return q;
}

int top(prioroty_queue *q){
	return q->data[1];
}

int empty(prioroty_queue *q){
	return q->cnt==0;
}

int push(prioroty_queue *q,int val){
	if(q==NULL) return 0;
	if(q->cnt==q->size) return 0;
	q->data[++(q->cnt)]=val;
	int ind=q->cnt;
	while(ind>>1 && q->data[ind]>q->data[ind>>1]){
		swap(q->data[ind],q->data[ind>>1]);
		ind>>=1;
	}
	return 1;
}

int pop(prioroty_queue *q){
	if(q==NULL) return 0;
	if(empty(q)) return 0; 
	q->data[1]=q->data[q->cnt--];
	int ind=1;
	while((ind<<1)>=q->cnt){
		int temp=ind,l=ind<<1,r=ind<<1 | 1;
		if(q->data[l]>q->data[temp]) temp=l;
		if(r<=q->cnt && q->data[r]>q->data[temp]) temp=r;
		if(ind==temp) break;
		swap(q->data[ind],q->data[temp]);
		ind=temp;
	}
	return 1;
}

void clear(prioroty_queue *q){
	if(q==NULL) return ;
	free(q->data);
	free(q);
	return ;
}

int main(){
	srand(time(0));
	#define MAX_OP 20
	prioroty_queue *q=init(MAX_OP);
	for(int i=0; i<MAX_OP; i++){
		int val=rand()%100;
		push(q,val);
		printf("insert %d to the priority_queue!\n",val);
	}
	for(int i=0; i<MAX_OP; i++){
		printf("%d ",top(q));
		pop(q);
	}
	printf("\n");
	#undef MAX_OP
	clear(q);
	return 0;
}
