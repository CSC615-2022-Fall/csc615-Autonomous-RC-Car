#include "SensorDriver.h"

SensorDriver* _sensor_driver;

// Private helper for new_ functions
// Necessary to register the sensors to the driver
// This way we can later start their threads
void _add_sensor_to_driver(Sensor* sensor, int index);
void _add_thread_to_driver(int index);

/*
* Initialize the state of the driver
*/
void init_sensor_driver(int max_sensors)
{
    if(max_sensors < 1)
    {
        printf("WARNING: init_sensor_driver has max sensors of 0.\n");
        return;
    }
    _sensor_driver = malloc(sizeof(SensorDriver));
    _sensor_driver->num_of_sensors = 0;
    _sensor_driver->sensor_list_capacity = max_sensors;
    _sensor_driver->sensors = malloc(sizeof(SensorDriver) * max_sensors);
    _sensor_driver->_threads = malloc(sizeof(pthread_t) * max_sensors);
}

/*
* Ends the program by deallocating the resources
*/
void terminate_sensor_driver()
{
    _sensor_driver->isRunning = RUN_OFF;

    // Deallocate sensors
    Sensor* current_sensor;
    pthread_t* current_thread;
    for(int i = 0; 
        i < _sensor_driver->num_of_sensors; 
        i++)
    {
        current_sensor = _sensor_driver->sensors[i * sizeof(Sensor)];
        current_thread = _sensor_driver->_threads[i * sizeof(pthread_t)];
        // Join Thread
        free(current_thread);
        free(current_sensor);
    }

    // Deallocate driver's attributes
    free(_sensor_driver->sensors);
    free(_sensor_driver->_threads);
    // Deallocate the driver
    free(_sensor_driver);
}

/*
* Starts thread for each specific sensors.
* TODO: Call thread functions here
*/
void start_sensors()
{
    _sensor_driver->isRunning = RUN_ON;

    printf("TODO: Modify the inner for loop to initialize threads\n");
    Sensor* current_sensor;
    pthread_t* current_thread;
    for(int i = 0; 
        i < _sensor_driver->num_of_sensors; 
        i++)
    {
        current_sensor = _sensor_driver->sensors[i];
        current_thread = _sensor_driver->_threads[i];
    
        if(current_sensor->sensorType == SENSOR_TYPE_ECHO)
        {
            printf("SensorType: ECHO started \n"); // TODO implement thread
            printf("Thread: %p\n", current_thread);
            printf("Echo GPIO: %d started \n", current_sensor->gpio_echo);
            printf("Trig GPIO: %d started \n", current_sensor->gpio_trig);

        } else if(current_sensor->sensorType == SENSOR_TYPE_LINE)
        {
            printf("SensorType: LINE started \n"); // TODO implement thread
            printf("Thread: %p\n", current_thread);
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

    int current_index = _sensor_driver->num_of_sensors;
    _add_sensor_to_driver(ret, current_index);
    _add_thread_to_driver(current_index);

    _sensor_driver->num_of_sensors++; // Increment the sensor count
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

    int current_index = _sensor_driver->num_of_sensors;
    int max_capacity = _sensor_driver->sensor_list_capacity;
    if(current_index >= max_capacity)
    {
        printf("ERROR: num of sensors exceeded the max\n");
        return NULL;
    }
    _add_sensor_to_driver(ret, current_index);
    _add_thread_to_driver(current_index);

    _sensor_driver->num_of_sensors++; // Increment the sensor count
    return ret;
}

/*
*  Adds sensor to the driver
*  so that it can be initialized in a thread
*/
void _add_sensor_to_driver(Sensor* sensor, int index)
{
    _sensor_driver->sensors[index] = sensor;
}

/*
*  Allocates thread space to the driver
*  so that it can be initialized in a thread
*/
void _add_thread_to_driver(int index)
{
    _sensor_driver->_threads[index] = malloc(sizeof(pthread_t));
}