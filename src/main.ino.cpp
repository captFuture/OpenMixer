# 1 "C:\\Users\\profs\\AppData\\Local\\Temp\\tmpa4lsvno9"
#include <Arduino.h>
# 1 "C:/Users/profs/OneDrive/Dokumente/PlatformIO/Projects/OpenMixer/src/main.ino"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include "globals.h"
#include <Arduino.h>


#include <M5Stack.h>
#include <M5GFX.h>
#include "UNIT_4RELAY.h"

#ifdef USE_M5MINISCALES
  #include "UNIT_SCALES.h"
  UNIT_SCALES scales;
#else
  #include <HX711_ADC.h>
  HX711_ADC LoadCell(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
#endif



#include <SPI.h>
#include <WiFi.h>

#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <Update.h>



WiFiClient wifiClient;
HTTPClient httpclient;
UNIT_4RELAY relay;
TaskHandle_t servetask;
TaskHandle_t measuretask;

M5GFX display;
M5Canvas canvas(&display);

const int calVal_eepromAdress = 0;
unsigned long t = 0;


#include <filedownload.h>
#include <display.h>
#include <sdfunctions.h>
#include <functions.h>
#include <servetask.h>
#include <measuretask.h>
void setup();
void loop();
#line 50 "C:/Users/profs/OneDrive/Dokumente/PlatformIO/Projects/OpenMixer/src/main.ino"
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
  DEBUG_INFORMATION_SERIAL.print("Current firmware: v"); Serial.println(FWversion);
  DEBUG_INFORMATION_SERIAL.print("Pumps: "); Serial.println(config.pumps);
  DEBUG_INFORMATION_SERIAL.println("Starting...");

  #include <network.h>
  #include <loadcell.h>

  relay.begin();
  relay.Init(1);





  setDisplay(serving.displaypage);

  #ifdef USE_M5MINISCALES
    scales.setOffset();
  #else

  #endif


}

void loop() {
  M5.update();

  #ifdef USE_M5MINISCALES
    float weightf = scales.getWeight();
    serving.weight=(int)weightf;
    if(weightf <= 0){ weightf = 0;}
    if(serving.weight <= 0){ serving.weight = 0;}
  #else

  #endif

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