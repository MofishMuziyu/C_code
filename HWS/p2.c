#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STRING_SIZE 1000000
struct cMystring{
    int length;   
    char str[MAX_STRING_SIZE+1];
};
typedef struct cMystring  CMyString;


void InitCMystring(CMyString *CS, char *s ){
    char *p1,*p2;
    for (CS->length = 0,p1 = CS->str,p2 = (char *)s; *p2; CS->length++){
        *(p1++) = *(p2++);
    }
     *p1 = 0;
}

void DeleteS(CMyString *CS,int pos,int len){
    int rlen = len;
    if (pos + rlen > CS->length){
        rlen = CS->length- pos +1;
    }
    memcpy(CS->str + pos, CS->str + pos +rlen , CS->length -pos +1 );
}

void  Generate_next(int *next , CMyString *s){
    int i=0 , j=-1;
    next[0] = -1; 

    while(j >= 0 && s->str[i] != s->str[j])
     j = next[j];


    i++;j++;

    if(s->str[i] == s->str[j]){
        next[i] = next[j];
    }

    else
    next[i] = j;
}

int Find_KMP(CMyString *CS, CMyString *s){  
    int i,j;
    int *next = (int *)malloc(sizeof(int) *s->length );

    Generate_next(next , s);

    for (i =0,j=0;i<s->length && j<CS->length;){

        if (s->str[i] == CS->str[j]){
            i++;j++;
        }

        else if(next[i]>=0){
            i = next[i];
        }
        else{
            i=0;
            j++;
        }
    }

    if (i>= s->length){
        return j - s->length;
    }
    else
    return -1;
}
int get_length(char *s){
    char* p = s;
    int result = 0;

    while (p){
        result++; p++;
    }
    return result;
}
int main() {    

    int next[101];
    CMyString *p1,*p2;
    char * s1,*s2;
    s1 = (char*)malloc(sizeof(char)*MAX_STRING_SIZE);
    s2 = (char*)malloc(sizeof(char)*105);
    s1 = fgets(s1, MAX_STRING_SIZE,stdin);
    fflush(stdin);
    s2 = fgets(s2, MAX_STRING_SIZE,stdin);
    fflush(stdin);

   //printf("%d", get_length(s1));
   printf("123456\n");
    InitCMystring(p1,s1);
    printf("123456\n");
    InitCMystring(p2,s2);

    int del_len = p2->length;
    Generate_next(next,p2);
    int flag = Find_KMP(p1,p2);
    while(flag != -1){
        DeleteS(p1,flag,del_len);
        flag = Find_KMP(p1,p2);
    }
    
    
    for(int i= 0;i< p1->length;i++){
        printf("%s", p1->str);
    }

    

    return 0;
}

