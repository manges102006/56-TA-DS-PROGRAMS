#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPH 26

typedef struct TrieNode{
    struct TrieNode *children[ALPH];
    int isEnd;
} TrieNode;

TrieNode* getNode(){
    TrieNode *p = malloc(sizeof(TrieNode));
    p->isEnd = 0;
    for(int i=0;i<ALPH;i++) p->children[i]=NULL;
    return p;
}

void insertTrie(TrieNode *root, const char *key){
    TrieNode *p = root;
    for(int i=0;i<strlen(key);i++){
        int idx = tolower(key[i]) - 'a';
        if(idx<0 || idx>=ALPH) continue;
        if(!p->children[idx]) p->children[idx] = getNode();
        p = p->children[idx];
    }
    p->isEnd = 1;
}
int searchTrie(TrieNode *root, const char *key){
    TrieNode *p = root;
    for(int i=0;i<strlen(key);i++){
        int idx = tolower(key[i]) - 'a';
        if(idx<0 || idx>=ALPH) continue;
        if(!p->children[idx]) return 0;
        p = p->children[idx];
    }
    return p != NULL && p->isEnd;
}

int main(){
    TrieNode *root = getNode();
    insertTrie(root, "and");
    insertTrie(root, "bat");
    insertTrie(root, "ball");
    printf("Search 'bat': %s\n", searchTrie(root,"bat")? "Found":"Not Found");
    printf("Search 'cat': %s\n", searchTrie(root,"cat")? "Found":"Not Found");
    return 0;
}
