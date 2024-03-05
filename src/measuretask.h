void loadCellHandling(){
    #ifdef USE_M5MINISCALES
    #else
        static boolean newDataReady = 0;
        if (LoadCell.update()) newDataReady = true;
        if(newDataReady){
            float weightf = LoadCell.getData();
            serving.weight=(int)weightf;
            if(weightf <= 0){ weightf = 0;}
            if(serving.weight <= 0){ serving.weight = 0;}
            newDataReady = 0;
        }
    #endif
}

void measuretaskCode(void* pvParameters) {
    while (1) {
        //Serial.print("measuretask Uptime (ms): ");
        //Serial.println(millis());
        //Serial.print("measuretask running on core ");
        //Serial.println(xPortGetCoreID());
        loadCellHandling();
        delay(100);  
    }
}