#include <stdio.h>
#include <string.h>

#define MAX_STRING_SIZE 1000100
#define MAX_STRING 105
void Nextval(char T[],int *next)
{
	int lenT=strlen(T);
	int k=-1;//前缀 
	int j=0;//后缀 
	next[0]=-1; 
	
	while(j<lenT)
	{
		if(k==-1||T[j]==T[k])
		{
			j++;
			k++;
			//较之前next数组求法，改动在下面4行
			if(T[j]!=T[k])
			{
				next[j]=k;//之前只有这一行
			}
			else
			{
				next[j]=next[k];/*为不能出现T[j] = T[ next[j ]]，
				                  所以当出现时连续进行两次回溯，k = next[next[k]]  */ 
			 } 
		}
		else 
		{
			k=next[k];
		 } 
	}
}

int KMP(char S[],char T[])
{
	int i=0,j=0,lenS,lenT;
	lenS=strlen(S);
	lenT=strlen(T);
	
	int next[MAX_STRING];
	Nextval(T,next);
	
	while(i<lenS&&j<lenT)
	{
		if(j==-1||S[i]==T[j])
		{
			i++;
			j++;
		}
		else
		{ 
			j=next[j];
		}
	}
	 
	if(j==lenT)
	{   
	  
	 	return i-j;
	} 
	else 
	{
	
		return -1;
    }
}


int main() 
{
    char S[MAX_STRING_SIZE],T[MAX_STRING];
    int target;
	gets(S);
    gets(T);




	target=KMP(S,T);
    while(target>0){
        memcpy(S, S + target, strlen(S + target)+1);
        printf("%d",target);
        target=KMP(S,T);
        
    }
	printf("Position is %d\n",target);
    printf("%s\n", S);

	return 0;
}
