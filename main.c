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

#include <pigpio.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "src/sensor.h"
#include "src/External_Libraries/MotorDriver.h"

// GPIO Pin Numbers
#define REFL_L 20 // Reflective sensor left
#define REFL_R 21 // Reflective sensor right

// Flag to tell loops when to stop
int running;

// sigint handler for cntl-c
void sigint(int sig) {
	running = 0;
}

int main(int argc, char *argv[]) {
	// GPIO Init
	if (gpioInitialise() < 0) {
		fprintf(stderr, "pigpio initialisation failed\n");
		return 1;
	}

	// I2C, PWM, MOTOR HAT Init
	Motor_Init();

	// Left Reflective Sensor Init
	// Pointer for input init
	int reflLeftInput = 0;
	int* reflLeftInputPtr = &reflLeftInput;
	setupSimpleSensor(REFL_L, reflLeftInputPtr); // setup thread

	// Right Reflective Sensor Init
	// Pointer for input init
	int reflRightInput = 0;
	int* reflRightInputPtr = &reflRightInput;
	setupSimpleSensor(REFL_R, reflRightInputPtr); // setup thread

	// flag init
	running = 1;

	signal(SIGINT, sigint);

	// BUTTON SIGNAL GOES HERE

	while (running) {
		// decision handling here

		// Sensor and Motor test
		if (*reflLeftInputPtr == 1) {
			Motor_Run(MOTORA, FORWARD, 100);
		} else {
			Motor_Run(MOTORA, FORWARD, 0);
		}

		if (*reflRightInputPtr == 1) {
			Motor_Run(MOTORB, FORWARD, 100);
		} else {
			Motor_Run(MOTORB, FORWARD, 0);
		}

		// break and set running = false when done
	}

	// Cleanup
	gpioTerminate();
	cleanupSensors();

	return 0;
}
