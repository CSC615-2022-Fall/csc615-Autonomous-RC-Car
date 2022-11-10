/**************************************************************
 * Class:  CSC-615-01 Fall 2022
 * Names: Christian Francisco, David Ye Luo, Marc Castro, Rafael Sunico
 * Student IDs: 920603057, 917051959, 921720147, 920261261
 * GitHub Name: csc615-term-project-DavidYeLuo
 * Group Name: Fried Pi
 * Project: Robot Car
 *
 * File: sensor.c
 *
 * Description: Sensor handler
 *
 **************************************************************/

#include <pthread.h>

#include "sensor.h"

// Flag to tell sensor loops when to stop
int sensorsRunning = 1;

// TODO: array to hold thread ids

// Get input from simple sensor thread func
void *handleSimpleSensor(void *pthread_args) {
    // get (int gpioPin, int* input) from pthread_args
	while (sensorsRunning) {
		// load input from gpio pin into int* input
	}
}

// Get input, and calculate distance from sonar sensor thread func
void *handleSonarSensor(void *pthread_args) {
    // get (int triggerGpioPin, int echoGpioPin, int* input) from pthread_args
	while (sensorsRunning) {
        // calculate distance in cm
		// load distance into int* input
	}
}

int setupSimpleSensor(int gpioPin, int* input) {

    // start thread
    // store thread id in array

    return 0;
}

int setupSonarSensor(int triggerGpioPin, int echoGpioPin, int* input) {

    // start thread
    // store thread id in array

    return 0;
}

void cleanupSensors() {
    sensorsRunning = 0;
    // TODO: call pthread_join on every thread id
}
