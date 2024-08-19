#include <stdio.h>
#include <error.h>

int main(int argc, char *argv[])
{
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

        /**
         * Parse input line into seconds and message
         * (%63[^\n]), consisting of up to 63 characters
         * separated from the seconds by a space, and
         * terminated by a newline character.
         * 
         */
        if (sscanf(line, "%d %63[^\n]", &seconds, message) < 2)
        {
            fprintf(stderr, "Invalid input\n");
            continue;
        }
        else if (seconds < 0)
        {
            fprintf(stderr, "Invalid input\n");
            continue;
        }
        else
        {
            sleep(seconds);
            printf("Alarm (%d) seconds: %s\n", seconds, message);
        }
    }
}