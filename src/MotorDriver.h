#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H
#include "stdlib.h"
#include "External_Libraries/DEV_Config.h"
#include "External_Libraries/PCA9685.h"
#include "MacroId/MacroDefinitions.h"
#include "MacroId/MotorData.h" // <-- Contains motor data

typedef struct MotorDriver
{
    int num_of_motors;
    int motor_capacity;
    Motor** motors;
} MotorDriver;

extern MotorDriver* _motor_driver;

// Init and terminate
void init_motor_driver(char i2c_address, int pwm_freq, int max_num_of_motors);
void terminate_motor_driver();

// Adding motor
void add_motor_to_driver(int base_speed, int pwm_pin, int positive_motor_pin, int negative_motor_pin);

// Controls
void set_motor_direction(int index, int direction);
void set_motor_speed(int index, int speed_percentage);
void set_all_motor_speed(int index, int speed_percentage);
void set_all_motors_to_stop();

#endif