#include "sensor_avg.h"

static float temp_buf[AVG_N], hum_buf[AVG_N];
static int buf_idx = 0, buf_count = 0;
SemaphoreHandle_t xSensorMutex = NULL;

void addSample (float t, float h){
    if (xSensorMutex == NULL) {
        xSensorMutex = xSemaphoreCreateMutex();
    }
    xSemaphoreTake (xSensorMutex, portMAX_DELAY);
    temp_buf[buf_idx] = t;
    hum_buf[buf_idx] = h;
    buf_idx = (buf_idx + 1) % AVG_N;
    if (buf_count < AVG_N) buf_count++;
    xSemaphoreGive (xSensorMutex);
}

bool getAverage (float *t_avg, float *h_avg){
    if (t_avg == NULL || h_avg == NULL) {
        return false;
    }
    if (xSensorMutex == NULL) {
        xSensorMutex = xSemaphoreCreateMutex();
    }
    xSemaphoreTake (xSensorMutex, portMAX_DELAY);
    if (buf_count == 0) {
        xSemaphoreGive (xSensorMutex);
        return false;
    }
    float t_sum = 0, h_sum = 0;
    for (int i = 0; i < buf_count; i++) {
        t_sum += temp_buf[i];
        h_sum += hum_buf[i];
    }
    *t_avg = t_sum / buf_count;
    *h_avg = h_sum / buf_count;
    xSemaphoreGive (xSensorMutex);
    return true;
}