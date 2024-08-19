#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct alarm_tag
{
    int seconds;
    char message[100];
} alarm_t;

static void errno_abort(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

void *alarm_thread(void *arg)
{
    alarm_t *alarm = (alarm_t *)arg;
    int status;

    status = pthread_detach(pthread_self());
    if (status != 0)
    {
        errno_abort("pthread_detach");
    }
    sleep(alarm->seconds);
    printf("Sleep %d seconds, Alarm: %s\n", alarm->seconds, alarm->message);
    free(alarm);
    return NULL;
}

int main()
{
    int status;
    char line[100];
    pthread_t thread;

    while (1)
    {
        printf("Alarm> \n");
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            exit(0);
        }

        if (strlen(line) <= 1)
        {
            continue;
        }

        alarm_t *alarm = (alarm_t *)malloc(sizeof(alarm_t));
        if (alarm == NULL)
        {
            errno_abort("Allocate alarm");
        }

        if (sscanf(line, "%d %99[^\n]", &alarm->seconds, alarm->message) < 2)
        {
            fprintf(stderr, "Invalid input\n");
            free(alarm);
        }
        else
        {
            status = pthread_create(&thread, NULL, alarm_thread, alarm);
            if (status != 0)
            {
                errno_abort("pthread_create");
            }
        }
    }

    return 0;
}
