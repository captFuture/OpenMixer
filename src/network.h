if(config.NETworkmode){
  if(strcmp(config.mode, "client") == 0){
    //connect to Network in config.json
    DEBUG_INFORMATION_SERIAL.println("Wifi Mode Client");
    WiFi.mode(WIFI_STA);
    WiFi.hostname(config.clientId);
    WiFi.setHostname(config.clientId);
    WiFi.begin(config.ssid, config.password);
    DEBUG_INFORMATION_SERIAL.println("Connecting");
    int retries = 0;
    while(WiFi.status() != WL_CONNECTED) { 
      delay(500);
      DEBUG_INFORMATION_SERIAL.print("retry "); DEBUG_INFORMATION_SERIAL.println(retries);
      if(retries >= 10){
        //config.NETworkmode = false;
        strncpy(config.mode, "ap", sizeof config.mode);
        
        DEBUG_INFORMATION_SERIAL.println("Wifi Mode Accesspoint");
        WiFi.mode(WIFI_AP);
        WiFi.softAP(config.ssid, config.password);
        IPAddress IP = WiFi.softAPIP();
        DEBUG_INFORMATION_SERIAL.print("AP IP address: "); Serial.println(IP);
        break;
      }
      retries++;
    }
    if(strcmp(config.mode, "client") == 0){
      DEBUG_INFORMATION_SERIAL.println("");
      DEBUG_INFORMATION_SERIAL.print("Connected to WiFi network with IP Address: ");
      DEBUG_INFORMATION_SERIAL.println(WiFi.localIP());
    }
  }else{
    //Start Accesspoint defined in config.json
    DEBUG_INFORMATION_SERIAL.println("Wifi Mode Accesspoint");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(config.ssid, config.password);
    IPAddress IP = WiFi.softAPIP();
    DEBUG_INFORMATION_SERIAL.print("AP IP address: "); Serial.println(IP);
  }

}else{}


/*
    WiFi.mode(WIFI_STA);
    WiFiManager wm;
    wm.setDebugOutput(true);
    wm.setConfigPortalTimeout(timeout);
    wm.preloadWiFi(config.ssid, config.password);
    bool res;
    res = wm.autoConnect(config.clientId);
    if(!res) {
      DEBUG_INFORMATION_SERIAL.println("Failed to connect");
      config.NETworkmode = false;
    }else {
      DEBUG_INFORMATION_SERIAL.println("WiFi connected");
      DEBUG_INFORMATION_SERIAL.print("IP address: ");
      DEBUG_INFORMATION_SERIAL.println(WiFi.localIP());
    }
*/