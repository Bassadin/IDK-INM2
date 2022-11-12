#include "./draw.h"
#include <iostream>
#include "var.h"
#include <thread>

#include <linux/can.h>  // struct can_frame
#include "../lib/can.h" // can_open()
#include <fcntl.h>      // O_RDONLY
#include <unistd.h>     // write()

#include <cstring>

#define CAN_INTERFACE "vcan0"

int delay = 1000;

int input_main()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    kmhDashboardValue = 20;
    rpmDashboardValue = 1000;

    int fd_can = can_open(CAN_INTERFACE);

    while (true)
    {
        // Einzelnen Log-Eintrag auslesen.
        struct can_frame entry;
        int r = read(fd_can, &entry, sizeof(struct can_frame));

        if (r <= 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        else
        {
            // int value;
            // memcpy(&value, entry.data, sizeof(int));

            std::cout << entry.data << std::endl;

            // Daten könnten hier nun an draw.cpp "gesendet" werden, sie sind jedoch unlesbar, da Binärformat
            // So könnten sie aktualisiert werden
            // kmhDashboardValue = x;
            // rpmDashboardValue = y;

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }

    return 0;
}