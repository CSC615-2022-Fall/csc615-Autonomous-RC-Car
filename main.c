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
#include <unistd.h>

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
	Motor_Run(MOTORA, FORWARD, 0);
    Motor_Run(MOTORB, FORWARD, 0);
	gpioTerminate();
	cleanupSensors();
}

int main(int argc, char *argv[]) {
	// GPIO Init
	if (gpioInitialise() < 0) {
		fprintf(stderr, "pigpio initialisation failed\n");
		return 1;
	}

	// I2C, PWM, MOTOR HAT Init
	Motor_Init();

    gpioSetMode(REFL_L, PI_INPUT);
    gpioSetMode(REFL_R, PI_INPUT);

	// Left Reflective Sensor Init
	// Pointer for input init
	int reflLeftInput = 0;
	int* reflLeftInputPtr = &reflLeftInput;
	setupSimpleSensor(REFL_L, reflLeftInputPtr); // setup and start thread

	// Right Reflective Sensor Init
	// Pointer for input init
	int reflRightInput = 0;
	int* reflRightInputPtr = &reflRightInput;
	setupSimpleSensor(REFL_R, reflRightInputPtr); // setup and start thread
    

	// flag init
	running = 1;

	signal(SIGINT, sigint);

	// BUTTON SIGNAL GOES HERE

	while (running) {
		printf("Hi\n");
		// decision handling here

		// MOTORA = Left Motor
		// MOTORB = Right Motor

		// Follow line test
		// Uses two reflective sensors at the front, 1 for each side, infront of the wheels
		// Car steers by powering 1 side of motor(s) and stopping/reversing the other
		// Follows the line by steering towards the the sensor that sees black, meaning
		// if a sensor sees black, stop/reverse the corresponding wheel, otherwise continue moving forwards
		if (*reflLeftInputPtr == 1) { // 1 = ON BLACK
			// STOP
			Motor_Run(MOTORA, FORWARD, 0);
			// TODO: Test with reversing if stopping is not enough
			// TODO: Test with slowing down if stopping is too much
			// TODO: Test with incrementally slowing down/reversing if none of the above work
		} else { // 0 = ON WHITE
			// CONTINUE
			Motor_Run(MOTORA, FORWARD, 100);
		}

		if (*reflRightInputPtr == 1) { // 1 = ON BLACK
			// STOP
			Motor_Run(MOTORB, FORWARD, 0);
		} else { // 0 = ON WHITE
			// CONTINUE
			Motor_Run(MOTORB, FORWARD, 100);
		}

		// Obstruction test
		/*
			if front echo sensor sees object AND not running this subroutine then
				full stop
				90 degree turn left
				move forwards slightly
				repeat move forwards at 30% until right echo sensor does not see object
				move forwards slightly
				90 degree turn right
				repeat move forwards at 50% until right echo sensor sees object
				repeat move forwards at 30% until right echo sensor does not see object
				move forwards slightly
				90 degree turn right
				repeat move forwards at 30% until left reflective sensor see black
				stop left
				repeat move right forwards at 20% until right sensor sees black, if not on black already
				repeat move right forwards at 20% until right sensor sees white
			done
			NOTE: This strat relies on if the car can turn with a pivot under a specific front wheel, by setting one side to stop, and one side to move. 
		*/

	}

	// STOP
	Motor_Run(MOTORA, FORWARD, 0);
    Motor_Run(MOTORB, FORWARD, 0);

	// Cleanup
	gpioTerminate();
	cleanupSensors();

	return 0;
}
