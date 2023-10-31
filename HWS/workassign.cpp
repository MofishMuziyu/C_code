#include<iostream>
using namespace std;
#define MAX 100100
int porfit(int time,int div_time);
struct task{
    int pre_time;
    int xjb;
    int profit;
};
/*
*/
int main(){
    int N;
    int i,j,k;
    task tasks[MAX];
    cin>>N;
    for (i = 0;i< N ;i++){
        cin>>tasks[i].pre_time;  
    }
    for(j=0;j<N;j++){
        cin>>tasks[j].xjb;
        tasks[j].profit = tasks[j].pre_time * tasks[j].xjb;
    }









}

