#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char t[1024];
    char p[1024];
    fgets(t,1024,stdin);
    fgets(p,1024,stdin);
    int result = kmp_sort(p, t);
    printf("%d",result);

}

int  kmp_sort(char p[],char t[])
{
    int i,j;
    int * next = (int *)malloc(sizeof(int)*strlen(p));
    generate_next(next, p);

    for(i=0,j=0; i<strlen(p),j<strlen(t);){
        if (p[i] == t[j]){
            i++;j++;
        }
        else if(next[i] >=0){
            i = next[i];
        }
        else{
            i = 0; j++;
        }
    }

    if(i >= strlen(p)){
        return  j - strlen(p);
    }
    else
    return -1;


}

void generate_next(int next[],char * s){
    int i=0,j = -1;
    next[0] = -1;

    
    int len = strlen(s);
    while (i < len){
        while (j>=0 && s[i]!=s[j]){
            j = next[j];
        }
        i++;j++;
        if(s[i] == s[j]){
            next[i] = next[j];
        }
        else 
        next[i] = j;
    }
}