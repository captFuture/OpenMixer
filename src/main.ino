#include <ArduinoJson.h>
#include <HTTPClient.h>
#include "globals.h"
#include <Arduino.h>
#include <M5Stack.h>
#include <SPIFFS.h>
#include <HX711_ADC.h>

#include "UNIT_4RELAY.h"

/* wifi  */
#include <SPI.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <Update.h>

/* wifimanager */
#include <WiFiManager.h>

#define FWURL "http://www.mrtarantl.online/ota/openmixer/openmixer_v" 


WiFiClient wifiClient;
HTTPClient httpclient;
HX711_ADC LoadCell(HX711_dout, HX711_sck);

UNIT_4RELAY relay;

TaskHandle_t servetask;
TaskHandle_t measuretask;
TaskHandle_t displaytask;

const int calVal_eepromAdress = 0;
unsigned long t = 0;

/* additional */

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

  Serial.begin(115200);
  if (SPIFFS.begin()) {
		Serial.println("SPIFFS MOUNTED");
	}
  delay(10);

  DEBUG_INFORMATION_SERIAL.print("Networkmode: "); DEBUG_INFORMATION_SERIAL.println(config.NETworkmode); 
  DEBUG_INFORMATION_SERIAL.println();
  DEBUG_INFORMATION_SERIAL.print("Current firmware: v");  Serial.println(FWversion);
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

 if(config.NETworkmode){
    checkupdate();
 }

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

    delay(100);
  }
  
}
