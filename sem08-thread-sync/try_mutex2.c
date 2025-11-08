typedef struct {
    volatile int locked = -1; // -1 means unlocked, 0 or 1 means locked by that thread
    volatile bool flag[2]; // flags for each thread
} Mutex;


void lock(Mutex* mutex, int thread_id) { // thread_id should be 0 or 1
    int other = 1 - thread_id;
    mutex->flag[thread_id] = true;
    mutex->locked = thread_id;
    while (mutex->flag[other] && mutex->locked == thread_id) {
        // busy wait
    }
}

void unlock(Mutex* mutex, int thread_id) {
    mutex->flag[thread_id] = false;
    mutex->locked = thread_id;
}