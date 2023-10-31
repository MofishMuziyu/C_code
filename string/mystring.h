#define MAX_STRING_SIZE 1024

struct cMystring{
    int length;   /*串的长度*/
    char str[MAX_STRING_SIZE+1];
};

typedef struct cMystring  CMyString;


void InitCMystring(CMyString *, char *s );
/*初始化函数，创建一个指向字符指针的串*/

void Concatenate(CMyString * ,CMyString *s);
/*将字符串s加入到本字符串之后*/

void InsertS(CMyString *,CMyString *s,int pos);
/*将字符串s插入到本字符串pos所指向的位置*/

void DeleteS(CMyString *,int pos,int len);
/*删除从pos位置起的len个字符*/

CMyString* SubString(CMyString *, int pos,int len);
/*提取一个子串，从pos位置起，长度为len的子串*/

char *Getstring(CMyString *);
/*获取本字符串*/

void  Generate_next(int *next , CMyString *s);
/*产生NEXT数组的函数*/

