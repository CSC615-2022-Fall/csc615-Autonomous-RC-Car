#ifndef SENSORDRIVER_H
#define SENSORDRIVER_H

#define SENSOR_TYPE_LINE 0
#define SENSOR_TYPE_ECHO 1

#define MAX_SENSORS 10

#define RUN_OFF 0
#define RUN_ON 1

#include <stdlib.h>
#include <stdio.h>

typedef struct Sensor {
    int sensorType;
    int gpio_line; // GPIO for Line sensor
    int gpio_echo; // GPIO for Echo sensor
    int gpio_trig; // GPIO for Echo sensor
    int data; // Contains the output of the sensors
} Sensor;

typedef struct SensorDriver {
    int num_of_sensors;
    int isRunning;
    Sensor** sensors;
} SensorDriver;

extern SensorDriver* _sensor_driver;

void init_sensor_driver();
void terminate_sensor_driver();
void start_sensors();

Sensor* new_line_sensor(int gpio_line);
Sensor* new_echo_sensor(int gpio_echo, int gpio_trig);

#endif