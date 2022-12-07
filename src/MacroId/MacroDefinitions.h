#ifndef MACRODEFINITIONS_H
#define MACRODEFINITIONS_H

// Used to specify what kind of sensor to use
#define SENSOR_TYPE_LINE 0
#define SENSOR_TYPE_ECHO 1

// Used to tell if the Sensor Driver is running
// Data for _sensor_driver->isRunning
#define RUN_OFF 0
#define RUN_ON 1

// Line sensor
// ON_LINE is 0 because the road is dark color.
// Dark object tend to absorb light.
// This means that if we are not recieving a signal,
// then that means we are on track.
// TLDR:
// 0 for dark object
// 1 for reflective object
#define ON_LINE 0
#define OFF_LINE 1 

// Motor
#define FORWARD 1
#define BACKWARD 0
// Below are used for config settings
// In case that motor is spinning the wrong way, we can change it
#define NORMAL_CONTROL 0
#define REVERSE_CONTROL 1

#endif
