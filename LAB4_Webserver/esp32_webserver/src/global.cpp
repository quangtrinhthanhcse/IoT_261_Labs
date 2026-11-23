#include "global.h"

float glob_temperature = 0;
float glob_humidity = 0;

String ssid = "ESP32-G08"; // Group 08 AP SSID
String password = "12345678"; // Must be >= 8 characters

String wifi_ssid = ""; // Set via /connect
String wifi_password = "";

bool isWifiConnected = false;
SemaphoreHandle_t xBinarySemaphoreInternet = NULL; // Created in setup()
