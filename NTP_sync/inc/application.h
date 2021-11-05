#pragma once

/**
 * @brief run singal synchronization of system time with NTP server time
 * */
void sync(void);

/**
 * @brief set time for the singal synchronization of system time with NTP server time
 * */
void set_time(void);

/**
 * @brief run continuously synchronization of system time with NTP server time
 * */
void cont_sync(void);

/**
 * @brief display the difference beetween system time and NTP server time
 * */
void print_diff(void);
