void switchLed(int name, int status){
    digitalWrite(name, status);
}

String ip2Str(IPAddress ip){
  String s="";
  for (int i=0; i<4; i++) {
    s += i  ? "." + String(ip[i]) : String(ip[i]);
  }
  return s;
}


//----------------------------------------------------------------------------------------------------------------------
void updateFirmware(uint8_t *data, size_t len){
  Update.write(data, len);
  currentLength += len;
  if(currentLength != totalLength) return;
  Update.end(true);
  Serial.printf("\nUpdate Success, Total Size: %u\nRebooting...\n", currentLength);
  ESP.restart();
}

void checkupdate(){
  Serial.println("Checking SD content");
  getSDcontent(); 


  Serial.println("Checking if new firmware is available.");
  int fwNewVersion = atoi(FWversion)+1;
  fwVersionURL = FWURL + String(fwNewVersion) + ".bin";
  DEBUG_INFORMATION_SERIAL.print("Online Firmware url: ");  Serial.println(fwVersionURL); 
  httpclient.begin(fwVersionURL);
  // Get file, just to check if each reachable
  int resp = httpclient.GET();
  Serial.print("Response: ");
  Serial.println(resp);
  // If file is reachable, start downloading
  if(resp == 200){
      totalLength = httpclient.getSize();
      int len = totalLength;

      Update.begin(UPDATE_SIZE_UNKNOWN);
      Serial.printf("FW Size: %u\n",totalLength);
      // create buffer for read
      uint8_t buff[128] = { 0 };
      // get tcp stream
      WiFiClient * stream = httpclient.getStreamPtr();
      // read all data from server
      Serial.println("Updating firmware...");
      while(httpclient.connected() && (len > 0 || len == -1)) {
           // get available data size
           size_t size = stream->available();
           if(size) {
              // read up to 128 byte
              int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
              // pass to function
              updateFirmware(buff, c);
              if(len > 0) {
                 len -= c;
              }
           }
           delay(1);
      }
  }else{
    Serial.println("Cannot download firmware file.");
  }
  httpclient.end();

}



void buttonHandling(){
  if (M5.BtnA.pressedFor(5000)) {
    if(config.NETworkmode){
      checkupdate();
    }
    buttonPress = 0;
    delay(2000);
  }

  if (M5.BtnB.pressedFor(5000)) {
    //clearSDcontent();
    buttonPress = 0;
    delay(2000);
  }

  if (M5.BtnC.pressedFor(5000)) {
    //writeSDcontent();
    buttonPress = 0;
    delay(2000);
  }

  if(buttonPress >= 100){
    switchDisplay(0);
    buttonPress = 0;
  }

  if (M5.BtnA.wasPressed()) {
    switchDisplay(1);
    buttonPress = 0;
    DEBUG_INFORMATION_SERIAL.println("Taring scale.");
    LoadCell.tare();
    delay(100);
    serving.servestatus = 0;
    serving.led1 = 0;
    serving.led2 = 0;
  } else {
  }

  if (M5.BtnB.wasPressed()) {
    switchDisplay(1);
    buttonPress = 0;
    DEBUG_INFORMATION_SERIAL.println("MAKING DRINK");
    LoadCell.tare();
    delay(100);
    serving.servestatus = 1;
    serving.led1 = 1;
    serving.led2 = 1;
    serving.pump0 = 1;
    //playAudio(0);
  } else {
  }

  if (M5.BtnC.wasPressed()) {
    switchDisplay(1);
    buttonPress = 0;
    DEBUG_INFORMATION_SERIAL.println("CANCELLING DRINK");
    serving.servestatus = 0;
    serving.led1 = 0;
    serving.led2 = 0;
    
  } else {
  }
}