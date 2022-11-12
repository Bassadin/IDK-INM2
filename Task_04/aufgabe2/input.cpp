#include "./draw.h"

#include <iostream>
#include "var.h"

#include <thread>

GLfloat moveSpeed = 0.5;

int input_main()
{
    kmhDashboardValue = 50;

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    kmhDashboardValue = 120;
    rpmDashboardValue = 4000;

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    kmhDashboardValue = 30;
    rpmDashboardValue = 6000;

    return 0;
}