# include<iostream>
# include<stdlib.h>
# include<string.h>
typedef struct Node{
	char *str;//值域 
	struct Node *next;//指针域 
}Node;

typedef struct HashTable{
	//拉链表哈希法 
	Node **data;
	int size;
}HashTable;


Node *init_node(char *str,Node *head){//初始化链表节点 
	Node *p=(Node *)malloc(sizeof(Node));
	p->str=strdup(str);//strdup：开辟了一块空间，将字符串复制过去 
	p->next=head;
	return p;
}
HashTable *init_hash(int n){
	HashTable *h=(HashTable *)malloc(sizeof(HashTable));
	h->size=(n<<1);
	h->data=(Node **)calloc(h->size,sizeof(Node *));
	return h;
}

int BKDRHash(char *str){
	int seed=31,hash=0;
	for(int i=0; str[i]; i++) hash=hash*seed+str[i];
	return hash & 0x7fffffff;
}

int insert(HashTable *h,char *str){
	if(h==NULL) return 0;
	int hash=BKDRHash(str);
	int ind=hash % h->size;
	h->data[ind]=init_node(str,h->data[ind]);
	return 1;
}

int search(HashTable *h,char *str){
	if(h==NULL) return 0;
	int hash=BKDRHash(str);
	int ind=hash%h->size;
	Node *p=h->data[ind];
	while(p && strcmp(p->str,str)) p=p->next;
	return p!=NULL;
}

void clear_node(Node *node){
	if(node==NULL) return ;
	Node *p=node,*q;
	while(p){
		q=q->next;
		free(p->str);
		free(p);
		p=q;
	}
	return ;
}
void clear(HashTable *h){
	if(h==NULL) return ;
	for(int i=0; i<h->size; i++){
		clear_node(h->data[i]);
	}
	free(h);
	return ;
}
int main(){
	int op;
	#define MAX_N 100
	char str[MAX_N+5]={0};
	HashTable *h=init_hash(MAX_N);
	while(~scanf("%d%s",&op,str)){
		switch(op){
			case 0:
				printf("insert %s to HashTable\n",str);
				insert(h,str);
				break;
			case 1:
				printf("search %s from HashTable result=%d\n",str,search(h,str));
				break;
		}
	}
	#undef MAX_N
	clear(h);
	return 0;
}
