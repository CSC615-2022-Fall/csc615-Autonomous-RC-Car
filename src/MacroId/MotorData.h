/**************************************************************
 * Class:  CSC-615-01 Fall 2022
 * Names: Christian Francisco, David Ye Luo, Marc Castro, Rafael Sunico
 * Student IDs: 920603057, 917051959, 921720147, 920261261
 * GitHub Name: csc615-term-project-DavidYeLuo
 * Group Name: Fried Pi
 * Project: Robot Car
 *
 * File: MotorData.h
 *
 * Description: Contains information such as which PCA channel is which.
 * Also contains a Motor structure to be used like an object.
 *
 **************************************************************/
#ifndef MOTORDATA_H
#define MOTORDATA_H
#include "../External_Libraries/DEV_Config.h"

#define PWMA PCA_CHANNEL_0
#define AIN1 PCA_CHANNEL_2
#define AIN2 PCA_CHANNEL_1 // Positive Pole
#define PWMB PCA_CHANNEL_5
#define BIN1 PCA_CHANNEL_3 // Positive Pole
#define BIN2 PCA_CHANNEL_4

typedef struct Motor {
  UWORD base_speed;

  // Hardware wiring
  UBYTE pwm_pin;
  UBYTE positive_pole;
  UBYTE negative_pole;
} Motor;

#endif
