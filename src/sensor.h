/**************************************************************
 * Class:  CSC-615-01 Fall 2022
 * Names: Christian Francisco, David Ye Luo, Marc Castro, Rafael Sunico
 * Student IDs: 920603057, 917051959, 921720147, 920261261
 * GitHub Name: csc615-term-project-DavidYeLuo
 * Group Name: Fried Pi
 * Project: Robot Car
 *
 * File: sensor.h
 *
 * Description: Sensor handler API definitions
 *
 **************************************************************/
#ifndef SENSOR_H
#define SENSOR_H
#include <stdio.h>
#include <pigpio.h>
#include <stdlib.h>
#include <pthread.h>

// Starts a thread that continuously reads from the given gpio pin.
// Expects gpio pin to be connected to a simple 0-1 input sensor, and 
// must already be initialized with pigpio.
// Input from sensor is loaded into the given int pointer.
// @param gpioPin the gpio pin number connected to the sensor
// @param input int pointer where input from sensor will be loaded into
// @param id unique int id for thread creation
// @return 0 for success, otherwise for fail
int setupSimpleSensor(int gpioPin, int* input, pthread_t id);

// Starts a thread that continuously sends a pulse to the given trigger 
// gpio pin, reads from the given echo gpio pin, and calculates the distance 
// between the sensor and any object hit by the sonar.
// Expects trigger gpio pin to be connected to a sonar sensor trigger output, and 
// must already be initialized with pigpio.
// Expects echo gpio pin to be connected to a sonar sensor echo input, and 
// must already be initialized with pigpio.
// Distance calculated is loaded into the given int pointer in cm.
// @param triggerGpioPin the gpio pin number connected to the sonar sensor trigger output
// @param echoGpioPin the gpio pin number connected to the sonar sensor echo input
// @param input int pointer where input from sensor will be loaded into
// @param id unique int id for thread creation
// @return 0 for success, otherwise for fail
int setupSonarSensor(int triggerGpioPin, int echoGpioPin, int* input, pthread_t id);

// Stops all sensor threads
void cleanupSensors();

#endif