/**
 * @file lifecycle.c
 * @author sunmy
 * @date 2024-08-19
 * @brief This is the implementation of pthread lifecycle example.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <error.h>

typedef struct thread_args
{
    int value;
    char name[100];
} thread_args;

static void *thread_routine(void *arg)
{
    thread_args *args = (thread_args *)arg;
    printf("value: %d, name: %s\n", args->value, args->name);

    printf("Thread id: %lu\n", pthread_self());
    return arg;
}

int main()
{
    pthread_t thread_id;
    void *thread_result;
    int status;

    thread_args *args = (thread_args *)malloc(sizeof(thread_args));
    args->value = 100;
    strcpy(args->name, "Thread Child");

    status = pthread_create(&thread_id, NULL, thread_routine, args);
    if (status != 0)
    {
        error(1, status, "pthread_create failed");
    }
    else
    {
        printf("Thread created successfully\n");
    }

    printf("Main thread id: %lu\n", pthread_self());

    status = pthread_join(thread_id, &thread_result);
    if (status != 0)
    {
        error(1, status, "pthread_join failed");
    }
    else
    {
        printf("Thread joined successfully\n");
    }

    if (thread_result == NULL)
    {
        printf("Thread returned NULL, Test failed\n");
        return 0;
    }
    else
    {
        printf("Thread returned %p Test passed\n", thread_result);
        return 1;
    }

    return 0;
}