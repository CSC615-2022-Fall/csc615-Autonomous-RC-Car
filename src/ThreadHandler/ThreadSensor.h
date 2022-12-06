#ifndef THREADSENSOR_H
#define THREADSENSOR_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// Not a fan of using relative path but don't want to use too much time on this
#include "../MacroId/SensorData.h" 
#include "../MacroId/MacroDefinitions.h"

/*
* The first data should be the pointer to isRunning in the SensorDriver
*   -> Should be of type int*
* The second data should be information of sensor
*   -> Should be struct Sensor
*/
void* thread_collect_echo_sensor_data(void* threadArgs);
void* thread_collect_line_sensor_data(void* threadArgs);

#endif