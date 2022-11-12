#include "./draw.h"

#include <iostream>
#include "var.h"

#include <thread>

GLfloat moveSpeed = 0.5;
int delay = 1000;

int input_main()
{
    while (true)
    {
        kmhDashboardValue = 20;
        rpmDashboardValue = 1000;

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        kmhDashboardValue = 20;
        rpmDashboardValue = 1000;

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        kmhDashboardValue = 40;
        rpmDashboardValue = 2000;

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        kmhDashboardValue = 60;
        rpmDashboardValue = 3000;

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        kmhDashboardValue = 80;
        rpmDashboardValue = 4000;

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        kmhDashboardValue = 100;
        rpmDashboardValue = 5000;

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    return 0;
}