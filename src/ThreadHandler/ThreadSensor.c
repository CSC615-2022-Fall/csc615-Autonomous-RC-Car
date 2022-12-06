#include "ThreadSensor.h"

/**
 * Threaded function where it will pull data from echo sensor.
 * 
 * @param threadArgs Contains information such as when to stop, and sensor information.
 * @return void* 
 */
void* thread_collect_echo_sensor_data(void* threadArgs)
{
    ThreadArgs* args = (ThreadArgs*) threadArgs;
    int* isRunning = args->isRunning;
    Sensor* sensor = args->sensor;

    /**
     * TODO: make actual implementation using external libraries or homework assignment.
     * Code below are just template
     */
    int temp = 100000;
    while(*isRunning == RUN_ON)
    {
        sensor->data = temp;// Here is how we should modify the data
        temp--;
        if(temp < 0){
            pthread_exit(NULL);
        }
    }
    pthread_exit(NULL);
}
void* thread_collect_line_sensor_data(void* threadArgs)
{
    /**
     * TODO: make actual implementation using external libraries or homework assignment.
     * Code below are just template
     */
    printf("Collecting line data\n");
    pthread_exit(NULL);
}