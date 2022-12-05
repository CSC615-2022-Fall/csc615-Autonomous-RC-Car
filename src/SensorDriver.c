#include "SensorDriver.h"

SensorDriver* _sensor_driver;

// Private helper for add_sensor_ functions
// Necessary to register the sensors to the driver
// This way we can later start all of them at once
void add_sensor_to_driver(Sensor* sensor);

/*
* Initialize the state of the driver
*/
void init_sensor_driver()
{
    _sensor_driver = malloc(sizeof(SensorDriver));
    _sensor_driver->num_of_sensors = 0;
    _sensor_driver->sensors = malloc(sizeof(SensorDriver) * MAX_SENSORS);
}

/*
* Ends the program by deallocating the resources
*/
void terminate_sensor_driver()
{
    // Deallocate sensors
    Sensor* current_sensor;
    for(int i = 0; 
        i < _sensor_driver->num_of_sensors; 
        i++)
    {
        current_sensor = _sensor_driver->sensors[i * sizeof(SensorDriver)];
        free(current_sensor);
    }

    // Deallocate driver's attributes
    free(_sensor_driver->sensors);
    // Deallocate the driver
    free(_sensor_driver);
}

/*
* TODO: Initialize threads here
*/
void start_sensors()
{
    printf("TODO: Modify the inner for loop to initialize threads\n");
    Sensor* current_sensor;
    for(int i = 0; 
        i < _sensor_driver->num_of_sensors; 
        i++)
    {
        current_sensor = _sensor_driver->sensors[i];
        if(current_sensor->sensorType == SENSOR_TYPE_ECHO)
        {
            printf("SensorType: ECHO started \n"); // TODO implement thread
            printf("Echo GPIO: %d started \n", current_sensor->gpio_echo);
            printf("Trig GPIO: %d started \n", current_sensor->gpio_trig);

        } else if(current_sensor->sensorType == SENSOR_TYPE_LINE)
        {
            printf("SensorType: LINE started \n"); // TODO implement thread
            printf("Line GPIO: %d started \n", current_sensor->gpio_line);
        }
        else 
        {
            printf("ERROR: current_sensor not supported type. %d\n"
            , current_sensor->sensorType);
            return;
        }
    }
}

/*
* 1) Creates a new sensor
* 2) Add the new sensor to the driver.
*    This way the driver can be initialized in a thread
* NOTE: This returns a Sensor*
* Sensor* contains all the necessary data that the user need
*/
Sensor* new_line_sensor(int gpio_line)
{
    Sensor* ret = malloc(sizeof(Sensor));
    ret->gpio_line = gpio_line;
    ret->sensorType = SENSOR_TYPE_LINE;

    add_sensor_to_driver(ret);
    return ret;
}

/*
* 1) Creates a new sensor
* 2) Add the new sensor to the driver.
*    This way the driver can be initialized in a thread
* NOTE: This returns a Sensor*
* Sensor* contains all the necessary data that the user need
*/
Sensor* new_echo_sensor(int gpio_echo, int gpio_trig)
{
    Sensor* ret = malloc(sizeof(Sensor));
    ret->gpio_echo = gpio_echo;
    ret->gpio_trig = gpio_trig;
    ret->sensorType = SENSOR_TYPE_ECHO;

    add_sensor_to_driver(ret);
    return ret;
}

/*
*  Adds sensor to the driver
*  so that it can be initialized in a thread
*/
void add_sensor_to_driver(Sensor* sensor)
{
    int _num_of_sensors = _sensor_driver->num_of_sensors;
    if(_num_of_sensors >= MAX_SENSORS)
    {
        printf("ERROR: num of sensors exceeded the max\n");
        return;
    }
    _sensor_driver->sensors[_num_of_sensors] = sensor;
    _sensor_driver->num_of_sensors++; // Increment the sensor count
}