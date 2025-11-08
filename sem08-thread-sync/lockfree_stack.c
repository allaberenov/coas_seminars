#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

typedef struct node {
    int value;
    struct node* next;
} node_t;

typedef struct lockfree_stack {
    _Atomic(node_t*) head;
} lockfree_stack_t;

void push(lockfree_stack_t* stack, int value) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->value = value;

    node_t* old_head;
    do {
        old_head = atomic_load(&stack->head);
        new_node->next = old_head;
    } while (!atomic_compare_exchange_weak(&stack->head, &old_head, new_node));
}

int pop(lockfree_stack_t* stack, int* value) {
    node_t* old_head;
    node_t* new_head;
    do {
        old_head = atomic_load(&stack->head);
        if (old_head == NULL) {
            return 0; // Stack is empty
        }
        new_head = old_head->next;
    } while (!atomic_compare_exchange_weak(&stack->head, &old_head, new_head));

    *value = old_head->value;
    free(old_head);
    return 1; // Success
}



typedef struct {
    lockfree_stack_t* stack;
    int value;
} push_args_t;

void* push_thread(void* arg) {
    push_args_t* args = (push_args_t*)arg;
    push(args->stack, args->value);
    printf("Thread %lu pushed %d\n", pthread_self(), args->value);
    return NULL;
}

int main() {
    lockfree_stack_t stack;
    atomic_store(&stack.head, NULL);

    pthread_t t1, t2, t3, t4;

    push_args_t args1 = { &stack, 10 };
    push_args_t args2 = { &stack, 20 };
    push_args_t args3 = { &stack, 30 };
    push_args_t args4 = { &stack, 40 };


    pthread_create(&t1, NULL, push_thread, &args1);
    pthread_create(&t2, NULL, push_thread, &args2);
    pthread_create(&t3, NULL, push_thread, &args3);
    pthread_create(&t4, NULL, push_thread, &args4);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    int value;
    while (pop(&stack, &value)) {
        printf("Popped: %d\n", value);
    }

    return 0;
}