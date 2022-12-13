#ifndef SENSORDATA_H
#define SENSORDATA_H

// User Provided Data
typedef struct Sensor {
  int sensorType;

  int gpio_line; // GPIO for Line sensor
  int gpio_echo; // GPIO for Echo sensor
  int gpio_trig; // GPIO for Echo sensor

  int data; // Contains the output of the sensors
} Sensor;

// Used to pass sensor data to pass to threads
typedef struct ThreadArgs {
  int *isRunning;
  Sensor *sensor;
} ThreadArgs;

#endif
