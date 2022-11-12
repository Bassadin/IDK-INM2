// --------------------------------------------------------------------------
// DashBoard - Aufgabe 1
//
// Bearbeitet von:
//     Bastian Hodapp, 271488
//     Aljosha Vieth, 271401
//
// --------------------------------------------------------------------------

// Header
#include "./draw.h"
#include "./input.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t kmhLock;
pthread_mutex_t rpmLock;

void *drawingThread(void *arg)
{
	// detach the current thread
	// from the calling thread
	pthread_detach(pthread_self());

	draw_main();

	// exit the current thread
	pthread_exit(NULL);
}

void *inputThread(void *arg)
{
	// detach the current thread
	// from the calling thread
	pthread_detach(pthread_self());

	input_main();

	// exit the current thread
	pthread_exit(NULL);
}

void fun()
{
	pthread_t ptid_drawing;
	pthread_t ptid_input;

	// Creating a new thread
	pthread_create(&ptid_drawing, NULL, &drawingThread, NULL);
	pthread_create(&ptid_input, NULL, &inputThread, NULL);

	// Waiting for the created thread to terminate
	// pthread_join(ptid, NULL);

	pthread_exit(NULL);
}

int main()
{
	fun();
	return 0;
}