#ifndef MOTORDATA_H
#define MOTORDATA_H
#include "../External_Libraries/DEV_Config.h"

#define PWMA        PCA_CHANNEL_0
#define AIN1        PCA_CHANNEL_2
#define AIN2        PCA_CHANNEL_1 // Positive Pole
#define PWMB        PCA_CHANNEL_5
#define BIN1        PCA_CHANNEL_3 // Positive Pole
#define BIN2        PCA_CHANNEL_4

typedef struct Motor
{
    int base_speed;

    // Hardware wiring
    int pwm_pin;
    int positive_pole;
    int negative_pole;
} Motor;

#endif