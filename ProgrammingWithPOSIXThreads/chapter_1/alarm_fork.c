#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

static void errno_abort(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    int seconds = 0;
    char line[128];
    char message[64];

    while (1)
    {
        printf("Alarm >\n");
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            exit(0);
        }

        if (strlen(line) <= 1)
        {
            continue;
        }

        if (sscanf(line, "%d %63[^\n]", &seconds, message) < 2)
        {
            fprintf(stderr, "Bad input format\n");
        }
        else if (seconds <= 0)
        {
            fprintf(stderr, "Seconds must be a positive integer\n");
        }
        else
        {
            pid = fork();
            if (pid == (pid_t)-1)
            {
                errno_abort("Fork");
            }

            if (pid == (pid_t)0)
            {
                sleep(seconds);
                printf("Sleep %d seconds, Alarm: %s\n", seconds, message);
                exit(0);
            }
            else
            {
                do
                {
                    pid = waitpid((pid_t)-1, &status, WNOHANG);
                    if (pid == (pid_t)-1)
                    {
                        errno_abort("Wait for child pid");
                    }
                } while (pid > 0);
            }
        }
    }
}
