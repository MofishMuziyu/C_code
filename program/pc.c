#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
    /*程序要求：建立一个生产者，五个消费者进程
    文件建立一个共享区
    生产者依次向缓存区写入整数0,1,2，...499
    每个消费者读取100个数，每读取一个就打印出来；
    缓存区文件最多只能保存10个数；

    生产者写入的数不必打印出来
    */
#define MAX_PRODUCE 500;
#define MAX_LENGTH 10;
#define MAX_CONSUME 100;

int share[10];
int if_read,if_write;
sem_t empty,full,consumer;
int consume_id=0;
void sleep_random(int t){
    sleep((int)(t *(rand()/RAND_MAX*1.0)));
}

void *produce(){
    sleep_random(2);
    int i;

    for (i=0;i<500;i++){
        sem_wait(&empty);
        share[if_write++] = i;
        if_write %=10;
        sem_post(&full);
    }
}


void *consumer5(){

    sleep_random(2);
    int i;
    int value;
    consume_id++;

    for (i=0; i<100; i++){
        sem_wait(&consumer);
        sem_wait(&full);
        value  =  share[if_read++];
        if_read %=10;
        printf("%d : %d \n",&consume_id,&value);
        sem_post(&empty);
        sem_post(&consumer);
    }


}


int main(){
    int i;
    sem_init(&empty,0,10);
    sem_init(&full,0,0);
    sem_init(&consumer,0,1);

    if_read = 0;
    if_write = 0;

    pthread_t consume[5];
    pthread_t p;

    pthread_create(&p,NULL,produce,NULL);
    for (i=0;i<5;i++){
        pthread_create(&consume[i],NULL,consumer5,NULL);

    }
    for (i=0;i<5;i++){
        pthread_join(consume[i],NULL);
    }
    pthread_join(p,NULL);

    return 0;

}