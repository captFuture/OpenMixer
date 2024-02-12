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
    clearSDcontent();
    buttonPress = 0;
    delay(2000);
  }

  if (M5.BtnC.pressedFor(5000)) {
    writeSDcontent();
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

