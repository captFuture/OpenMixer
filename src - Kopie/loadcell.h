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