#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    int color;
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    NIL->key = -1;
    NIL->color = 1;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NIL;
    p->color = 0;
    return p;
}

int has_red_child(Node *root) {
    return root->lchild->color == 0 || root->rchild->color == 0;
}

Node *left_rotate(Node *root) {
    printf("left rotate : %d\n", root->key);
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}

Node *right_rotate(Node *root) {
    printf("right rotate : %d\n", root->key);
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}

const char *maintain_str[] = {"", "LL", "LR", "RR", "RL"};

Node *insert_maintain(Node *root) {
    if (!has_red_child(root)) return root;
    if (root->lchild->color == 0 && root->rchild->color == 0) {
        printf("Situation 1 : change color\n");
        root->color = 0;
        root->lchild->color = 1;
        root->rchild->color = 1;
        return root;
    }
    if (root->lchild->color == 0 && !has_red_child(root->lchild)) return root;
    if (root->rchild->color == 0 && !has_red_child(root->rchild)) return root;
    int flag = 0;
    printf("Situation 2: \n");
    if (root->lchild->color == 0) {
        if (root->lchild->rchild->color == 0) {
            root->lchild = left_rotate(root->lchild);
            flag = 2;
        } else {
            flag = 1;
        }
        root = right_rotate(root);
    } else {
        if (root->rchild->lchild->color == 0) {
            root->rchild = right_rotate(root->rchild);
            flag = 3;
        } else {
            flag = 4;
        }
        root = left_rotate(root);
    }
    printf("Maintain Type : %s\n", maintain_str[flag]);
    printf("Situation 2 : change color\n");
    root->color = 0;
    root->lchild->color = 1;
    root->rchild->color = 1;
    return root;
}

Node *__insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (key < root->key) {
        root->lchild = __insert(root->lchild, key);
    } else {
        root->rchild = __insert(root->rchild, key);
    }
    return insert_maintain(root);
}

Node *insert(Node *root, int key) {
    root = __insert(root, key);
    root->color = 1;
    printf("change root color to black!\n");
    return root;
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

Node *erase_maintain(Node *root) {
    if (root->lchild->color != 2 && root->rchild->color != 2) return root;
    if (has_red_child(root)) {
        printf("Situation X : brother is red!\n");
        int flag = 0;
        root->color = 0;
        if (root->lchild->color == 0) {
            root = right_rotate(root); flag = 0;
        } else {
            root = left_rotate(root); flag = 1;
        }
        root->color = 1;
        if (flag == 0) root->rchild = erase_maintain(root->rchild);
        else root->lchild = erase_maintain(root->lchild);
        return root;
    }
    if ((root->lchild->color == 2 && !has_red_child(root->rchild)) || 
        (root->rchild->color == 2 && !has_red_child(root->lchild))) {
        printf("Situation 1 : change color done!\n");
        root->color += 1;
        root->lchild->color -= 1;
        root->rchild->color -= 1;
        return root;
    }
    int maintain_type = 0;
    if (root->rchild->color == 2) {
        root->rchild->color = 1;
        if (root->lchild->lchild->color != 0) {
            root->lchild->color = 0;
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = 1;
            maintain_type = 2;
        } else {                                      
            maintain_type = 1;
        }
        root = right_rotate(root);
        root->color = root->rchild->color;
    } else { 
        root->lchild->color = 1;
        if (root->rchild->rchild->color != 0) {
            root->rchild->color = 0;
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = 1;
            maintain_type = 3;
        } else {
            maintain_type = 4;
        }
        root = left_rotate(root);
        root->color = root->lchild->color;
    }
    root->lchild->color = root->rchild->color = 1;
    printf("Maintain Type : %s\n", maintain_str[maintain_type]);
    return root;
}

Node *__erase(Node *root, int key) {
    if (root == NIL) return NIL;
    if (key < root->key) {
        root->lchild = __erase(root->lchild, key);
    } else if (key > root->key) {
        root->rchild = __erase(root->rchild, key);
    } else {
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = root->lchild == NIL ? root->rchild : root->lchild;
            temp->color += root->color;
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);
        }
    }
    return erase_maintain(root);
}

void output(Node *);

Node *erase(Node *root, int key) {
    printf("\n earse %d from red black tree : \n", key);
    root = __erase(root, key);
    root->color = 1;
    printf("change root color to black\n");
    output(root);
    return root;
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void print(Node *root) {
    printf("(%d | %d, %d, %d)\n",
          root->color, root->key, 
          root->lchild->key,
          root->rchild->key
    );
    return ;
}

void __output(Node *root) {
    if (root == NIL) return ;
    print(root);
    __output(root->lchild);
    __output(root->rchild);
    return ;
}

void output(Node *root) {
    __output(root);
    printf("NIL : ");
    print(NIL);
    return ;
}

Node *rand_insert(Node *root) {
    int val = rand() % 100;
    printf("\ninsert %d to RB_Tree : \n", val);
    root = insert(root, val);
    printf("-----------------\n");
    output(root);
    printf("-----------------\n");
    return root;
}

int main() {
    int n;
    srand(time(0));
    scanf("%d", &n);
    Node *root = NIL;
    for (int i = 0; i < n; i++) {
        root = rand_insert(root);
    }
    while (~scanf("%d", &n)) {
        root = erase(root, n);
    }
    clear(root);
    return 0;
}
