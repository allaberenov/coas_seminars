#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t sem; // наш семафор

void* worker(void* arg) {
    sem_wait(&sem);  // ↓ захватывает "ресурс"
    printf("Thread %ld entered critical section\n", (long)arg);
    sleep(6);
    printf("Thread %ld leaving\n", (long)arg);
    sem_post(&sem);  // ↑ освобождает ресурс
    return NULL;
}

int main() {
    pthread_t t[5];
    printf("ret = %d\n", sem_init(&sem, 0, 2));  // начальное значение = 2 (два потока могут одновременно работать)

    for (int i = 0; i < 5; i++)
        pthread_create(&t[i], NULL, worker, (void*)(long)i);
        sleep(2);

    for (int i = 0; i < 5; i++)
        pthread_join(t[i], NULL);

    sem_destroy(&sem);
}
