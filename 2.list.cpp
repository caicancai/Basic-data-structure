# include<stdio.h>
# include<stdlib.h>
# include<time.h>
typedef struct ListNode{
	int data;//数据域 
	struct ListNode *next;//指针域 
}ListNode;

typedef struct List{
	ListNode head;//虚拟头节点 
	int length;
}List;

ListNode *getNewNode(int);//初始化节点 
List *getLinkList();//初始化链表 
void clear_node(ListNode*);//销毁节点 
void clear(List*);//整个销毁 
int insert(List*,int, int);
int erase(List*,int);
void output(List*);
void clear_node(ListNode*);

int main(){
	srand(time(0));
	#define MAX_OP 20
	List *l = getLinkList();
	for(int i=0; i<MAX_OP; i++){
		int val=rand()%100;
		int ind=rand()% (l->length+3)-1;
		int op=rand()%2;
		switch(op){
			case 0:
			case 1:{
				printf("insert %d at %d to list=%d\n",val,ind,val);
			}break;
			case 2:{
				printf("erase a itern at %d from List =%d\n",ind,erase(l,ind));
			}break;
			case 3:{
				printf("reverse\n");
			}
		}
		output(l),printf("\n");
	}
	#undef MAX_OP
	clear(l);
	return 0;
}

ListNode *getNewNode(int val){
	ListNode *p=(ListNode*)malloc(sizeof(ListNode));
	p->data=val;
	p->next=NULL;
	return p;
}

List *getLinkList(){
	List*l=(List*)malloc(sizeof(List));
	l->head.next=NULL;
	l->length=0;
	return l;
}


int insert(List *l,int ind,int val){
	if(l==NULL) return 0;
	if(ind < 0 || ind>l->length) return 0;
	ListNode *p=&(l->head),*node = getNewNode(val);
	while(ind--) p=p->next;
	node->next = p->next;
	p->next =node;
	l->length +=1;
	return 1;
}

int erase(List *l,int ind){
	if( l== NULL) return 0;
	if(ind < 0 || ind >=l->length) return 0;
	ListNode *p=&(l->head), *q;
	while(ind--) p=p->next;
	q=p->next;
	p->next=q->next;
	free(p);
	l->length -=1;
	return 1;
}

void reverse(List *l){
	if( l == NULL) return ;
	ListNode *p=l->head.next, *q;
	l->head.next=NULL;
	while(p != NULL){
		q=p->next;
		p->next=l->head.next;
		l->head.next = p;	
		p=q;
	}
	return ;	
}

void output(List *l){
	if(l == NULL) return ;
	printf("list(%d) :", l->length);
	for(ListNode *p=l->head.next; p!=NULL; p=p->next){
		printf("%d->",p->data);
	}
	printf("NULL\n");
	return ;
}

void clear(List *l){
	if(l==NULL) return ;
	ListNode *p=l->head.next,*q;
	while(p!=NULL){
		q=p->next;
		free(p);
		p=q;
	}
	free(l);
	return;
}
