# include<stdio.h>
# include<stdlib.h>

#define swap(a,b){\
	__typeof(a)__temp=a;\
	a=b; b=__temp;\
}

typedef struct Node{
	char ch;
	double p;
	struct Node *lchild,*rchild;	
}Node;

Node *getNewNode(char ch,double per){
	Node *p=(Node *)malloc(sizeof(Node));
	p->ch=ch;
	p->p=per;
	p->lchild=p->rchild=NULL;
	return p;
}

Node *CombinNode(Node *a,Node *b){
	Node *p=getNewNode(0,a->p + b->p);
	p->lchild=a;
	p->rchild=b;
	return p;
}

void pick_min(Node **arr,int n){
	for(int j=n-1; j>=0; j--){
		if(arr[n]->p > arr[j]->p){
			swap(arr[n],arr[j]);
		}
	}
	return ;
}
Node *getHaffmanTree(Node **arr,int n){
	for(int i=1; i<n; i++){
		pick_min(arr,n-i);
		pick_min(arr,n-i-1);
		arr[n-i]=CombinNode(arr[n-i],arr[n-i-1]);
	}
	return arr[0];
}

void __output_encode(Node *root,char *str,int k){
	str[k]=0;
	if(root->lchild==NULL && root->rchild==NULL){
		printf("%c %s\n",root->ch,str);
		return ;
	}
	str[k]='0';
	__output_encode(root->lchild,str,k+1);
	str[k]='1';
	__output_encode(root->rchild,str,k+1);
	return ;
}

void output_encode(Node *root){
	char str[100];
	__output_encode(root,str,0);
	return ;
}
void clear(Node *root){
	if(root==NULL) return ;
	clear(root->lchild);
	clear(root->rchild);
	free(root);
	return ;
}
int main(){
	int n;
	scanf("%d",&n);
	Node **arr;
	arr=(Node **)malloc(sizeof(Node *)* n);
	for(int i=0; i<n; i++){
		char ch[10];
		double p;
		scanf("%s%lf",ch,&p);
		arr[i]=getNewNode(ch[0],p);
	}
	Node *root=getHaffmanTree(arr,n);
	output_encode(root);
	clear(root);
	free(arr);
	return 0;
}
