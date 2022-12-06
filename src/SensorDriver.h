#ifndef SENSORDRIVER_H
#define SENSORDRIVER_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "MacroId/SensorData.h"
#include "MacroId/MacroDefinitions.h"
#include "ThreadHandler/ThreadSensor.h"

// Internal Data
typedef struct SensorDriver {
    int isRunning;

    int num_of_sensors; // current number of sensors
    int sensor_list_capacity; // Corresponds to how many sensors the driver can use

    Sensor** sensors;
    pthread_t** _threads;
    ThreadArgs** _thread_arguments;
} SensorDriver;

extern SensorDriver* _sensor_driver;

void init_sensor_driver(int max_sensors);
void terminate_sensor_driver();
void start_sensors();

Sensor* new_line_sensor(int gpio_line);
Sensor* new_echo_sensor(int gpio_echo, int gpio_trig);

#endif