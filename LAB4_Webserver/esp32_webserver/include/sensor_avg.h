#include <Arduino.h>

#define AVG_N 10
extern SemaphoreHandle_t xSensorMutex;
void addSample (float t, float h);
bool getAverage (float *t_avg, float *h_avg);

