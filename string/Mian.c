#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)


int FindSubStr(char* t, char* p){
    int len_p = strlen(p);
    int len_t = strlen(t);
    int i,j;
    for(i=0;i<len_t-len_p;i++){
        j=0;
        while(j<len_p && p[j]==t[j+i]) j++;
        if(j==len_p){
            return i;
        }
    }1
    return -1;


}
int main()
{
	// to test finding the first son string
	char t[100]; // mother string
	char p[100]; // son string
	scanf("%s", t);
	scanf("%s", p);
	int i=FindSubStr(t, p);
	printf("Location: ");
	if(i==-1) printf("not found!");
	else printf("%d",i);
    return 0;
}