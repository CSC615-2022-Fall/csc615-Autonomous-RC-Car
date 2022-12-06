#include "MotorDriver.h"


MotorDriver* _motor_driver;
/**
 * Motor rotation.
 *
 * Example:
 * Motor_Init();
 */
void init_motor_driver(char i2c_address, int pwm_freq, int max_num_of_motors)
{
    PCA9685_Init(i2c_address); // TODO: Test this later because main is passing an int
    PCA9685_SetPWMFreq(pwm_freq);
    _motor_driver->motor_capacity = max_num_of_motors;
    _motor_driver = malloc(sizeof(MotorDriver) * max_num_of_motors);
}


void terminate_motor_driver()
{
    Motor* current_motor;
    for(int i = 0; i < _motor_driver->num_of_motors; i++)
    {
        current_motor = _motor_driver->motors[i];

        // Stop it from driving
        PCA9685_SetPwmDutyCycle(current_motor->pwm_pin, 0);

        free(current_motor);
    }
    free(_motor_driver);
}

void add_motor_to_driver(int base_speed, int pwm_pin, int positive_motor_pin, int negative_motor_pin)
{
    int index = _motor_driver->num_of_motors;
    if(index >= _motor_driver->motor_capacity)
    {
        printf("Add motor failed. Tried to add more than the capacity.\n");
    }
    // Create the driver
    Motor* current_motor = malloc(sizeof(Motor));
    current_motor->pwm_pin = pwm_pin;
    current_motor->base_speed = base_speed;
    current_motor->positive_pole = positive_motor_pin;
    current_motor->negative_pole = negative_motor_pin;

    // Add the driver
    _motor_driver->motors[index];
    _motor_driver->num_of_motors++; // Increment counter
}

/**
 * Motor move forward or backward
 * This doesn't handle actual movement!
 * Only the polarity changes
 * direction should be either FORWARD or BACKWARD
 */
void set_motor_direction(int index, int direction)
{
    Motor* current_motor = _motor_driver->motors[index];
    if(direction == FORWARD)
    {
        PCA9685_SetLevel(current_motor->positive_pole, 1);
        PCA9685_SetLevel(current_motor->negative_pole, 0);
    }
    else if(direction == FORWARD)
    {
        PCA9685_SetLevel(current_motor->positive_pole, 0);
        PCA9685_SetLevel(current_motor->negative_pole, 1);
    }
    else
    {
        printf("Direction not found\n");
    }
}

void set_motor_speed(int index, int speed_percentage)
{
    PCA9685_SetPwmDutyCycle(_motor_driver->motors[index]->pwm_pin, 0);
}

void set_all_motor_speed(int index, int speed_percentage)
{
    Motor* current_motor;
    for(int i = 0; i < _motor_driver->num_of_motors; i++)
    {
        current_motor = _motor_driver->motors[i];
        PCA9685_SetPwmDutyCycle(current_motor->pwm_pin, 0);
    }
}

/**
 * Motor stop rotation.
 *
 * @param motor: Motor A and Motor B.
 *
 * Example:
 * @code
 * Motor_Stop(MOTORA);
 */
void set_all_motor_to_stop()
{
    Motor* current_motor;
    for(int i = 0; i < _motor_driver->num_of_motors; i++)
    {
        current_motor = _motor_driver->motors[i];
        PCA9685_SetPwmDutyCycle(current_motor->pwm_pin, 0);
    }
}
