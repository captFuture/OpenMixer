#ifdef USE_M5MINISCALES
    while (!scales.begin(&Wire, 21, 22, DEVICE_DEFAULT_ADDR)) {
        Serial.println("scales connect error");
        M5.Lcd.print("scales connect error");
        delay(1000);
    }
    scales.setLEDColor(0x001000);
    LoadCellok = 1;
#else
    LoadCell.begin();
    unsigned long stabilizingtime = 2000; 
    boolean _tare = true;
    LoadCell.start(stabilizingtime, _tare);
    if (LoadCell.getTareTimeoutFlag()) {
        DEBUG_INFORMATION_SERIAL.println("Timeout, check MCU>HX711 wiring and pin designations");
        LoadCellok = 0;
    }else {
        LoadCell.setCalFactor(calibrationValue);
        DEBUG_INFORMATION_SERIAL.println("Startup is complete");
        LoadCellok = 1;
    }
#endif