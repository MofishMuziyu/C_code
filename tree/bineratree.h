#include <stdio.h>
#include <stdlib.h>

#define Treedata int 

typedef struct BinTreeNode{
    Treedata key;
    struct BinTreeNode *leftchild;
    struct BinTreeNode *rightchild;
}BinTreeNode;

typedef struct Bintree{
    BinTreeNode *root;
}Bintree;

void InitBinTree(BinTreeNode *root,Treedata data, BinTreeNode *left,BinTreeNode * right){
    root->leftchild = left;
    root->rightchild = right;
    root->key = data;
}

void CreateBinTree(Treedata data,BinTreeNode* lptr,BinTreeNode *rptr){
    BinTreeNode *p;
    p = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    InitBinTree(p,data,lptr,rptr);
}




int Size(BinTreeNode *t);

int Height(BinTreeNode *t);

BinTreeNode* Find(BinTreeNode *t, Treedata key);
BinTreeNode* LeftChild(BinTreeNode *t);
BinTreeNode* RightChild(BinTreeNode *t);

BinTreeNode* Parent(BinTreeNode *t, Treedata key);bool Equal(BinTreeNode *t1, BinTreeNode *t2); 

bool Equal(BinTreeNode *t1, BinTreeNode *t2);

void Copy(BinTreeNode *t, BinTreeNode *&t1);

void ClearBinTree(BinTreeNode *&t);
