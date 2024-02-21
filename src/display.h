void setDisplay(int state){
  if(olddisplay != serving.displaypage){
    switch (state){
      case 0:
        if(SDinserted == true){
          M5.Lcd.drawJpgFile(SD, "/design/main_bg.jpg");
        }else{
          M5.Lcd.drawJpgFile(SPIFFS, "/main_bg.jpg");
        }
        olddisplay = state;
      break;
      case 1:
        M5.Lcd.clear();
        if(SDinserted == true){
          M5.Lcd.drawJpgFile(SD, "/design/done_bg.jpg");
        }else{
          M5.Lcd.drawJpgFile(SPIFFS, "/done_bg.jpg");
        }
        delay(2000);
        if(SDinserted == true){
          M5.Lcd.drawJpgFile(SD, "/design/main_bg.jpg");
        }else{
          M5.Lcd.drawJpgFile(SPIFFS, "/main_bg.jpg");
        }
        olddisplay = state;
        serving.displaypage = 0;
      break;
      case 2:

      break;
      case 3:

      break;
    }
  }
}

void showBar(int slone, int sltwo, int slthree, float factor){
  M5.Lcd.fillRect(161, 21, 146, 202, BLACK);
  M5.Lcd.drawRect(160, 20, 148, 204, TFT_DARKGREY);

  if(slone != 0){M5.Lcd.fillRect(161, 21, 146, (float)slone*factor, RED);}
  if(sltwo != 0){M5.Lcd.fillRect(161, (float)(21+slone)*factor, 146, (float)sltwo*factor, YELLOW);}
  if(slthree != 0){M5.Lcd.fillRect(161, (float)(21+slone+sltwo)*factor, 146, (float)slthree*factor, GREEN);}
  M5.Lcd.drawRoundRect(148, 0, 171, 238, 15, TFT_DARKGREY);
  //Todo - showing an actual bar
}

void switchDisplay(int onoff){
  if(onoff == 0){
    M5.Lcd.sleep();
    M5.Lcd.setBrightness(0);
    DEBUG_INFORMATION_SERIAL.println("Display off");
  }else{
    M5.Lcd.wakeup();
    M5.Lcd.setBrightness(200);
    DEBUG_INFORMATION_SERIAL.println("Display on");
  }
}

//top left
void showSDStatus(){
  if(SDinserted == true){
    M5.Lcd.drawRect(100, 0, 20, 20, TFT_DARKGREY);
    M5.Lcd.fillRect(101, 1, 18, 18, GREEN);
    M5.Lcd.drawString("S", 106, 3, 1);
  }else{
    M5.Lcd.drawRect(100, 0, 20, 20, TFT_DARKGREY);
    M5.Lcd.fillRect(101, 1, 18, 18, RED);
    M5.Lcd.drawString("S", 106, 3, 1);
  }
}

//top right
void showNetStatus(){
  if(config.NETworkmode == true){
    M5.Lcd.drawRect(122, 0, 20, 20, TFT_DARKGREY);
    M5.Lcd.fillRect(123, 1, 18, 18, GREEN);
    M5.Lcd.drawString("N", 126, 3, 1);
  }else{
    M5.Lcd.drawRect(122, 0, 20, 20, TFT_DARKGREY);
    M5.Lcd.fillRect(123, 1, 18, 18, RED);
    M5.Lcd.drawString("N", 126, 3, 1);
  }
}

//bottom right
void showLoadStatus(){
  if(LoadCellok == 1){
    M5.Lcd.drawRect(122, 22, 20, 20, TFT_DARKGREY);
    M5.Lcd.fillRect(123, 23, 18, 18, GREEN);
    M5.Lcd.drawString("W", 126, 24, 1);
  }else if(LoadCellok == 0){
    M5.Lcd.drawRect(122, 22, 20, 20, TFT_DARKGREY);
    M5.Lcd.fillRect(123, 23, 18, 18, RED);
    M5.Lcd.drawString("W", 126, 24, 1);
  }else{
    M5.Lcd.drawRect(122, 22, 20, 20, TFT_DARKGREY);
    M5.Lcd.fillRect(123, 23, 18, 18, BLUE);
    M5.Lcd.drawString("W", 126, 24, 1);
  }

}

void showDrinkWindow(){
    M5.Lcd.fillRect(29, 215, 40, 18, LIGHTGREY);
    M5.Lcd.drawRoundRect(148, 0, 171, 238, 15, TFT_DARKGREY);
    M5.Lcd.setCursor(10,225);
    M5.Lcd.setTextColor(BLACK);
    M5.lcd.setTextSize(2);
    M5.Lcd.drawNumber(serving.weight, 30, 216);
}

void updateDisplay(){
  showSDStatus();
  showNetStatus();
  showDrinkWindow();
  showLoadStatus();
  setDisplay(serving.displaypage);
}
