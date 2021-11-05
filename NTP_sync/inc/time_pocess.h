#pragma once

#include <time.h>
#include <stdint.h>

/**
 * @brief NTP packect structure
 * */

typedef struct
{
    uint8_t li_v_mode4; // Leap indicator 2 bits, Version number 3 bits, Mode 3 bits
    uint8_t stratum;    // Stratum level of the local clock
    uint8_t poll;       // Max . interval between successive messages
    uint8_t precision;  // Precision of the local clock

    uint32_t rootDelay;      // Total round trip delay time
    uint32_t rootDispersion; // Max error from primary clock source
    uint32_t refId;          // Reference clock identifier

    uint32_t refTm_s; // Reference time - stamp seconds
    uint32_t refTm_f; // Ref. time - stamp fraction of a second

    uint32_t origTm_s; // Originate time - stamp seconds
    uint32_t origTm_f; // Origin . time - stamp fraction of a second

    uint32_t rxTm_s; // Received time - stamp seconds
    uint32_t rxTm_f; // Received time - stamp fraction of a second

    uint32_t txTm_s; // Transmit time - stamp seconds which is

    uint32_t txTm_f; // Transmit time - stamp fraction of a second

} ntp_packet; // Totally 48 bytes

/**
 * @brief provide NTP time from the server
 * @param host - host address
 * @param port - port
 * @return 32 bits : Reference time - stamp seconds.
 * */
uint32_t get_ntp_time(const char *host, uint16_t port);

/**
 * @brief set system time ti the dedicated value, sudo rights required
 * @param set_time - time to set as the time_t structure
 * */
void set_sys_time(const time_t *set_time);

/**
 * @brief handels the error using global variable errno. Display error and terminate the service.
 * @param error - Text to print with the errno.
 * */
void error_handling(const char *error);
