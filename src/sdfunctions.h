void initializeSD(){

    if (!SD.begin()) {
        SDinserted = false;
        DEBUG_ERROR_SERIAL.println("SDCard failed, or not present"); 
    }else{
        SDinserted = true;
        DEBUG_INFORMATION_SERIAL.println("SDCard present"); 
    }
    if(SDinserted){
        if (SD.exists("/madedrinks.csv")) {
            DEBUG_INFORMATION_SERIAL.println("drinks.csv exists.");
            File drinksFile = SD.open("/madedrinks.csv", FILE_APPEND);
            drinksFile.println("exists NEW DATA ----------");
            drinksFile.close();
        } else {
            DEBUG_ERROR_SERIAL.println("madedrinks.csv doesn't exist.");
            File drinksFile = SD.open("/madedrinks.csv", FILE_WRITE);
            int written = drinksFile.println("does not exist NEW FILE ----------");
            DEBUG_INFORMATION_SERIAL.println(written);
            drinksFile.close();
        }
    }
}


void readConfig(){
    if(SDinserted == true){
        File configFile = SD.open("/config.json", FILE_READ);
        DEBUG_INFORMATION_SERIAL.print("Reading config from SD: ");


        StaticJsonDocument<512> doc;
        DeserializationError error = deserializeJson(doc, configFile);
        if (error){
            Serial.println(F("Failed to read file, using default configuration"));      
        }else{
            serializeJsonPretty(doc, Serial);
        }

        strlcpy(config.liquid0, doc["liquid0"] | xstr(LIQUID0), sizeof(config.liquid0));
        strlcpy(config.liquid1, doc["liquid1"] | xstr(LIQUID1), sizeof(config.liquid1));
        strlcpy(config.liquid2, doc["liquid2"] | xstr(LIQUID2), sizeof(config.liquid2));
        strlcpy(config.liquid3, doc["liquid3"] | xstr(LIQUID3), sizeof(config.liquid3));
        strlcpy(config.liquid4, doc["liquid4"] | xstr(LIQUID4), sizeof(config.liquid4));
        strlcpy(config.liquid4, doc["liquid5"] | xstr(LIQUID4), sizeof(config.liquid5));
        strlcpy(config.liquid4, doc["liquid6"] | xstr(LIQUID4), sizeof(config.liquid6));
        strlcpy(config.liquid4, doc["liquid7"] | xstr(LIQUID4), sizeof(config.liquid7));

        strlcpy(config.clientId, doc["clientid"] | xstr(CLIENTID), sizeof(config.clientId));
        strlcpy(config.ssid, doc["ssid"] | xstr(SSID), sizeof(config.ssid));
        strlcpy(config.password, doc["password"] | xstr(PASSWORD), sizeof(config.password));
        config.NETworkmode = doc["networkmode"] | false;

        configFile.close();
    }else{
        DEBUG_INFORMATION_SERIAL.println("SD not present - config not readable");
    }
    
}

void writePayload(){
    if(SDinserted == true){
        File sensorFile = SD.open("/madedrinks.csv", FILE_APPEND);
        sprintf(sdmsg, sdFormat, measureTime, config.clientId, WiFi.RSSI());
        DEBUG_INFORMATION_SERIAL.print("Writing madedrinks to SD: ");
        int written = sensorFile.println(sdmsg);
        DEBUG_INFORMATION_SERIAL.println(written);
        //DEBUG_SENSOR_SERIAL.println(sdmsg);
        sensorFile.close();
    }else{
        sprintf(sdmsg, sdFormat, measureTime, config.clientId, WiFi.RSSI());
        DEBUG_INFORMATION_SERIAL.println(sdmsg);
        DEBUG_INFORMATION_SERIAL.println("SD not present - not writing");
    }
    
}

void clearSDcontent(){
    if(SDinserted == true){
        SD.remove("/madedrinks.csv");
        File drinksFile = SD.open("/madedrinks.csv", FILE_WRITE);
        DEBUG_INFORMATION_SERIAL.println("SDcard cleared - new madedrinks.csv added");
        drinksFile.close();
    }else{
        DEBUG_INFORMATION_SERIAL.println("SD not present - not clearing");
    }
}

void writeSDcontent(){
    if(SDinserted == true){
        SD.remove("/config.json");
        File configFile = SD.open("/config.json", FILE_WRITE);
        String standardconfig = "{\n  \"clientid\": \"Maker_001\",\n  \"liquid0\": \"0\", \n  \"liquid1\": \"41\",\n  \"liquid2\": \"21\",\n  \"liquid3\": \"151\",\n  \"liquid4\": \"0\",\n  \"liquid5\": \"0\",\n  \"liquid6\": \"0\",\n  \"liquid7\": \"0\",\n \"ssid\": \"bender\",\n  \"password\": \"denber01\",\n  \"mqttserver\": \"bender.local\",\n  \"mqttuser\": \"bender\",\n  \"mqttpwd\": \"denber01\",\n  \"mqttport\": \"1883\",\n  \"ntpserver\":\"pool.ntp.org\",\n  \"networkmode\":false\n}";
        int written = configFile.println(standardconfig);
        DEBUG_INFORMATION_SERIAL.println(written);
        DEBUG_SENSOR_SERIAL.println(sdmsg);
        
        DEBUG_INFORMATION_SERIAL.println("Writing standard Config config.json added");
        configFile.close();
    }else{
        DEBUG_INFORMATION_SERIAL.println("SD not present - not writing standard config");
    }
}

