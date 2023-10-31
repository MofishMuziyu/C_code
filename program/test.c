    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <pthread.h>
    #include <semaphore.h>
    #include <time.h>
    /*程序要求*/
    //A先于BCE ----signal1
    //E,D先于F ----signal2
    //B，C先于D ----signal3
    //F，先于G,H ----signal4
    //思路就是所有初始量定义为零，先的会释放一个
    //初始量，后的会占用一个初始量，因为是初始是0，所以
    //没有释放的情况下就不会有占用，保证了先后顺序

    /*信号量定义*/
    sem_t signal1,signal2,signal3,signal4;

    /*休眠函数，便于观察打断*/
    void sleep_random(int t){
        sleep((int)(t *(rand()/RAND_MAX*1.0)));
    }


    void *A(){
        sleep_random(2);//随机休眠

        printf("My name is A.\n");

        sem_post(&signal1);
    }

    void *B(){
        sleep_random(2);//随机休眠
        sem_wait(&signal1);

        printf("My name is B.\n");

        sem_post(&signal3);
        sem_post(&signal1);
    }

    void *C(){
        sleep_random(2);//随机休眠
        sem_wait(&signal1);

        printf("My name is C.\n");

        sem_post(&signal3);
        sem_post(&signal1);
    }

    void *D(){
        sleep_random(2);//随机休眠
        sem_wait(&signal3);
        sem_wait(&signal3);
        printf("My name is D.\n");

        sem_post(&signal2);
    }

    void *E(){
        sleep_random(2);//随机休眠
        sem_wait(&signal1);
        printf("My name is E.\n");

        sem_post(&signal2);
        sem_post(&signal1);
    }

    void *F(){
        sleep_random(2);//随机休眠
        sem_wait(&signal2);
        sem_wait(&signal2);
        printf("My name is F.\n");

        sem_post(&signal2);
        sem_post(&signal4);
    }

    void *G(){
        sleep_random(2);//随机休眠
        sem_wait(&signal4);
        printf("My name is G.\n");

        sem_post(&signal4);
    }

    void *H(){
        sleep_random(2);//随机休眠

        sem_wait(&signal4);
        printf("My name is H.\n");

        sem_post(&signal4);
    }



    int main()
    {
        int i;
        pthread_t t[8];
        srand((int)time(0));

        /*信号量初始化*/
        sem_init(&signal1,0,0);
        sem_init(&signal2,0,0);
        sem_init(&signal3,0,0);
        sem_init(&signal4,0,0);
        /*创建线程*/

        pthread_create(&t[0],NULL,A,NULL);
        pthread_create(&t[1],NULL,B,NULL);
        pthread_create(&t[2],NULL,C,NULL);
        pthread_create(&t[3],NULL,D,NULL);
        pthread_create(&t[4],NULL,E,NULL);
        pthread_create(&t[5],NULL,F,NULL);
        pthread_create(&t[6],NULL,G,NULL);
        pthread_create(&t[7],NULL,H,NULL);
            
        /*合并线程*/
        for(i=0;i<=7;i++){
            pthread_join(t[i],NULL);
        }
        return 0;
    }


