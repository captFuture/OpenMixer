#define FILENAME "/config.json"
File f;

void getSDcontent() {
  Serial.println(F("Reading SD content"));
  Serial.println(F("---"));
  File root = SD.open("/");
  File file = root.openNextFile();
 
  while(file){
      Serial.print("FILE: ");
      Serial.println(file.name());
      file = root.openNextFile();
  }
  Serial.println(F("---"));

  File sddrinks = SD.open("/drinks");
  File drink = sddrinks.openNextFile();
 
  while(drink){
      Serial.print("DRINKS: ");
      Serial.println(drink.name());
      drink = sddrinks.openNextFile();
  }
  Serial.println(F("---"));
  f = SD.open("/config.json", "r");
  String content = f.readString();
  Serial.println(content);
  f.close();
  Serial.println(F("---"));
}