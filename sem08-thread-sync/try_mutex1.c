
typedef struct {
    volatile bool flag[2] = {false, false}; // flags for each thread
} Mutex;

void lock(Mutex* mutex, int thread_id) { // thread_id should be 0 or 1
    int other = 1 - thread_id;
    mutex->flag[thread_id] = true;
    while (mutex->flag[other]) {
        // busy wait
    }
}

void unlock(Mutex* mutex, int thread_id) {
    mutex->flag[thread_id] = false;
}

int main() {
    Mutex mutex;
    
    return 0;
}