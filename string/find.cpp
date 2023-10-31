/*************************************************************
    date: April 2009
    copyright: Zhu En
    DO NOT distribute this code.
**************************************************************/

int FindSubStr(char* t, char* p)
/*
从字符串t查找子字符串p。
字符串以数值结尾，例如p="str",那么p[0]='s',p[1]='t',p[2]='r',p[3]=0。
采用朴素的匹配算法。
返回子字符串第一次出现的位置,例如t="string ring",p="ring"，则返回2。
若没有找到，则返回-1。
*/
{
    // 请在此添加代码，补全函数FindSubStr
    /********** Begin *********/
    int result = -1;
    int i=0;
    char *init_p = p;
    char *init_t = t;
    while(p){
        if(t==0){
            i = -1;
            break;
        }
        if(p == t){
            p++;t++;i++;
        }
        else{
            t++;i++;
            p = init_p;
        }
    }
    if(i==-1) return i;
    else{
        return i-(p - init_p);
    }


    /********** End **********/
}
