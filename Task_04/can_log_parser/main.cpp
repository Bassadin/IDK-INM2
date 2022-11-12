// --------------------------------------------------------------------------
// CanParser - Aufgabe 5
//
// Bearbeitet von:
//     Vieth, 270401
//     Hodapp, 271488
//
// --------------------------------------------------------------------------

// Lokale Header
#include <stdio.h>		// printf(), perror()
#include <stdlib.h>		// exit()
#include <unistd.h>		// write()
#include <fcntl.h>		// O_RDONLY
#include <linux/can.h>	// struct can_frame
#include "../lib/can.h" // can_open()
#include <chrono>

#include <iostream>
#include <thread>
// Feste Definitionen für dieses Programm
#define CAN_INTERFACE "vcan0"
#define LOG_FILE "../logs/20121011_bmw_stopngo_5min.raw"

// Diese Datenstruktur repräsentiert einen einzelnen Eintrag in der Log-Datei.
struct log_entry
{
	struct timeval timeval;
	struct can_frame can_frame;
};

int main(void)
{
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	int fd_can;
	fd_can = can_open(CAN_INTERFACE);
	int fd_log = open(LOG_FILE, O_RDONLY);

	__suseconds_t time = 0;
	while (true)
	{
		// Einzelnen Log-Eintrag auslesen.
		struct log_entry entry;
		int r = read(fd_log, &entry, sizeof(struct log_entry));
		// struct can_frame frame;
		if (r == 0)
		{
			break;
		}
		__suseconds_t time_delta = 0;
		if (time != 0)
		{
			time_delta = entry.timeval.tv_usec - time;
		}
		time = entry.timeval.tv_usec;
		std::cout << time << ": " << &entry.can_frame.data << std::endl;
		write(fd_can, &entry.can_frame, sizeof(struct can_frame));
		std::this_thread::sleep_for(std::chrono::microseconds(time_delta));
		std::cout << time_delta << std::endl;
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Execution time = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;

	return 0;
}
