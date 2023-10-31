/*
//  author :lyl
    date : 2023 one day
    use:  to computer the pow(x,y) when the y is very big quickly
and list the number of evrey number.0-9
*/


#include <iostream>
using namespace std;


int i,j,tmp;
void Power(int base , int N);
void Print(int *array,int N);
int main(){
    int base;
    int N;

    cout<<"Please enter the base and the power_number:"<<endl;
    cin>>base;
    cin>>N;
    Power(base,N);

    return 0;

}


void Power(int base , int N){
    int i ;
    int j,tmp,cin;
    int * array ;
    array = new int[N];
    for (j=0;j<N;j++){
        *(array+j) = -1;
    }
    array[N-1] = 1;

    for (j=0 ; j < N ; j++){
        cin = 0;
        i = N-1;
        tmp = 0;
        while (i>=0 && array[i] != -1)
        {
            tmp = array[i] * base + cin ; 
            array[i]  =  tmp%10;
            cin = tmp/10;
            i--;
        }

        if (tmp>=10 && cin>0){
            array[i] = cin; 
        }
    }
    Print(array , N);
    delete [] array;
    

}
void Print(int *array,int N){
    int i ;
    int start = 0;
    int a[10] = {0};
    for (i = 0; i<=N-1 ;i++){
        if (*(array+i) != -1){
            start = i;

            break;
        }
        else{
            continue;
        }
    }
    cout<<"The result is:"<<endl;
    for (i = start;i<=N-1;i++)
    {
        a[*(array+i)]++;
        cout<<*(array+i);
    }
    cout<<endl;
    cout<<"The times of every number in the result is:"<<endl;

    for (int j=0;j<10;j++){
        cout<<"The times of number "<<j<<"  is "<<a[j]<<endl;    
    }

}
