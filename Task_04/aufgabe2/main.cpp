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

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* drawingThread(void* arg)
{
    // detach the current thread
    // from the calling thread
    pthread_detach(pthread_self());
  
    draw_main();
  
    // exit the current thread
    pthread_exit(NULL);
}
  
void fun()
{
    pthread_t ptid;
  
    // Creating a new thread
    pthread_create(&ptid, NULL, &drawingThread, NULL);
  
  
    // Waiting for the created thread to terminate
    // pthread_join(ptid, NULL);
  
    pthread_exit(NULL);
}
  
int main()
{
    fun();
    return 0;
}