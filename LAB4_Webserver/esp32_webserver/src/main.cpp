#include "global.h"
#include "mainserver.h"
#include "sensor_avg.h"

// Wait for "Internet ready" signal from main_server_task
void internet_task(void *pvParameters)
{
  while (1)
  {
    // Blocked here until main_server_task calls xSemaphoreGive()
    if (xSemaphoreTake(xBinarySemaphoreInternet, portMAX_DELAY) == pdTRUE)
    {
      Serial.println("[NET] Internet ready");
      // Exercise 5: connect to CoreIOT and publish telemetry here
    }
  }
}

// Simulated sensor task for testing without physical DHT20 attached
void sensor_task(void *pvParameters)
{
  while (1)
  {
    float t = 28.0 + random(0, 300) / 100.0; // 28.00..30.99
    float h = 60.0 + random(0, 500) / 100.0; // 60.00..64.99
    glob_temperature = t;
    glob_humidity = h;
    addSample(t, h);

    float t_avg = 0, h_avg = 0;
    if (getAverage(&t_avg, &h_avg))
    {
      Serial.printf("[SENSOR] Raw: T=%.2f C, H=%.2f %% | Avg: T=%.2f C, H=%.2f %%\n",
                    t, h, t_avg, h_avg);
    }
    vTaskDelay(pdMS_TO_TICKS(2000)); // 2 seconds
  }
}

void setup()
{
  Serial.begin(115200);

  // 1) Create semaphore BEFORE any task uses it
  xBinarySemaphoreInternet = xSemaphoreCreateBinary();

  xSensorMutex = xSemaphoreCreateMutex();

  // 2) Start tasks
  xTaskCreate(main_server_task, "server", 8192, NULL, 2, NULL);
  xTaskCreate(internet_task, "internet", 4096, NULL, 1, NULL);
  xTaskCreate(sensor_task, "sensor", 4096, NULL, 1, NULL);
}

void loop()
{
  vTaskDelay(pdMS_TO_TICKS(1000));
}
