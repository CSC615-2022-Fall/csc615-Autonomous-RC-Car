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

#include "src/SensorDriver.h"
#include "src/MotorDriver.h"
#include "src/MacroId/SensorData.h"
#include "src/MacroId/MacroDefinitions.h"

// I2C Hat Address
#define I2C_HAT_ADDRESS (char) 0x40

// GPIO Pin Numbers
#define GPIO_LEFT_LINE_SENSOR 20 // Reflective sensor left
#define GPIO_RIGHT_LINE_SENSOR 21 // Reflective sensor right
#define GPIO_FRONT_ECHO_SENSOR_TRIG 19 // Front Echo Sensor Trigger
#define GPIO_FRONT_ECHO_SENSOR_ECHO 13 // Front Echo Sensor Trigger

// SensorDriver Config
#define MAX_NUM_OF_SENSORS 10

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

int running;

// sigint handler for cntl-c
void sigint(int sig) {
	running = RUN_OFF;
}

int main(int argc, char *argv[]) {
	// Data to use
	int* left_line_sensor;
	int* right_line_sensor;
    int* front_echo_sensor;

	// GPIO Init
	if (gpioInitialise() < 0) {
		fprintf(stderr, "pigpio initialisation failed\n");
		return 1;
	}

	// I2C, PWM, MOTOR HAT Init
	// init_motor_driver(I2C_HAT_ADDRESS, 100, 2);
	init_motor_driver(0x40, 100, 2); // Not sure if this fixes some bug
	// Add Motors
	add_motor_to_driver(100, PWMA, AIN1, AIN2);
	add_motor_to_driver(100, PWMB, BIN2, BIN1);
	// Sets up the initial direction
	set_motor_direction_forward(LEFT_MOTOR);
	set_motor_direction_forward(RIGHT_MOTOR);
	set_all_motors_to_stop();

    gpioSetMode(GPIO_LEFT_LINE_SENSOR, PI_INPUT);
    gpioSetMode(GPIO_RIGHT_LINE_SENSOR, PI_INPUT);
    gpioSetMode(GPIO_FRONT_ECHO_SENSOR_TRIG, PI_OUTPUT);
    gpioSetMode(GPIO_FRONT_ECHO_SENSOR_ECHO, PI_INPUT);

	// Init Sensors here
	init_sensor_driver(MAX_NUM_OF_SENSORS);

	// Add sensors
	// Left Line Sensor
	Sensor* currentSensor = new_line_sensor(GPIO_LEFT_LINE_SENSOR);
	left_line_sensor = &(currentSensor->data);
	// Right Line Sensor
	currentSensor = new_line_sensor(GPIO_RIGHT_LINE_SENSOR);
	right_line_sensor = &(currentSensor->data);
    // Front Echo Sensor
    currentSensor = new_echo_sensor(GPIO_FRONT_ECHO_SENSOR_ECHO, GPIO_FRONT_ECHO_SENSOR_TRIG);
    front_echo_sensor = &(currentSensor->data);
    
    
    // Start sensors
    start_sensors();

	signal(SIGINT, sigint);

	// BUTTON SIGNAL GOES HERE

	running = RUN_ON;
	while (running == RUN_ON) {
		// decision handling here

		

		// Sensor and Motor test
		// if (*left_line_sensor = ON_LINE) {
		// 	// Motor_Run(MOTORA, FORWARD, 100);
		// } else {
		// 	// Motor_Run(MOTORA, FORWARD, 0);
		// }

		// if (*left_line_sensor == ON_LINE) {
		// 	// Motor_Run(MOTORB, FORWARD, 100);
		// } else {
		// 	// Motor_Run(MOTORB, FORWARD, 0);
		// }
        // printf("left_line_sensor = %d\n", *left_line_sensor);
        // printf("right_line_sensor = %d\n", *right_line_sensor);
        if (*front_echo_sensor < 30) // 10 is just an arbitrary threshold for now
        {
            // This is just a sample
            // TODO: implement actual logic
            set_all_motors_to_stop();
            continue;
        }

        if (*left_line_sensor == ON_LINE) 
        {
            set_motor_speed(LEFT_MOTOR, 65);
        } else
        {
            set_motor_speed(LEFT_MOTOR, 40);
        }

        if (*right_line_sensor == ON_LINE) 
        {
            set_motor_speed(RIGHT_MOTOR, 65);
        } else
        {
            set_motor_speed(RIGHT_MOTOR, 40);
        }
	}
    
	// Cleanup
	set_all_motors_to_stop();
	terminate_sensor_driver();
	terminate_motor_driver();
	gpioTerminate();

	return 0;
}
