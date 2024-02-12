void loadCellHandling(){
  static boolean newDataReady = 0;
  const int serialPrintInterval = 10;
  
  if (LoadCell.update()) newDataReady = true;
  if (newDataReady){
      float weightf = LoadCell.getData();
      serving.weight=(int)weightf;
      if(weightf <= 0){ weightf = 0;}

      if(serving.weight <= 0){ serving.weight = 0;}
      newDataReady = 0;
  }
}

void measuretaskCode(void* pvParameters) {
    while (1) {
        //Serial.print("measuretask Uptime (ms): ");
        //Serial.println(millis());
        //Serial.print("measuretask running on core ");
        //Serial.println(xPortGetCoreID());
        loadCellHandling();

        delay(200);
    }
}