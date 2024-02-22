#include <ArduinoJson.h>
#include <HTTPClient.h>
#include "globals.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <HX711_ADC.h>
#include "UNIT_4RELAY.h"

/* wifi  */
#include <SPI.h>
#include <WiFi.h>

#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <Update.h>

/* wifimanager */
//#include <WiFiManager.h>

WiFiClient wifiClient;
HTTPClient httpclient;
HX711_ADC LoadCell(HX711_dout, HX711_sck);
UNIT_4RELAY relay;
TaskHandle_t servetask;
TaskHandle_t measuretask;

//TFT_eSPI    tft = TFT_eSPI();
//TFT_eSprite spr_sd = TFT_eSprite(&tft);

const int calVal_eepromAdress = 0;
unsigned long t = 0;

/* additional */
#include <filedownload.h>
#include <display.h>
#include <sdfunctions.h>
#include <functions.h>
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
  M5.Lcd.println(VERSION);
  Wire.begin();
  initializeSD(); 
  readConfig();
  delay(2000);
  Serial.begin(115200);
  if (SPIFFS.begin()) {
		Serial.println("SPIFFS MOUNTED");
	}
  delay(10);

  DEBUG_INFORMATION_SERIAL.print("Network: "); DEBUG_INFORMATION_SERIAL.println(config.NETworkmode); 
  DEBUG_INFORMATION_SERIAL.print("Networkmode: "); DEBUG_INFORMATION_SERIAL.println(config.mode); 
  DEBUG_INFORMATION_SERIAL.print("Current firmware: v");  Serial.println(FWversion);
  DEBUG_INFORMATION_SERIAL.print("Pumps: ");  Serial.println(config.pumps);
  DEBUG_INFORMATION_SERIAL.println("Starting...");

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
}

void loop() {
  M5.update();

  buttonHandling();
  updateDisplay();

  if (millis() - oldMillisTWO >= pauseTWO) {
    oldMillisTWO = millis();
    buttonPress = buttonPress+1;
  }

 if(config.NETworkmode){
  if(strcmp(config.mode, "client") == 0){
    if ((WiFi.status() != WL_CONNECTED)) {
      DEBUG_INFORMATION_SERIAL.print("Reconnecting to WiFi... retry "); DEBUG_INFORMATION_SERIAL.println(reconretries);
      if(reconretries >= 10){
        strncpy(config.mode, "ap", sizeof config.mode);
        DEBUG_INFORMATION_SERIAL.println("Wifi Mode Accesspoint");
        WiFi.mode(WIFI_AP);
        WiFi.softAP(config.ssid, config.password);
        IPAddress IP = WiFi.softAPIP();
        DEBUG_INFORMATION_SERIAL.print("AP IP address: "); Serial.println(IP);
      }else{
        WiFi.disconnect();
        WiFi.reconnect();
        reconretries++;
      }
    }else{
      reconretries = 0;
    }
  }else{}
  delay(100);
 }
  
}
