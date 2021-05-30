#include "esp_camera.h"
#include <WiFi.h>
#include "camera_config.cpp"


const char *ssid = "********";
const char *password = "********";


void startCameraServer();

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  // Arduino connection setup
  Serial2.begin(38400, SERIAL_8N1, 15, 14);

  // Camera setup
  camera_config_t config;
  config_camera(&config);
  
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera/ init failed with error 0x%x", err);
    return;
  }
  
  sensor_t *s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_SVGA);
//  s->set_quality(s, 30);/


  // WiFi setup
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect/");
}


void loop(){
//  Serial2.write("90", 2);/
//  delay(2000);/
//  Serial2.write("00", 2);/
//  delay(1000);/
}
