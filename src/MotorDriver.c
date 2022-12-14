/**************************************************************
 * Class:  CSC-615-01 Fall 2022
 * Names: Christian Francisco, David Ye Luo, Marc Castro, Rafael Sunico
 * Student IDs: 920603057, 917051959, 921720147, 920261261
 * GitHub Name: csc615-term-project-DavidYeLuo
 * Group Name: Fried Pi
 * Project: Robot Car
 *
 * File: MotorDriver.c
 *
 * Description: A program that handles multiple motors in as an array list.
 * It interfaces with the WaveShare PCA9685 to do the actual moving.
 * This program stores information such as the pwm_pin and pin polarities so
 * that the user don't need to specifiy them when using it.
 *
 **************************************************************/
#include "MotorDriver.h"

MotorDriver *_motor_driver;

/**
 * Initializes the motor driver
 *
 * Choose the i2c_address to use
 * Choose the pwm_freq
 * Specify the limit of motors
 */
void init_motor_driver(char i2c_address, UWORD pwm_freq,
                       int max_num_of_motors) {
  if (max_num_of_motors < 1) {
    printf("Warning: max_num_of_motor is less than 1\n");
    return;
  }
  _motor_driver = malloc(sizeof(MotorDriver));
  PCA9685_Init(
      i2c_address); // TODO: Test this later because main is passing an int
  PCA9685_SetPWMFreq(pwm_freq);
  _motor_driver->num_of_motors = 0;
  _motor_driver->motor_capacity = max_num_of_motors;
  _motor_driver->motors = malloc(sizeof(Motor) * max_num_of_motors);
}

/**
 * Terminate program
 * Deallocates resources
 */
void terminate_motor_driver() {
  Motor *current_motor;
  for (int i = 0; i < _motor_driver->num_of_motors; i++) {
    current_motor = _motor_driver->motors[i];

    // Stop it from driving
    PCA9685_SetPwmDutyCycle(current_motor->pwm_pin, 0);

    free(current_motor);
    _motor_driver->motors[i] = NULL;
  }
  free(_motor_driver->motors);
  free(_motor_driver);
}

/**
 * Adds a motor to the driver
 *
 * Specify the base_speed
 * Specify pwm_pin - PWMA or PWMB
 * Specify which pin is positive/negative
 */
void add_motor_to_driver(UWORD base_speed, UBYTE pwm_pin,
                         UBYTE positive_motor_pin, UBYTE negative_motor_pin) {
  int index = _motor_driver->num_of_motors;
  if (index >= _motor_driver->motor_capacity) {
    printf("Add motor failed. Tried to add more than the capacity.\n");
  }
  // Create the driver
  Motor *current_motor = malloc(sizeof(Motor));
  current_motor->pwm_pin = pwm_pin;
  current_motor->base_speed = base_speed;
  current_motor->positive_pole = positive_motor_pin;
  current_motor->negative_pole = negative_motor_pin;

  // Add the driver
  _motor_driver->motors[index] = current_motor;
  _motor_driver->num_of_motors++; // Increment counter
}

/**
 * Set the motor for a specific motor direction to forward.
 */
void set_motor_direction_forward(int index) {
  Motor *current_motor = _motor_driver->motors[index];
  PCA9685_SetLevel(current_motor->positive_pole, 1);
  PCA9685_SetLevel(current_motor->negative_pole, 0);
}

/**
 * Set the motor for a specific motor direction to backward.
 */
void set_motor_direction_backward(int index) {
  Motor *current_motor = _motor_driver->motors[index];
  PCA9685_SetLevel(current_motor->positive_pole, 0);
  PCA9685_SetLevel(current_motor->negative_pole, 1);
}

/**
 * Set the motor speed for a single motor given the index
 */
void set_motor_speed(int index, UWORD speed) {
  PCA9685_SetPwmDutyCycle(_motor_driver->motors[index]->pwm_pin, speed);
}

/**
 * Sets all motor to a specific speed
 */
void set_all_motors_speed(UWORD speed) {
  Motor *current_motor;
  for (int i = 0; i < _motor_driver->num_of_motors; i++) {
    current_motor = _motor_driver->motors[i];
    PCA9685_SetPwmDutyCycle(current_motor->pwm_pin, speed);
  }
}

/**
 * Stop motor rotation.
 */
void set_all_motors_to_stop() {
  Motor *current_motor;
  for (int i = 0; i < _motor_driver->num_of_motors; i++) {
    current_motor = _motor_driver->motors[i];
    PCA9685_SetPwmDutyCycle(current_motor->pwm_pin, 0);
  }
}
