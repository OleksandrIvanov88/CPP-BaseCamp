# Linux Time Sync 

A small service that evaluates the accuracy of your computer's clock. The service synchronizes the system time using NTP, turn on continuously synchronization turn on synchronization for a predetermined time (second, minute, hour), request the time from NTP and read the discrepancy with the system time. 

### Build and run
- make
- sudo ./main

### User interface 
- `sync`       - run single sync
- `set_time`   - set time for the next single sync
- `cont_sync`  - run continuously sync
- `print_diff` - display difference of NTP and system time
- `exit`       - stop the service
