#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BASE 26

typedef struct Node {
    const char *str;//NULL 表示目前无法独立成词
    struct Node *next[BASE], *fail;
} Node;

int node_cnt;

Node *getNewNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    p->str = NULL;
    p->fail = NULL;
    memset(p->next, 0, sizeof(Node *) * BASE);
    node_cnt += 1;
    return p;
}

inline int ind(char ch) {
    return ch - 'a';
}

const char *copyStr(const char *str) {
    int n = strlen(str);
    char *buff = (char *)malloc(sizeof(char) * (n + 1));
    strcpy(buff, str);
    return buff;
}

void insert(Node *root, const char *str) {
    Node *p = root;
    for (int i = 0; str[i]; ++i) {
        int ind = str[i] -  'a';
        if (p->next[ind] == NULL) p->next[ind] = getNewNode();
        p = p->next[ind];
    }
    p->str = copyStr(str);
    return ;
}

//-------------------------------------

typedef struct Queue {
    Node **data;
    int head, tail;
} Queue;

Queue *init_queue(int cnt) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (Node **)malloc(sizeof(Node *) * cnt);
    q->head = q->tail = 0;
    return q;
}

void push(Queue *q, Node *node) {
    if (q == NULL) return ;
    q->data[q->tail++] = node;
    return ;
}

int empty(Queue *q) {
    return q->head == q->tail;
}

void pop(Queue *q) {
    if (empty(q)) return ;
    q->head += 1;
    return ;
}

Node *front(Queue *q) {
    return q->data[q->head];
}

void clear_queue(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

void init_clear_queue(Queue *q, Queue *clear_node, Node *root) {
    push(clear_node, root);
    for (int i = 0; i < BASE; ++i) {
        if (root->next[i] == root) continue;
        push(q, root->next[i]);
        push(clear_node, root->next[i]);
    }
    return ;
}

void clear(Node *root) {
    Queue *clear_node = init_queue(node_cnt);
    Queue *q = init_queue(node_cnt);
    init_clear_queue(q, clear_node, root);
    while (!empty(q)) {
        Node *tmp = front(q);
        pop(q);
        for (int i = 0; i < BASE; ++i) {
            if (tmp->next[i] != tmp->fail->next[i]) {
                push(clear_node, tmp->next[i]);
                push(q, tmp->next[i]);
            }
        }
    }
    int cnt = 0;
    while (!empty(clear_node)) {
        Node *tmp = front(clear_node);
        free(tmp);
        pop(clear_node);
        cnt += 1;
    }
    printf("cnt : %d; node_cnt : %d\n", cnt, node_cnt);
    clear_queue(q);
    clear_queue(clear_node);
    return ;
}

Queue *init_ac_queue(Node *root) {
    Queue *q = init_queue(node_cnt);
    for (int i = 0; i < BASE; ++i) {
        if (root->next[i] == NULL) {
            root->next[i] = root;
        } else {
            root->next[i]->fail = root;
            push(q, root->next[i]);
        }
    }
    return q;
}

void build_ac(Node *root) {
    if (root == NULL) return ;
    Queue *q = init_ac_queue(root);
    while (!empty(q)) {
        Node *tmp = front(q);
        for (int i = 0; i < BASE; ++i) {
            if (tmp->next[i] == NULL) {
                tmp->next[i] = tmp->fail->next[i];
                continue;
            }
            Node *k = tmp->fail;
            tmp->next[i]->fail = k->next[i];
            push(q, tmp->next[i]);
        }
        pop(q);
    }
    clear_queue(q);
    return ;
}

void match_ac(Node *root, const char *str) {
    Node *p = root;
    for (int i = 0; str[i]; ++i) {
        int tmp = ind(str[i]);
        printf("input %c\n", str[i]);
        p = p->next[tmp];
        Node *q = p;
        while (q) {
            if (q->str != NULL) printf("find %s\n", q->str);
            q = q->fail;
        }
    }
    return ;
}

int main() {
    int n;
    char str[100];
    scanf("%d", &n);
    Node *root = getNewNode();
    for (int i = 0; i < n; ++i) {
        scanf("%s", str);
        insert(root, str);
    }
    build_ac(root);
    scanf("%s", str);
    match_ac(root, str);
    clear(root);
    return 0;
}