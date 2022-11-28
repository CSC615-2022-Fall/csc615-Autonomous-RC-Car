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

//creating a struct to pull and store distance
//read by simple sensor
typedef struct simpleData {
    int gpioNum;
    int *input;
} simpleData;

typedef struct sonarData {
    int triggerPin;
    int echoPin;
    int *input;
} sonarData;

// Flag to tell sensor loops when to stop
int sensorsRunning = 1;

// TODO: array to hold thread ids
int simpleCount = 0;
int sonarCount = 0;
pthread_t simpleThreads[4];
pthread_t sonarThreads[3];

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
    simpleData *args = pthread_args;
	while (sensorsRunning) {
        // calculate distance in cm

		// load distance into int* input

	}
}

int setupSimpleSensor(int gpioPin, int* input, pthread_t id) {
    struct simpleData *args = malloc(sizeof(simpleData));
    args->gpioNum = gpioPin;
    args->input = input;
    // start thread
    pthread_create(&id, NULL, handleSimpleSensor, &args);
    // store thread id in array
    simpleThreads[simpleCount] = id;
    simpleCount++;

    return 0;
}

int setupSonarSensor(int triggerGpioPin, int echoGpioPin, int* input, pthread_t id) {
    struct sonarData *args = malloc(sizeof(sonarData));
    args->echoPin = echoGpioPin;
    args->triggerPin = triggerGpioPin;
    args->input = input;
    // start thread
    pthread_create(&id, NULL, handleSonarSensor, &args);
    sonarThreads[sonarCount] = id;
    sonarCount++;
    // store thread id in array


    return 0;
}

void cleanupSensors() {
    sensorsRunning = 0;
    // TODO: call pthread_join on every thread id
    for(int i = 0; i <= simpleCount; i++) {
        pthread_join(simpleThreads[i], NULL);
    }

    for(int i = 0; i <= sonarCount; i++) {
        pthread_join(sonarThreads[i], NULL);
    }
}
