void printLocalTime(){
  //Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));
    if (!getLocalTime(&timeinfo)){
      DEBUG_INFORMATION_SERIAL.println("Failed to obtain time");
    }
  int second = rtc.getSecond();
  int minute = rtc.getMinute();
  int hour = rtc.getHour(true)-1;
  int day = rtc.getDay();
  int month = rtc.getMonth() + 1;
  int year = rtc.getYear();
  int weekday = rtc.getDayofWeek() +1;

  sprintf(measureTime, "%i/%i/%i %i:%i:%i", day, month, year, hour,minute, second);
  DEBUG_INFORMATION_SERIAL.print("Time: "); DEBUG_INFORMATION_SERIAL.println(measureTime);

  M5.lcd.fillRect(0, 210, 100, 30, BLACK);
  M5.lcd.setCursor(0, 210);
  M5.lcd.printf("time: %s", measureTime);
}

void SetTime(String str){
  //String str = "00,30,12,21,02,1976";
  String strs[6];
  int StringCount = 0;

  while (str.length() > 0){
    int index = str.indexOf(',');
    if (index == -1)
    {
      strs[StringCount++] = str;
      break;
    }
    else
    {
      strs[StringCount++] = str.substring(0, index);
      str = str.substring(index+1);
    }
  }
  for (int i = 0; i < StringCount; i++)
    {
      Serial.print(i);
      Serial.print(": \"");
      Serial.print(strs[i]);
      Serial.println("\"");
    }
  rtc.setTime(strs[0].toInt(), strs[1].toInt(), strs[2].toInt(), strs[3].toInt(), strs[4].toInt(), strs[5].toInt());
  DEBUG_INFORMATION_SERIAL.println(rtc.getTime("%d/%m/%Y %H:%M:%S"));
}
