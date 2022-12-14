/**************************************************************
 * Class:  CSC-615-01 Fall 2022
 * Names: Christian Francisco, David Ye Luo, Marc Castro, Rafael Sunico
 * Student IDs: 920603057, 917051959, 921720147, 920261261
 * GitHub Name: csc615-term-project-DavidYeLuo
 * Group Name: Fried Pi
 * Project: Robot Car
 *
 * File: SensorDriver.h
 *
 * Description: A program that manages multiple sensors as an array.
 * It also treats uses the Sensor struct as a common interface for
 * echo sensors or line sensors.
 *
 **************************************************************/
#ifndef SENSORDRIVER_H
#define SENSORDRIVER_H

#include "MacroId/MacroDefinitions.h"
#include "MacroId/SensorData.h"
#include "ThreadHandler/ThreadSensor.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Internal Data
typedef struct SensorDriver {
  int isRunning;

  int num_of_sensors;       // current number of sensors
  int sensor_list_capacity; // Corresponds to how many sensors the driver can
                            // use

  Sensor **sensors;
  pthread_t **_threads;
  ThreadArgs **_thread_arguments;
} SensorDriver;

extern SensorDriver *_sensor_driver;

void init_sensor_driver(int max_sensors);
void terminate_sensor_driver();
void start_sensors();

Sensor *new_line_sensor(int gpio_line);
Sensor *new_echo_sensor(int gpio_echo, int gpio_trig);

#endif
