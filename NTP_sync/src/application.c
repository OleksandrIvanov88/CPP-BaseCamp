#include "application.h"
#include "time_pocess.h"

#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <errno.h>

static const char *HOST = "200.20.186.76";
static const uint16_t PORT = 123;

static int64_t proces_time(const time_t *ntp_time)
{
    if (NULL == ntp_time)
    {
        errno = EFAULT;
        error_handling("ERROR!!!NULL pointer passed to the function proces_time");
    }
    const uint64_t NTP_TIMESTAMP_DELTA = 2208988800ull;
    int64_t ntp_time_proc = ntohl(*ntp_time);
    ntp_time_proc -= NTP_TIMESTAMP_DELTA;

    return ntp_time_proc;
}

static void print_times(const int64_t *ntp_time)
{
    if (NULL == ntp_time)
    {
        errno = EFAULT;
        error_handling("ERROR!!!NULL pointer passed to the function print_times");
    }
    printf("NTP    time is %s", ctime(ntp_time));
    int64_t sys_time = time(0);
    printf("System time is %s", ctime(&sys_time));
    printf("System time is %li seconds off NTP\r\n", (sys_time - *ntp_time));
}

static int8_t compare_time(const struct tm *tm_1, const struct tm *tm_2)
{
    if (NULL == tm_1 || NULL == tm_2)
    {
        errno = EFAULT;
        error_handling("ERROR!!!NULL pointer passed to the function compare_time");
    }
    if (tm_1->tm_hour != tm_2->tm_hour)
        return 0;
    if (tm_1->tm_min != tm_2->tm_min)
        return 0;
    if (tm_1->tm_sec != tm_2->tm_sec)
        return 0;

    return 1;
}

void sync(void)
{
    time_t ntp_time = get_ntp_time(HOST, PORT);
    int64_t ntp_time_proc = proces_time(&ntp_time);
    print_times(&ntp_time_proc);
    printf("Synchronization...\r\n");
    set_sys_time(&ntp_time_proc);
    print_times(&ntp_time_proc);
}

void set_time(void)
{
    char cur_date[256] = {0};
    printf("Enter the today time waiting for (example 18:58:09):");
    int hh, mm, ss;
    struct tm when = {0};
    scanf("%s", cur_date);
    sscanf(cur_date, "%d:%d:%d", &hh, &mm, &ss);
    when.tm_hour = hh;
    when.tm_min = mm;
    when.tm_sec = ss;
    time_t sys_time = time(NULL);
    struct tm *local = localtime(&sys_time);

    printf("Waiting for the set time...\r\n");
    while (!compare_time(&when, local))
    {
        sys_time = time(NULL);
        local = localtime(&sys_time);
    }

    time_t ntp_time = get_ntp_time(HOST, PORT);
    int64_t ntp_time_proc = proces_time(&ntp_time);
    set_sys_time(&ntp_time_proc);
    print_times(&ntp_time_proc);
}

void cont_sync(void)
{
    printf("System clock is constantly syncing with NTP. Print \"stop\" to break:");

    while (1)
    {
        time_t ntp_time = get_ntp_time(HOST, PORT);
        int64_t ntp_time_proc = proces_time(&ntp_time);
        set_sys_time(&ntp_time_proc);

        char cmd[256] = {0};
        scanf("%s", cmd);

        if (strcmp(cmd, "stop") == 0)
        {
            break;
        }
    }
}

void print_diff(void)
{
    time_t ntp_time = get_ntp_time(HOST, PORT);
    int64_t ntp_time_proc = proces_time(&ntp_time);
    print_times(&ntp_time_proc);
}
