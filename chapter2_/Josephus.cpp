/*
author :lyl
date:  2023.6.5
function: to solve the Joesphus Problem
Input : n  -- number of all people
        m  -- who call the number m is the person to leave
        s  -- from who to start || 没有实现，但是可以通过提前旋转来达到。

用链表来实现
*/

#include<iostream>
using namespace std;

#define N 10
struct liner_loop{
    int data;
    struct liner_loop* next;
};

void Insert(liner_loop *root,liner_loop *node){
    liner_loop *p = root;
    while(p->next != root){
        p = p->next;
    }
    p->next = node;
    node->next = root;
}

liner_loop* delete_next(liner_loop *node){
    if(node->next!= node){
        liner_loop *p = node->next;
        node->next = node->next->next;
        free(p);
        return node->next;
    }
}
liner_loop* Joesphus(liner_loop* root, int n,int m){
    struct liner_loop *p =root;
    int i,j;

    if(m==1){
        while(p->next!=root){
            liner_loop *tmp=p;
            p=p->next;
            free(tmp);
        }
   
    }
    else{
        while(p->next != p){
        for(i=1;i<m-1;i++){
            p = p->next;
        }
        p = delete_next(p);
        }
 
    }

           return p;

}

int main(){
    int data[N];
    for(int i=0;i<N;i++){data[i] = i+1;}
    int n,m;
    cout<<"Please Enter The n, m."<<endl;
    cin>>n>>m;

    struct liner_loop *root = (liner_loop*)malloc(sizeof(liner_loop));
    root->data = 1;
    root->next = root;

    for(int i=2;i<=n;i++){
        struct liner_loop *tmp = (liner_loop*)malloc(sizeof(liner_loop));
        tmp->data=i;
        tmp->next = NULL;
        Insert(root,tmp);
    }

    liner_loop * result =Joesphus(root,n,m);
    cout<<result->data<<endl;

}
