if(config.NETworkmode){
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
}else{}