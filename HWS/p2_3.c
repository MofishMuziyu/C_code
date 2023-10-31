#include <stdio.h>
#include <string.h>
#define N 1000100
#define M 120
int main(){
    char s1[N],s2[M],s3[N];

    fgets(s1, N, stdin);
    fgets(s2, M, stdin);

    int len1 = strlen(s1) -1;
    int len2 = strlen(s2) -1;
    //printf("%s\n", s1);
    int i = 0;
    int index = 0;
    int j;
    for(i = 0; i < len1; i++){
        s3[index] = s1[i];
        index++;
        if(index  >= len2){
            int flag = 1;
            for(j = 0; j < len2; j++){
                if(s3[index-len2+j] != s2[j])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1){
                index -= len2;
            }
        }
    }
    s3[index] = '\0';
    printf("%s",s3);
}