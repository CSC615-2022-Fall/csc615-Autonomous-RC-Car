#include "ThreadSensor.h"

/**
 * Threaded function where it will pull data from echo sensor.
 * Credit to Rafael writing the implementation
 * @param threadArgs Contains information such as when to stop, and sensor information.
 * @return void* 
 */
void* thread_collect_echo_sensor_data(void* threadArgs)
{
    ThreadArgs* args = (ThreadArgs*) threadArgs;
    int* isRunning = args->isRunning;
    Sensor* sensor = args->sensor;
    int* triggerPin = &(sensor->gpio_trig);
    int* echoPin = &(sensor->gpio_echo);

    struct timespec startTime;
    struct timespec endTime;

    while (*isRunning == RUN_ON) {
        // Send trigger pulse, 1ms duration, HIGH value
        if (gpioTrigger(*triggerPin, 1, 1) != 0) {
            fprintf(stderr, "pigpio trigger failed for pin:%d\n", *triggerPin);
            pthread_exit(NULL);
        }

        // keep setting start timer until ECHO doesn't read 0
        while (gpioRead(*echoPin) == 0) {
            clock_gettime(CLOCK_REALTIME, &startTime);
        }

        // keep setting end timer until ECHO doesn't read 1
        while (gpioRead(*echoPin) == 1) {
            clock_gettime(CLOCK_REALTIME, &endTime);
        }

        // calulcate elapsed time
        double startSec = startTime.tv_sec + startTime.tv_nsec / NANO_PER_SEC;
        double endSec = endTime.tv_sec + endTime.tv_nsec / NANO_PER_SEC;
        double elapsedSec = endSec - startSec;

        // calculate distance in cm
        // speed of sound in air: 34300 cm/s, divide by 2 for roundtrip
        double distance = (elapsedSec * 34300) / 2;

        // load distance into int* input
        sensor->data = (int)distance;
    }
    pthread_exit(NULL);
}

/**
 * Credit to Rafael writing the implementation
 */
void* thread_collect_line_sensor_data(void* threadArgs)
{
    ThreadArgs* args = (ThreadArgs*) threadArgs;
    int* isRunning = args->isRunning;
    Sensor* sensor = args->sensor;
    int pin = sensor->gpio_line;

    while(*isRunning == RUN_ON)
    {
        sensor->data = gpioRead(pin);
    }
    pthread_exit(NULL);
}