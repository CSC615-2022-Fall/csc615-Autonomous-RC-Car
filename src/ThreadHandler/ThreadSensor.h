/**************************************************************
 * Class:  CSC-615-01 Fall 2022
 * Names: Christian Francisco, David Ye Luo, Marc Castro, Rafael Sunico
 * Student IDs: 920603057, 917051959, 921720147, 920261261
 * GitHub Name: csc615-term-project-DavidYeLuo
 * Group Name: Fried Pi
 * Project: Robot Car
 *
 * File: ThreadSensor.h
 *
 * Description: Thread function implmentation to gather data from sensors.
 * These functions will keep gathering data and placing them in Sensor->data
 *
 **************************************************************/
#ifndef THREADSENSOR_H
#define THREADSENSOR_H

#include <pigpio.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Not a fan of using relative path but don't want to use too much time on this
#include "../MacroId/MacroDefinitions.h"
#include "../MacroId/SensorData.h"

#define NANO_PER_SEC 1000000000.0

/*
 * Thread Args is a struct ThreadArgs
 * Sensor contains isRunning in the SensorDriver
 *   -> Should be of type int*
 * It also contains the information of Sensor
 *   -> Should be struct Sensor
 *   NOTE: this is the same structure that
 *   the sensor->data contains the sensor outputs.
 */

void *thread_collect_echo_sensor_data(void *threadArgs);
void *thread_collect_line_sensor_data(void *threadArgs);

#endif
