// IoT Health Monitoring System
// Using ESP32, DHT11 (temperature), Pulse Sensor (heart rate), Blynk Cloud

#define BLYNK_TEMPLATE_ID "TMPxxxxxxx"       // Example Template ID
#define BLYNK_DEVICE_NAME "HealthMonitor"
#define BLYNK_AUTH_TOKEN "1234567890abcdef1234567890abcdef" // Dummy Auth Token

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "MyWiFiNetwork";   // Dummy Wi-Fi SSID
char pass[] = "MyWiFiPassword";  // Dummy Wi-Fi password

#define DHTPIN 4          // GPIO pin for DHT11
#define DHTTYPE DHT11
#define PULSE_PIN 34      // ADC pin for pulse sensor

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensorData() {
  // Temperature reading
  float temp = dht.readTemperature();
  
  // Heart rate simulation or reading from sensor
  int pulseValue = analogRead(PULSE_PIN); // Raw analog value
  int heartRate = map(pulseValue, 0, 4095, 60, 120); // Simple scaling
  
  // Send to Blynk app
  Blynk.virtualWrite(V1, temp);       // Temperature
  Blynk.virtualWrite(V2, heartRate);  // Heart rate
  
  Serial.print("Temp: "); Serial.print(temp); Serial.print(" °C");
  Serial.print(" | Heart Rate: "); Serial.print(heartRate); Serial.println(" BPM");
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();

  // Timer to send data every 2 seconds
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
