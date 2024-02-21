#define FILENAME "/config.json"
//#define URL "http://www.mrtarantl.online/openmixer/alex/data/config.json"
File f;

void getSDcontent() {
  // check if test file exists and delete it if needed
  //if(SD.exists(FILENAME))
  //  SD.remove(FILENAME);

  // try to download a file
/*
  int httpCode;
  int error;
  Serial.println(F("Downloading: " URL));
  f = SD.open(FILENAME, "w");
  if (f){
    httpclient.begin(URL);
    httpCode = httpclient.GET();
    switch(httpCode)
    {
      case HTTP_CODE_OK:
        error = httpclient.writeToStream(&f);
        Serial.printf("Error code: %i\r\n", error);
        break;

      default:
        Serial.println(F("[HTTP] GET failed, error: "));
        Serial.printf("%i - %s\r\n", httpCode, httpclient.errorToString(httpCode).c_str());
        Serial.println(F(URL));
        break;
    }
    f.close();
  }
  httpclient.end();
*/
  // output file content
  Serial.println(F("Reading file content"));
  Serial.println(F("---"));
  File root = SD.open("/");
  File file = root.openNextFile();
 
  while(file){
      Serial.print("FILE: ");
      Serial.println(file.name());
      file = root.openNextFile();
  }
  Serial.println(F("---"));

  f = SD.open("/config.json", "r");
  String content = f.readString();
  Serial.println(content);
  f.close();
}