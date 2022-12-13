/**************************************************************
 * Class:  CSC-615-01 Fall 2022
 * Names: Christian Francisco, David Ye Luo, Marc Castro, Rafael Sunico
 * Student IDs: 920603057, 917051959, 921720147, 920261261
 * GitHub Name: csc615-term-project-DavidYeLuo
 * Group Name: Fried Pi
 * Project: Robot Car
 *
 * File: TurnCalibrate.c
 *
 * Description:
 *
 **************************************************************/

#include <pigpio.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "src/MacroId/MacroDefinitions.h"
#include "src/MotorDriver.h"

// I2C Hat Address
#define I2C_HAT_ADDRESS (char)0x40

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

int main(int argc, char *argv[]) {
  // CMD Line Arguments
  int turn_speed = 50;      // 90 Turning speed
  double turn_duration = 2; // 90 Turning duration
  if (argc == 3) {
    turn_speed = atoi(argv[1]);
    turn_duration = atof(argv[2]);
  }

  printf("Using arguments:\n90 Turn Speed: %d\n90 Turn Duration: %f\n",
         turn_speed, turn_duration);

  // GPIO Init
  if (gpioInitialise() < 0) {
    fprintf(stderr, "pigpio initialisation failed\n");
    return 1;
  }

  // I2C, PWM, MOTOR HAT Init
  // init_motor_driver(I2C_HAT_ADDRESS, 100, 2);
  init_motor_driver(0x40, 1000, 2); // Not sure if this fixes some bug
  // Add Motors
  add_motor_to_driver(100, PWMA, AIN1, AIN2);
  add_motor_to_driver(100, PWMB, BIN2, BIN1);

  // Sets up the initial direction
  set_motor_direction_forward(LEFT_MOTOR);
  set_motor_direction_backward(RIGHT_MOTOR);
  set_all_motors_to_stop();

  set_motor_speed(LEFT_MOTOR, turn_speed);
  set_motor_speed(RIGHT_MOTOR, turn_speed);

  time_sleep(turn_duration);

  // Cleanup
  set_all_motors_to_stop();
  terminate_motor_driver();
  gpioTerminate();

  return 0;
}
