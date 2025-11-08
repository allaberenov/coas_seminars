#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int data_ready = 0;

void* producer(void* arg) {
    sleep(1); // немного подождать, чтобы consumer успел заснуть
    pthread_mutex_lock(&m);
    data_ready = 1;
    printf("Producer: data ready!\n");
    pthread_cond_signal(&cond); // разбудить ждущий поток
    pthread_mutex_unlock(&m);
    return NULL;
}

void* consumer(void* arg) {
    pthread_mutex_lock(&m);
    while (!data_ready) {
        printf("Consumer: waiting...\n");
        pthread_cond_wait(&cond, &m); // отпускает m и засыпает
    }
    printf("Consumer: got the data!\n");
    pthread_mutex_unlock(&m);
    return NULL;
}

int main(void) {
    pthread_t prod, cons;

    pthread_create(&cons, NULL, consumer, NULL);
    pthread_create(&prod, NULL, producer, NULL);

    pthread_join(cons, NULL);
    pthread_join(prod, NULL);

    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&cond);

    return 0;
}
