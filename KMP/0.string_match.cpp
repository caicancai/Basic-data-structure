#include<iostream>
#include<string>
#include<cstdio>
#include<stdlib.h>
#include<cstring>
using namespace std;


int brute_force(const char *text,const char *pattern){
    for(int i=0; text[i]; ++i){
        int flag=1;
        for(int j=0; pattern[j]; ++j){
            if(text[i+j]== pattern[j]) continue;
            flag=0;
            break;
        }
        if(flag) return i;
    }
    return -1;
}

void getNext(const char *t,int *next){
    next[0] = -1;
    int j=-1;
    for(int i = 1; t[i]; i++){
        while(j !=-1 && t[j+1] != t[i]) j=next[j];
        if(t[j+1] == t[i]) j+=1;
        next[i]=j;
    }
    return ;
}

int kmp(const char *s,const char *t){
    int n=strlen(t);
    int *next = (int *)malloc(sizeof(int));
    getNext(t,next);
    for(int i=0, j=-1; s[i]; i++){
        while(j!=-1 && s[i]!=t[j+1]) j=next[j];
        if(t[j+1]==s[i]) j+=1;
        if(t[j+1]==0){
            free(next);
            return i-n+1;
        }
    }
    free(next);
}

int sunday(const char *text,const char *pattern){
    #define BASE 256
    int n=strlen(text),m,last_pos[BASE];
    for(int i=0; i<BASE; i++) last_pos[i] = -1;
    for(m=0; pattern; ++m) last_pos[pattern[m]]=m;
    for(int i=0; i + m <= n;i+=(m-last_pos[text[i + m]])){
        int flag=1;
        for(int j=0; pattern[j]; ++j){
            if(text[i + j]==pattern[j]) continue;
            flag=0;
            break;
        }
        if(flag) return i;
    }
    return -1;
}

#define TEST(func,s1,s2){\
    printf("%s(%s,%s)=%d\n",#func,s1,s2,func(s1,s2));\
}
int main(){
    char s1[100],s2[100];
    while(cin >> s1 >> s2){
        TEST(brute_force, s1,s2);
        TEST(kmp,s1,s2);
        TEST(sunday,s1,s2);
    }

    return 0;
}

