#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define USE_SERIAL Serial
ESP8266WiFiMulti WiFiMulti;

int led1 = 16;
int blink_delay = 250;

void setup() {
  pinMode(led1, OUTPUT);
  digitalWrite(led1, HIGH);
  delay(blink_delay);
  digitalWrite(led1, LOW);
  delay(blink_delay);

  USE_SERIAL.begin(115200);
  // USE_SERIAL.setDebugOutput(true);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();
  for(int t = 4; t > 0; t--) {
    USE_SERIAL.printf("wait %d ...", t);
    USE_SERIAL.flush();
    delay(1000);
  }  
}

void loop() {
  digitalWrite(led1, HIGH);
  delay(blink_delay * 2);
  digitalWrite(led1, LOW);
  delay(blink_delay * 2);
  USE_SERIAL.print("  loop");
}
