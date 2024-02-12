#include <ArduinoJson.h>
#include <PubSubClient.h>
#include "globals.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <base64.h>
#include "UNIT_4RELAY.h"
#include <SPIFFS.h>

#include <HX711_ADC.h>
#include <EEPROM.h>
#include <ESP32Time.h>
struct tm timeinfo;
ESP32Time rtc(3600);

/* wifi and ntp */
#include <SPI.h>
#include <time.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <timeclient.h>

/* wifimanager */
#include <WiFiManager.h>

WiFiClient wifiClient;
PubSubClient client(wifiClient);
UNIT_4RELAY relay;
HX711_ADC LoadCell(HX711_dout, HX711_sck);

TaskHandle_t servetask;
TaskHandle_t measuretask;
TaskHandle_t displaytask;

const int calVal_eepromAdress = 0;
unsigned long t = 0;

/* additional */

#include <display.h>
#include <sdfunctions.h>
#include <functions.h>
#include <mqttfunctions.h>

#include <servetask.h>
#include <measuretask.h>

void setup() {
  xTaskCreatePinnedToCore(servetaskCode, "servetask", 4096, NULL, 1, &servetask, 0); 
  xTaskCreatePinnedToCore(measuretaskCode, "measuretask", 4096, NULL, 1, &measuretask, 0); 

  M5.begin();            
  M5.Power.begin();   
  M5.Lcd.setBrightness(200);
  M5.Lcd.setCursor(10,10);
  M5.lcd.setTextSize(2);
  M5.Lcd.printnln(VERSION);
  Wire.begin();
  initializeSD(); 
  readConfig();

  Serial.begin(115200);
  if (SPIFFS.begin()) {
		Serial.println("SPIFFS MOUNTED");
	}
  delay(10);

  DEBUG_INFORMATION_SERIAL.print("Networkmode: "); DEBUG_INFORMATION_SERIAL.println(config.NETworkmode); 
  DEBUG_INFORMATION_SERIAL.println();
  DEBUG_INFORMATION_SERIAL.println("Starting... Bender");

  #include <network.h>
  #include <loadcell.h>
    
  relay.begin();
  relay.Init(1);
  //pinMode(LED1, OUTPUT);
  //pinMode(LED2, OUTPUT);
  //switchLed(LED1,0); //servingled
  //switchLed(LED2,1);

  setDisplay(serving.displaypage);
  randomSeed(analogRead(0));

 if(config.NETworkmode){
    ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();
 }

}

void loop() {
  M5.update();
  client.loop();
  buttonHandling();
  updateDisplay();

  if (millis() - oldMillisTWO >= pauseTWO) {
    oldMillisTWO = millis();
    buttonPress = buttonPress+1;
  }

 if(config.NETworkmode){
    ArduinoOTA.handle();
    if (!client.connected()) {
      DEBUG_INFORMATION_SERIAL.println("Not connected - go to reconnect");
      reconnect();
    }
    client.loop();
    delay(100);
  }
  
}
