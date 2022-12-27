/*************************************************************************
	> File Name: 5.binary_tree.cpp
	> Author: 
	> Mail: 
	> Created Time: 
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {//定义二叉树的节点 
    int data;//节点数据域 
    struct Node *lchild, *rchild;//节点指针域 
} Node;

typedef struct Tree {//定义树形结构的结构定义 
    Node *root;//根节点的结构地址 
    int length;
} Tree;

Node *getNewNode(int val) {//节点初始化 
    Node *p = (Node *)calloc(1, sizeof(Node));
    /*
    void* calloc(size_t num,size_t size); 
	为num个对象的数组分配内存，并初始化所以分配存储中的字节为0
	若分配成功，会返回指向分配内存块最低位字节的指针，他为任何类型适当的对齐
	若size为0，则行为是实现定义的(可返回空指针，或返回不可用访问存储的非空指针)
	*/ 
    p->data = val;
    return p;
}

Tree *getNewTree() {//二叉树初始化 
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;//根节点 
    tree->length = 0;//节点个数 
    return tree;
}

void clear_node(Node *root) {//销毁节点 
    if (root == NULL) return ;
    clear_node(root->lchild);
    clear_node(root->rchild);
    free(root);
    return ;
}

void clear(Tree *tree) {//销毁树 
    if (tree == NULL) return ;
    clear_node(tree->root);
    free(tree);
    return ;
}

Node *insert_node(Node *root, int val, int *flag) {
    if (root == NULL) {
        *flag = 1;
        return getNewNode(val);
    }
    if (root->data == val) return root;
    if (root->data < val) root->rchild = insert_node(root->rchild, val, flag);
    else root->lchild = insert_node(root->lchild, val, flag);
    return root;
}

void insert(Tree *tree, int val) {
    if (tree == NULL) return ;
    int flag = 0;
    tree->root = insert_node(tree->root, val, &flag);
    tree->length += flag;
    return ;
}

void pre_order_node(Node *root) {
    if (root == NULL) return ;
    printf("%d ", root->data);
    pre_order_node(root->lchild);
    pre_order_node(root->rchild);
    return ;
}

void pre_order(Tree *tree) {
    if (tree == NULL) return ;
    printf("pre_order : ");
    pre_order_node(tree->root);
    printf("\n");
    return ;
}

void in_order_node(Node *root) {
    if (root == NULL) return ;
    in_order_node(root->lchild);
    printf("%d ", root->data);
    in_order_node(root->rchild);
    return ;
}

void in_order(Tree *tree) {
    if (tree == NULL) return ;
    printf("in_order : ");
    in_order_node(tree->root);
    printf("\n");
    return ;
}

void post_order_node(Node *root) {
    if (root == NULL) return ;
    post_order_node(root->lchild);
    post_order_node(root->rchild);
    printf("%d ", root->data);
    return ;
}

void post_order(Tree *tree) {
    if (tree == NULL) return ;
    printf("post_order : ");
    post_order_node(tree->root);
    printf("\n");
    return ;
}

void output_node(Node *root) {
    if (root == NULL) return ;
    printf("%d", root->data);
    if (root->lchild == NULL && root->rchild == NULL) return ;
    printf("(");
    output_node(root->lchild);
    printf(", ");
    output_node(root->rchild);
    printf(")");
    return ;
}

void output(Tree *tree) {
    if (tree == NULL) return ;
    printf("tree(%d) : ", tree->length);
    output_node(tree->root);
    printf("\n");
    return ;
}

int main() {
    srand(time(0));
    Tree *tree = getNewTree();
    #define MAX_OP 10
    for (int i = 0; i < MAX_OP; i++) {
        int val = rand() % 100;
        insert(tree, val);
        output(tree);
    }
    pre_order(tree);
    in_order(tree);
    post_order(tree);
    #undef MAX_OP
    clear(tree);
    return 0;
}
