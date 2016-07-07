#include <Arduino.h>
#include <user_interface.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

extern "C" {
  int16_t readvdd33(void);
}

ESP8266WiFiMulti WiFiMulti;

ADC_MODE(ADC_VCC);

int led1 = 14;
int blink_delay = 250;

void setup() {

  pinMode(led1, OUTPUT);
  digitalWrite(led1, HIGH);
  delay(blink_delay);
  digitalWrite(led1, LOW);
  delay(blink_delay);


  Serial.begin(115200);
  //Serial.setDebugOutput(true);

  Serial.flush();
  Serial.println();
  Serial.println();
  Serial.println("########## SETUP ##########");
  Serial.println();
  rst_info *ri = ESP.getResetInfoPtr();
  Serial.printf("[SETUP] Reset reason: %d", ri->reason);
  Serial.println();

  if(ri->reason != REASON_DEEP_SLEEP_AWAKE){  
  }    

  for(uint8_t t = 5; t > 0; --t) {
      Serial.printf("[SETUP] WAIT %d...\n", t);
      Serial.flush();
      delay(1000);
  }
  Serial.printf("[SETUP] Add AP");
  Serial.println();
  //WiFiMulti.addAP("FRITZ!Box Fon WLAN 7360 SL", "2029946184991954"); 
  WiFiMulti.addAP("FRITZ!Box 6360 Cable", "2519061608442019");
  delay(1000);
  int wlanState = WiFiMulti.run();
  int retries = 3;
  while(wlanState != WL_CONNECTED) {    
     if(--retries == 0){
       Serial.printf("[SETUP] Connection failed :( ...\n");
       Serial.flush();
       ESP.deepSleep(0);
     }
     Serial.printf("[SETUP] CONNECTING ...\n");
     Serial.flush();
     delay(1000);
  }
  Serial.flush();
}

void loop() {
    digitalWrite(led1, HIGH);
    delay(blink_delay);
    digitalWrite(led1, LOW);
    delay(blink_delay);
    // wait for WiFi connection
    int wlanState = WiFiMulti.run();
    if(wlanState == WL_CONNECTED) {
      HTTPClient http;
      
      Serial.print("[HTTP] begin...\n");
      // configure traged server and url
      //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
      http.begin("http://www.example.com/"); //HTTP

      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if(httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    }else{
      Serial.printf("[WLAN] No connection, error: %d", wlanState);      
      Serial.println();
    }
    Serial.printf("[VOLTAGE] %d mV", ESP.getVcc());
    Serial.println();
    Serial.flush();
    ESP.deepSleep(1000 * 1000 * 10);    
    //delay(10000);
}

