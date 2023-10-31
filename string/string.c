#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mystring.h"
/*
struct cMystring{
    int length;   
    char str[MAX_STRING_SIZE+1];
};*/

/*memcpy函数介绍
第一个参数为目的字符串函数
第二个参数为源字符串函数，
第三个是要复制的长度
*/
void InitCMystring(CMyString *CS, char *s ){
    char *p1,*p2;
    for (CS->length = 0,p1 = CS->str,p2 = (char *)s; *p2; CS->length++){
        *(p1++) = *(p2++);
    }
     *p1 = 0;
}

/*初始化函数，创建一个指向字符指针的串*/

void Concatenate(CMyString *CS ,CMyString *s){
    if((CS->length+ s->length )<MAX_STRING_SIZE){
        memcpy(CS->str + CS->length, s->str , s->length);
        CS->length += s->length;
    }

}
/*将字符串s加入到本字符串之后*/

void InsertS(CMyString *CS,CMyString *s,int pos){
    if((CS->length + s->length) <MAX_STRING_SIZE){
        memcpy(CS->str + pos + s->length, CS->str +pos, CS->length -pos + 1);
        memcpy(CS->str + pos, s->str , s->length);
        CS->length += s->length;
    }
    else
        printf("error: overflow");
}
/*将字符串s插入到本字符串pos所指向的位置,原来的部分顺位向后移动*/

void DeleteS(CMyString *CS,int pos,int len){
    int rlen = len;
    if (pos + rlen > CS->length){
        rlen = CS->length- pos +1;
    }
    memcpy(CS->str + pos, CS->str + pos +rlen , CS->length -pos +1 );
}
/*删除从pos位置起的len个字符*/

CMyString* SubString(CMyString *CS, int pos,int len){
    CMyString * p  = (CMyString * )malloc(sizeof(CMyString));
    int rlen = ((pos + len)> CS->length)?(CS->length - pos +1):len;
    p->length = rlen;
    memcpy(p->str, CS->str + pos, rlen);
    return p;
}
/*提取一个子串，从pos位置起，长度为len的子串*/

char *Getstring(CMyString *CS){
    char * s = (char * )malloc(sizeof(char)*CS->length);
    memcpy(s, CS->str , CS->length );
    return s;
}
/*获取本字符串*/


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




// int Find_KMP(CMyString *CS, CMyString *s){   //KMP算法,BM算法
//     int i,j;
//     int *next = (int *)malloc(sizeof(int) *s->length );

//     Generate_next(next , s);

//     for (i =0,j=0;i<s->length && j<CS->length;){

//         if (s->str[i] == CS->str[j]){
//             i++;j++;
//         }

//         else if(next[i]>=0){
//             i = next[i];
//         }
//         else{
//             i=0;
//             j++;
//         }
//     }

//     if (i>= s->length){
//         return j - s->length;
//     }
//     else
//     return -1;
// }
// /*在本字符串中查找字符串s首次出现的位置，如果不存在就返回-1*/





