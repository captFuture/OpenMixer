void sendDeviceStatus()
{
  //String sendtime = rtc.getTime("%d/%m/%Y %H:%M:%S");
  //DEBUG_INFORMATION_SERIAL.print("sendtime: ");
  //DEBUG_INFORMATION_SERIAL.println(sendtime);
  sprintf(msg, statusFormat, config.clientId, ip2Str(WiFi.localIP()), WiFi.RSSI());
  if (client.publish(statusTopic, msg))
  {
  }
}

void sendSensors(){
  sprintf(sdmsg,sdFormat,measureTime,config.clientId,WiFi.RSSI());
  DEBUG_INFORMATION_SERIAL.println(sdmsg);
  String encoded = base64::encode(sdmsg);
  DEBUG_INFORMATION_SERIAL.println(encoded);

  if (client.publish(encTopic, encoded.c_str())){
    DEBUG_INFORMATION_SERIAL.println("Publish ok");
  } else {
    DEBUG_ERROR_SERIAL.println("Publish failed");
  }
  
  if (client.publish(plainTopic, sdmsg)){
    DEBUG_INFORMATION_SERIAL.println("Publish ok");
  } else {
    DEBUG_ERROR_SERIAL.println("Publish failed");
  }
}

void callback(char *topic, byte *payload, unsigned int length){
  DEBUG_INFORMATION_SERIAL.println("Message arrived");
  char json[length + 1];
  strncpy(json, (char *)payload, length);
  json[length] = '\0';

  DEBUG_INFORMATION_SERIAL.print("Topic: ");
  DEBUG_INFORMATION_SERIAL.println(topic);
  DEBUG_INFORMATION_SERIAL.print("Message: ");
  DEBUG_INFORMATION_SERIAL.println(json);

  // Decode JSON request
  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, (char *)json);
  if (error){
      Serial.println(F("Failed to read payload"));      
  }
     int command = doc["command"]; // 
    DEBUG_INFORMATION_SERIAL.print("COMMAND: ");
    DEBUG_INFORMATION_SERIAL.println(command);

    if(command == 1){
    DEBUG_INFORMATION_SERIAL.println("Clearing SD content");
      clearSDcontent();
    }
    if(command == 2){
    DEBUG_INFORMATION_SERIAL.println("Rebooting device");
      ESP.restart();
    }

    if(command == 3){
    DEBUG_INFORMATION_SERIAL.println("Sending device Status");
      sendDeviceStatus();
    }
    if(command == 4){
    DEBUG_INFORMATION_SERIAL.println("Set Time");
      String mqttime = doc["time"];
      SetTime(mqttime);
    }
    if(command == 5){
    DEBUG_INFORMATION_SERIAL.println("Make Drink");
      switchDisplay(1);
      buttonPress = 0;
      DEBUG_INFORMATION_SERIAL.println("MAKING DRINK");
      LoadCell.tare();
      delay(100);
      serving.servestatus = 1;
      serving.led1 = 1;
      serving.led2 = 1;
      serving.pump0 = 1;
    }
}

void initManagedDevice()
{
  if (client.subscribe(inTopic))
  {
    DEBUG_INFORMATION_SERIAL.println("subscribe to inTopic OK");
  }
  else
  {
    DEBUG_ERROR_SERIAL.println("subscribe to inTopic FAILED");
  }

  if (client.subscribe(statusTopic))
  {
    sendDeviceStatus();
    DEBUG_INFORMATION_SERIAL.println("device statusTopic Manage ok");
  }
  else
  {
    DEBUG_ERROR_SERIAL.println("device Manage failed");
  }
}

void reconnect()
{
  while (!client.connected())
  {
  if(config.NETworkmode){
    DEBUG_INFORMATION_SERIAL.print("Attempting MQTT connection...");
    DEBUG_INFORMATION_SERIAL.println(config.mqttserver);

    if (client.connect(config.clientId, config.mqttuser, config.mqttpwd))
    {
      DEBUG_INFORMATION_SERIAL.println("connected");
      DEBUG_INFORMATION_SERIAL.print("state:");
      DEBUG_INFORMATION_SERIAL.println(client.state());
      client.setBufferSize(512);
      delay(1000);
      initManagedDevice();
    }
    else
    {
      DEBUG_ERROR_SERIAL.print("failed, rc=");
      DEBUG_ERROR_SERIAL.println(client.state());
      DEBUG_ERROR_SERIAL.print("Mqttretries: ");  DEBUG_ERROR_SERIAL.println(mqttretries);

      delay(5000);
      mqttretries = mqttretries -1;
      if(mqttretries <= 0){
        config.NETworkmode = false;
        return;
      }
    }
  }
  }
}

