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

#include "sensor.h"

#include <pigpio.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NANO_PER_SEC 1000000000.0

// creating a struct to pull and store distance
// read by simple sensor
typedef struct simpleData {
    int gpioPin;
    int *input;
} simpleData;

typedef struct sonarData {
    int triggerPin;
    int echoPin;
    int *input;
} sonarData;

// Flag to tell sensor loops when to stop
int sensorsRunning = 1;

// arrays to hold thread ids
int simpleIdx = 0;
int sonarIdx = 0;
pthread_t simpleThreads[10];  // max 10 threads
pthread_t sonarThreads[10];   // max 10 threads

// SENSOR HANDLER FUNCTIONS

// Get input from simple sensor thread func
void *handleSimpleSensor(void *pthread_args) {
    // get (int gpioPin, int* input) from pthread_args
    simpleData *args = pthread_args;
    int gpioPin = args->gpioPin;
    int *input = args->input;
    while (sensorsRunning) {
        // load input from gpio pin into int* input
        *input = gpioRead(gpioPin);
        time_sleep(0.5);
    }
    pthread_exit(NULL);
}

// Get input, and calculate distance from sonar sensor thread func
void *handleSonarSensor(void *pthread_args) {
    // get (int triggerGpioPin, int echoGpioPin, int* input) from pthread_args
    sonarData *args = pthread_args;
    int triggerPin = args->triggerPin;
    int echoPin = args->echoPin;
    int *input = args->input;

    // Initialise timers
    struct timespec startTime;
    struct timespec endTime;

    while (sensorsRunning) {
        // Send trigger pulse, 1ms duration, HIGH value
        if (gpioTrigger(triggerPin, 1, 1) != 0) {
            fprintf(stderr, "pigpio trigger failed for pin:%d\n", triggerPin);
            pthread_exit(NULL);
        }

        // keep setting start timer until ECHO doesn't read 0
        while (gpioRead(echoPin) == 0) {
            clock_gettime(CLOCK_REALTIME, &startTime);
        }

        // keep setting end timer until ECHO doesn't read 1
        while (gpioRead(echoPin) == 1) {
            clock_gettime(CLOCK_REALTIME, &endTime);
        }

        // calulcate elapsed time
        double startSec = startTime.tv_sec + startTime.tv_nsec / NANO_PER_SEC;
        double endSec = endTime.tv_sec + endTime.tv_nsec / NANO_PER_SEC;
        double elapsedSec = endSec - startSec;

        // calculate distance in cm
        // speed of sound in air: 34300 cm/s, divide by 2 for roundtrip
        double distance = (elapsedSec * 34300) / 2;

        // load distance into int* input
        *input = (int)distance;
    }
}

// PUBLIC FUNCTIONS

int setupSimpleSensor(int gpioPin, int *input) {
    if (simpleIdx >= 9) return 1;  // max simple sensor threads reached

    // construct args
    struct simpleData *args = malloc(sizeof(simpleData));
    args->gpioPin = gpioPin;
    args->input = input;
    // start thread
    pthread_t id = simpleIdx;  // index used as pthread id
    pthread_create(&id, NULL, handleSimpleSensor, args);
    // store thread id in array
    simpleThreads[simpleIdx] = id;
    simpleIdx++;  // increment to next slot

    return 0;
}

int setupSonarSensor(int triggerGpioPin, int echoGpioPin, int *input) {
    if (sonarIdx >= 9) return 1;  // max simple sensor threads reached

    // construct args
    struct sonarData *args = malloc(sizeof(sonarData));
    args->echoPin = echoGpioPin;
    args->triggerPin = triggerGpioPin;
    args->input = input;
    // start thread
    pthread_t id = sonarIdx;  // index used as pthread id
    pthread_create(&id, NULL, handleSonarSensor, args);
    // store thread id in array
    sonarThreads[sonarIdx] = id;
    sonarIdx++;  // increment to next slot

    return 0;
}

void cleanupSensors() {
    // tell all threads to stop
    sensorsRunning = 0;
    // call pthread_join on every thread id
    // wait for all threads to finish
    for (int i = 0; i <= simpleIdx; i++) {
        pthread_join(simpleThreads[i], NULL);
    }

    for (int i = 0; i <= sonarIdx; i++) {
        pthread_join(sonarThreads[i], NULL);
    }
}
