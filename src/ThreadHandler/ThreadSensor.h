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
 * The first data should be the pointer to isRunning in the SensorDriver
 *   -> Should be of type int*
 * The second data should be information of sensor
 *   -> Should be struct Sensor
 */
void *thread_collect_echo_sensor_data(void *threadArgs);
void *thread_collect_line_sensor_data(void *threadArgs);

#endif
