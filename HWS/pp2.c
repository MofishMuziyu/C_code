#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STRING_SIZE 1000000

int get_length(char * string){
    int length = 0; 
    while(string[length] != '\0') { 
        length++; 
    }
    return length; 
}

void delete(char * string, int index, int len){

}

void  Generate_next(int *next ,char* str){
    int i=0 , j=-1;
    next[0] = -1; 

    while(j >= 0 && str[i] != str[j])
     j = next[j];


    i++;j++;

    if(str[i] == str[j]){
        next[i] = next[j];
    }

    else
    next[i] = j;
}

int Find_KMP(char *CS, char *s, int CS_length,int s_length){  
    int i,j;
    int *next = (int *)malloc(sizeof(int) *s_length );

    Generate_next(next , s);

    for (i =0,j=0;i<s_length && j<CS_length;){

        if (s[i] == CS[j]){
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

    if (i>= s_length){
        return j - s_length;
    }
    else
    return -1;
}
int main(){
    char str1[MAX_STRING_SIZE],str2[105];
    int next[105]={0};

    fgets(str1,MAX_STRING_SIZE,stdin);
    fgets(str2,105,stdin);
    //printf("%s", str1);
    int len1 = get_length(str1);
    int len2 = get_length(str2);
    //printf("%d", len1);

    int index =  Find_KMP(str1,str2,len1,len2) +1 ;
    printf("%d  index:\n", index);
    while(index != -1){
        int rlen = len2;
        if (index + rlen > len1){
            rlen = len1- index +1;
        }
        memcpy(str1 + index, str1 + index +rlen , len1 - index +1 );
        index = Find_KMP(str1,str2,len1,len2);
    }
    printf("%s\n",str1);

}