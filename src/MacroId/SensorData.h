/**************************************************************
 * Class:  CSC-615-01 Fall 2022
 * Names: Christian Francisco, David Ye Luo, Marc Castro, Rafael Sunico
 * Student IDs: 920603057, 917051959, 921720147, 920261261
 * GitHub Name: csc615-term-project-DavidYeLuo
 * Group Name: Fried Pi
 * Project: Robot Car
 *
 * File: SensorData.h
 *
 * Description: Contains two structures that are used for storing data like
 * an object.
 * The idea of the Sensor structure is to treat echo and line sensors similar.
 * Meaning that sensor->data is the output of the sensors even though they use
 * different pins.
 *
 * ThreadArgs is designed so that we can pass in more information to thread
 *functions. Struct sensor is needed in ThreadArgs because it needs to know the
 *type, pins, and where to output the result. isRunning is a data that is used
 *to tell the thread functions to stop which comes from the SensorDriver.
 *
 **************************************************************/
#ifndef SENSORDATA_H
#define SENSORDATA_H

// User Provided Data
typedef struct Sensor {
  int sensorType; // Check for MacroDefinition.h

  int gpio_line; // GPIO for Line sensor
  int gpio_echo; // GPIO for Echo sensor
  int gpio_trig; // GPIO for Echo sensor

  int data; // Contains the output of the sensors
} Sensor;

// Used to pass sensor data to pass to threads
typedef struct ThreadArgs {
  int *isRunning; // Flag to turn off the thread functions
  Sensor *sensor; // Sensor Information
} ThreadArgs;

#endif
