#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H
#include "External_Libraries/DEV_Config.h"
#include "External_Libraries/PCA9685.h"
#include "MacroId/MacroDefinitions.h"
#include "MacroId/MotorData.h" // <-- Contains motor data
#include "stdlib.h"

typedef struct MotorDriver {
  int num_of_motors;
  int motor_capacity;
  Motor **motors;
} MotorDriver;

extern MotorDriver *_motor_driver;

// Init and terminate
void init_motor_driver(char i2c_address, UWORD pwm_freq, int max_num_of_motors);
void terminate_motor_driver();

// Adding motor
void add_motor_to_driver(UWORD base_speed, UBYTE pwm_pin,
                         UBYTE positive_motor_pin, UBYTE negative_motor_pin);

// Controls
void set_motor_direction_forward(int index);
void set_motor_direction_backward(int index);
void set_motor_speed(int index, UWORD speed);
void set_all_motors_speed(UWORD speed);
void set_all_motors_to_stop();

#endif
