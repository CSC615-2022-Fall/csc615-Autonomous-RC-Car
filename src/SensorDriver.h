#ifndef SENSORDRIVER_H
#define SENSORDRIVER_H

#define SENSOR_TYPE_LINE 0
#define SENSOR_TYPE_ECHO 1

#define RUN_OFF 0
#define RUN_ON 1

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct Sensor {
    int sensorType;

    int gpio_line; // GPIO for Line sensor
    int gpio_echo; // GPIO for Echo sensor
    int gpio_trig; // GPIO for Echo sensor

    int data; // Contains the output of the sensors
} Sensor;

typedef struct SensorDriver {
    int isRunning;

    int num_of_sensors; // current number of sensors
    int sensor_list_capacity; // Corresponds to how many sensors the driver can use

    Sensor** sensors;
    pthread_t** _threads;
} SensorDriver;

extern SensorDriver* _sensor_driver;

void init_sensor_driver(int max_sensors);
void terminate_sensor_driver();
void start_sensors();

Sensor* new_line_sensor(int gpio_line);
Sensor* new_echo_sensor(int gpio_echo, int gpio_trig);

#endif