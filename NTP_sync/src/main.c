#include "application.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void)
{

    char input_cmd[1024] = {0};
    while (1)
    {
        printf("\r\nEnter the option:\n\t\"sync\"- run single sync\n\t"
               "\"set_time\" - set time for the next single sync\r\n\t"
               "\"cont_sync\" - run continuously sync\r\n\t"
               "\"print_diff\" - display difference of NTP and system time\r\n\t"
               "\"exit\" - stop the service\r\n");


        if (scanf("%s", input_cmd) != 1)
        {
            perror("Input error");
            return EXIT_FAILURE;
        }

        if (strcmp(input_cmd, "sync") == 0)
        {
            sync();
        }
        else if (strcmp(input_cmd, "set_time") == 0)
        {
            set_time();
        }
        else if (strcmp(input_cmd, "cont_sync") == 0)
        {
            cont_sync();
        }
        else if (strcmp(input_cmd, "print_diff") == 0)
        {
            print_diff();
        }
        else if (strcmp(input_cmd, "exit") == 0)
        {
            break;
        }
        else
        {
            printf("Unknown command\r\n");
        }
    }

    return 0;
}
