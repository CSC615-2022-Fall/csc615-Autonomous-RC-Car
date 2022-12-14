/**************************************************************
 * Class:  CSC-615-01 Fall 2022
 * Names: Christian Francisco, David Ye Luo, Marc Castro, Rafael Sunico
 * Student IDs: 920603057, 917051959, 921720147, 920261261
 * GitHub Name: csc615-term-project-DavidYeLuo
 * Group Name: Fried Pi
 * Project: Robot Car
 *
 * File: main.c
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
#include "src/MacroId/SensorData.h"
#include "src/MotorDriver.h"
#include "src/SensorDriver.h"

// I2C Hat Address
#define I2C_HAT_ADDRESS (char)0x40

// GPIO Pin Numbers
#define GPIO_START_BUTTON 26
#define GPIO_LEFT_LINE_SENSOR 20       // Reflective sensor left
#define GPIO_RIGHT_LINE_SENSOR 21      // Reflective sensor right
#define GPIO_FRONT_ECHO_SENSOR_TRIG 19 // Front Echo Sensor Trigger
#define GPIO_FRONT_ECHO_SENSOR_ECHO 13 // Front Echo Sensor Echo
#define GPIO_LEFT_ECHO_SENSOR_TRIG 17  // Left Echo Sensor Trigger
#define GPIO_LEFT_ECHO_SENSOR_ECHO 27  // Left Echo Sensor Echo
#define GPIO_RIGHT_ECHO_SENSOR_TRIG 23 // Right Echo Sensor Trigger
#define GPIO_RIGHT_ECHO_SENSOR_ECHO 24 // Right Echo Sensor Echo

// SensorDriver Config
#define MAX_NUM_OF_SENSORS 10

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

int running;

// sigint handler for cntl-c
void sigint(int sig) { running = RUN_OFF; }

int main(int argc, char *argv[]) {
  // CMD Line Arguments
  int speed = 65;           // Normal speed
  int rev_speed = 30;       // Reverse speed
  int turn_speed = 50;      // 90 Turning speed
  double turn_duration = 2; // 90 Turning duration
  int use_left = 1;         // 1 = using left sensor steer right around obstruction, 0 = using right steer left
  if (argc == 6) {
    speed = atoi(argv[1]);
    rev_speed = atoi(argv[2]);
    turn_speed = atoi(argv[3]);
    turn_duration = atof(argv[4]);
    use_left = atof(argv[5]);
  }

  printf("Using arguments:\nSpeed: %d\nReverse Speed: %d\n90 Turn Speed: "
         "%d\n90 Turn Duration: %f\nUsing left sensor: %d\n",
         speed, rev_speed, turn_speed, turn_duration, use_left);

  // Data to use
  int *left_line_sensor;
  int *right_line_sensor;
  int *front_echo_sensor;
  int *back_echo_sensor;

  // GPIO Init
  if (gpioInitialise() < 0) {
    fprintf(stderr, "pigpio initialisation failed\n");
    return 1;
  }

  // I2C, PWM, MOTOR HAT Init
  // init_motor_driver(I2C_HAT_ADDRESS, 100, 2);
  init_motor_driver(0x40, 1000, 2);
  // Add Motors
  add_motor_to_driver(100, PWMA, AIN1, AIN2);
  add_motor_to_driver(100, PWMB, BIN2, BIN1);
  // Sets up the initial direction
  set_motor_direction_forward(LEFT_MOTOR);
  set_motor_direction_forward(RIGHT_MOTOR);
  set_all_motors_to_stop();

  gpioSetMode(GPIO_LEFT_LINE_SENSOR, PI_INPUT);
  gpioSetMode(GPIO_RIGHT_LINE_SENSOR, PI_INPUT);
  gpioSetMode(GPIO_FRONT_ECHO_SENSOR_TRIG, PI_OUTPUT);
  gpioSetMode(GPIO_FRONT_ECHO_SENSOR_ECHO, PI_INPUT);
  if (use_left == 1) {
    gpioSetMode(GPIO_LEFT_ECHO_SENSOR_TRIG, PI_OUTPUT);
    gpioSetMode(GPIO_LEFT_ECHO_SENSOR_ECHO, PI_INPUT);
  } else {
    gpioSetMode(GPIO_RIGHT_ECHO_SENSOR_TRIG, PI_OUTPUT);
    gpioSetMode(GPIO_RIGHT_ECHO_SENSOR_ECHO, PI_INPUT);
  }

  // Init Sensors here
  init_sensor_driver(MAX_NUM_OF_SENSORS);

  // Add sensors
  // Left Line Sensor
  Sensor *currentSensor1 = new_line_sensor(GPIO_LEFT_LINE_SENSOR);
  left_line_sensor = &(currentSensor1->data);
  // Right Line Sensor
  Sensor *currentSensor2 = new_line_sensor(GPIO_RIGHT_LINE_SENSOR);
  right_line_sensor = &(currentSensor2->data);
  // Front Echo Sensor
  Sensor *currentSensor3 = new_echo_sensor(GPIO_FRONT_ECHO_SENSOR_ECHO, GPIO_FRONT_ECHO_SENSOR_TRIG);
  front_echo_sensor = &(currentSensor3->data);
  // Back Echo Sensor
  Sensor *currentSensor4;
  if (use_left == 1) {
    currentSensor4 = new_echo_sensor(GPIO_LEFT_ECHO_SENSOR_ECHO, GPIO_LEFT_ECHO_SENSOR_TRIG);
  } else {
    currentSensor4 = new_echo_sensor(GPIO_RIGHT_ECHO_SENSOR_ECHO, GPIO_RIGHT_ECHO_SENSOR_TRIG);
  }
  back_echo_sensor = &(currentSensor4->data);

  // Start sensors
  start_sensors();

  signal(SIGINT, sigint);

  running = RUN_ON;

  // BUTTON SIGNAL GOES HERE
  printf("Waiting for button press...\n");
  while (running == RUN_ON && gpioRead(GPIO_START_BUTTON) == 0) {}
  printf("RUNNING\n");

  while (running == RUN_ON) {
    // decision handling here

    if (*front_echo_sensor < 10) {
      printf("I SEE OBJECT FRONT, TURN UNTIL BACK SEES OBJECT\n");

      // full stop
      set_all_motors_to_stop();
      time_sleep(0.2);

      // turn until back echo sees object
      set_motor_speed(RIGHT_MOTOR, turn_speed);
      set_motor_speed(LEFT_MOTOR, turn_speed);
      if (use_left) {
        // turn right until left echo sees object
        set_motor_direction_backward(RIGHT_MOTOR);
        set_motor_direction_forward(LEFT_MOTOR);
      } else {
        // turn left until right echo sees object
        set_motor_direction_forward(RIGHT_MOTOR);
        set_motor_direction_backward(LEFT_MOTOR);
      }
      while (*back_echo_sensor >= 20)
        usleep(100);
      printf("BACK SEES OBJECT, STOP TURNING, MOVE FORWARDS UNTIL BACK DOESNT SEE OBJECT\n");

      set_all_motors_to_stop();
      time_sleep(0.2);

      // repeat move forwards until back echo does not see object
      set_motor_speed(RIGHT_MOTOR, turn_speed);
      set_motor_speed(LEFT_MOTOR, turn_speed);
      set_motor_direction_forward(RIGHT_MOTOR);
      set_motor_direction_forward(LEFT_MOTOR);
      while (*back_echo_sensor < 20)
        usleep(100);
      printf("BACK DOESNT SEE OBJECT, STOP MOVING, TURN 90, MOVE FORWARDS UNTIL BACK SEES OBJECT\n");

      set_all_motors_to_stop();
      time_sleep(0.2);

      // 90 degree turn
      set_motor_speed(RIGHT_MOTOR, turn_speed);
      set_motor_speed(LEFT_MOTOR, turn_speed);
      if (use_left) {
        // turn left
        set_motor_direction_forward(RIGHT_MOTOR);
        set_motor_direction_backward(LEFT_MOTOR);
      } else {
        // turn right
        set_motor_direction_backward(RIGHT_MOTOR);
        set_motor_direction_forward(LEFT_MOTOR);
      }
      time_sleep(turn_duration);

      set_all_motors_to_stop();
      time_sleep(0.2);

      // repeat move forwards until back echo sensor sees object
      set_motor_speed(RIGHT_MOTOR, turn_speed);
      set_motor_speed(LEFT_MOTOR, turn_speed);
      set_motor_direction_forward(RIGHT_MOTOR);
      set_motor_direction_forward(LEFT_MOTOR);
      while (*back_echo_sensor >= 20)
        usleep(100);
      printf("BACK SEES OBJECT, STOP MOVING, MOVE FORWARDS SLIGHTLY, MOVE FORWARDS UNTIL BACK SEES OBJECT\n");

      set_all_motors_to_stop();
      time_sleep(0.2);

      // move forwards slightly
      set_motor_speed(RIGHT_MOTOR, turn_speed);
      set_motor_speed(LEFT_MOTOR, turn_speed);
      set_motor_direction_forward(RIGHT_MOTOR);
      set_motor_direction_forward(LEFT_MOTOR);
      time_sleep(0.05);

      set_all_motors_to_stop();
      time_sleep(0.2);

      // repeat move forwards until left echo sensor does not see object
      set_motor_speed(RIGHT_MOTOR, turn_speed);
      set_motor_speed(LEFT_MOTOR, turn_speed);
      set_motor_direction_forward(RIGHT_MOTOR);
      set_motor_direction_forward(LEFT_MOTOR);
      while (*back_echo_sensor < 20)
        usleep(100);
      printf("BACK SEES OBJECT, STOP MOVING, 90 TURN, MOVE FORWARDS UNTIL FRONT SEES BLACK\n");

      set_all_motors_to_stop();
      time_sleep(0.2);

      // move forwards slightly
      set_motor_speed(RIGHT_MOTOR, turn_speed);
      set_motor_speed(LEFT_MOTOR, turn_speed);
      set_motor_direction_forward(RIGHT_MOTOR);
      set_motor_direction_forward(LEFT_MOTOR);
      time_sleep(0.1);

      set_all_motors_to_stop();
      time_sleep(0.2);

      // 90 degree turn
      set_motor_speed(RIGHT_MOTOR, turn_speed);
      set_motor_speed(LEFT_MOTOR, turn_speed);
      if (use_left) {
        // turn left
        set_motor_direction_forward(RIGHT_MOTOR);
        set_motor_direction_backward(LEFT_MOTOR);
      } else {
        // turn right
        set_motor_direction_backward(RIGHT_MOTOR);
        set_motor_direction_forward(LEFT_MOTOR);
      }
      time_sleep(turn_duration);

      set_all_motors_to_stop();
      time_sleep(0.2);

      // repeat move forwards until RIGHT/LEFT reflective sensor see black
      set_motor_speed(RIGHT_MOTOR, turn_speed);
      set_motor_speed(LEFT_MOTOR, turn_speed);
      set_motor_direction_forward(RIGHT_MOTOR);
      set_motor_direction_forward(LEFT_MOTOR);
      if (use_left) {
        while (*right_line_sensor == OFF_LINE)
          usleep(100);
      } else {
        while (*left_line_sensor == OFF_LINE)
          usleep(100);
      }
      printf("LINE SEES BLACK FRONT, MOVE SIDE UNTIL OTHER LINE SEES BLACK\n");

      set_all_motors_to_stop();
      time_sleep(0.2);

      // stop RIGHT/LEFT, repeat move LEFT/RIGHT forwards until LEFT/RIGHT sensor sees black
      if (use_left) {
        set_motor_speed(RIGHT_MOTOR, 0);
        set_motor_speed(LEFT_MOTOR, turn_speed);
      } else {
        set_motor_speed(RIGHT_MOTOR, turn_speed);
        set_motor_speed(LEFT_MOTOR, 0);
      }
      set_motor_direction_forward(RIGHT_MOTOR);
      set_motor_direction_forward(LEFT_MOTOR);
      if (use_left) {
        while (*left_line_sensor == OFF_LINE)
          usleep(100);
      } else {
        while (*right_line_sensor == OFF_LINE)
          usleep(100);
      }
      printf("OTHER LINE SEES BLACK FRONT, MOVE SIDE UNTIL LINE SEES WHITE\n");

      set_all_motors_to_stop();
      time_sleep(0.2);

      // stop RIGHT/LEFT repeat move forwards until RIGHT/LEFT sensor sees white
      if (use_left) {
        set_motor_speed(RIGHT_MOTOR, 0);
        set_motor_speed(LEFT_MOTOR, turn_speed);
      } else {
        set_motor_speed(RIGHT_MOTOR, turn_speed);
        set_motor_speed(LEFT_MOTOR, 0);
      }
      set_motor_direction_forward(RIGHT_MOTOR);
      set_motor_direction_forward(LEFT_MOTOR);
      if (use_left) {
        while (*right_line_sensor == ON_LINE)
          usleep(100);
      } else {
        while (*left_line_sensor == ON_LINE)
          usleep(100);
      }
      printf("LINE SEES WHITE, WE ARE BACK ON THE LINE\n");

      continue;
    }

    if (*left_line_sensor == OFF_LINE) {
      set_motor_direction_forward(LEFT_MOTOR);
      set_motor_speed(LEFT_MOTOR, speed);
    } else {
      set_motor_direction_backward(LEFT_MOTOR);
      set_motor_speed(LEFT_MOTOR, rev_speed);
    }

    if (*right_line_sensor == OFF_LINE) {
      set_motor_direction_forward(RIGHT_MOTOR);
      set_motor_speed(RIGHT_MOTOR, speed);
    } else {
      set_motor_direction_backward(RIGHT_MOTOR);
      set_motor_speed(RIGHT_MOTOR, rev_speed);
    }
  }

  // Cleanup
  set_all_motors_to_stop();
  terminate_sensor_driver();
  terminate_motor_driver();
  gpioTerminate();

  return 0;
}
