/**************************************************************
 * Class:  CSC-615-01 Fall 2022
 * Names: Christian Francisco, David Ye Luo, Marc Castro, Rafael Sunico
 * Student IDs: 920603057, 917051959, 921720147, 920261261
 * GitHub Name: csc615-term-project-DavidYeLuo
 * Group Name: Fried Pi
 * Project: Robot Car
 *
 * File: main.c
 *
 * Description: 
 *
 **************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pigpio.h>

#include "sensor.h"

// Flag to tell loops when to stop
int running;

// sigint handler for cntl-c
void sigint(int sig) {
	running = 0;
}

int main(int argc, char *argv[])
{
    // GPIO Init
    if (gpioInitialise() < 0) {
        fprintf(stderr, "pigpio initialisation failed\n");
        return 1;
    }

    // flag init
	running = 1;

    signal(SIGINT, sigint);

    while (running) {
        // decision handling here

        // break and set running = false when done
    }

    // Cleanup
    gpioTerminate();
    cleanupSensors();

    return 0;
}
