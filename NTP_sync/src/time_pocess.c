#include "time_pocess.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

void error_handling(const char *error)
{
    perror(error);
    exit(EXIT_FAILURE);
}

uint32_t get_ntp_time(const char *host, uint16_t port)
{
    if (NULL == host)
    {
        errno = EFAULT;
        error_handling("ERROR!!!NULL pointer passed to the function get_ntp_time");
    }
    int socketdr = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketdr < 0)
    {
        error_handling("ERROR!!!Opening socket");
    }

    struct hostent *server = gethostbyname(host);
    if (server == NULL)
    {
        error_handling("ERROR!!!No such host found");
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(host);
    server_addr.sin_port = htons(port);

    if (connect(socketdr, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        error_handling("ERROR!!!No connecting");
    }

    ntp_packet packet;
    memset(&packet, 0, sizeof(packet));
    packet.li_v_mode4 = 0b00011011; //// li =0 v=3 mode4 =3
    int res = send(socketdr, &packet, sizeof(packet), MSG_NOSIGNAL);

    if (res < 0)
    {
        error_handling("ERROR!!!Writing socket");
    }

    res = recv(socketdr, &packet, sizeof(packet), MSG_NOSIGNAL);

    if (res < 0)
    {
        error_handling("ERROR!!!Reading from socket");
    }

    shutdown(socketdr, SHUT_RDWR);

    close(socketdr);

    return packet.txTm_s;
}

void set_sys_time(const time_t *set_time)
{
    if (NULL == set_time)
    {
        errno = EFAULT;
        error_handling("ERROR!!!NULL pointer passed to the function set_sys_time");
    }
    struct timespec time_set = {*set_time, 0};
    if (-1 == clock_settime(CLOCK_REALTIME, &time_set))
    {
        error_handling("ERROR!!!NTP and Sys time synchronization");
    }
}
