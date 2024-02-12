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

void buttonHandling(){
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

//----------------------------------------------------------------------------------------------------------------------
// Function to update firmware incrementally
// Buffer is declared to be 128 so chunks of 128 bytes
// from firmware is written to device until server closes
void updateFirmware(uint8_t *data, size_t len){
  Update.write(data, len);
  currentLength += len;
  // Print dots while waiting for update to finish
  //Serial.print('.');
  // if current length of written firmware is not equal to total firmware size, repeat
  if(currentLength != totalLength) return;
  Update.end(true);
  Serial.printf("\nUpdate Success, Total Size: %u\nRebooting...\n", currentLength);
  // Restart ESP32 to see changes 
  ESP.restart();
}

void checkupdate(){
  // Connect to external web server
  Serial.println("Checking if new firmware is available.");

  int fwNewVersion = atoi(FWversion)+1; //cerca la versione successiva del firmware.
  String fwVersionURL = FWURL + String(fwNewVersion) + ".bin";
   
  httpclient.begin(fwVersionURL);
  // Get file, just to check if each reachable
  int resp = httpclient.GET();
  Serial.print("Response: ");
  Serial.println(resp);
  // If file is reachable, start downloading
  if(resp == 200){
      // get length of document (is -1 when Server sends no Content-Length header)
      totalLength = httpclient.getSize();
      // transfer to local variable
      int len = totalLength;
      // this is required to start firmware update process
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
