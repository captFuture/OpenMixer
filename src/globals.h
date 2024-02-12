#define xstr(a) str(a)
#define str(a) #a

#define DEBUG_ERRORS true
#define DEBUG_ERROR_SERIAL if(DEBUG_ERRORS)Serial

#define DEBUG_SENSOR true
#define DEBUG_SENSOR_SERIAL if(DEBUG_SENSOR)Serial

#define DEBUG_INFORMATION true
#define DEBUG_INFORMATION_SERIAL if(DEBUG_INFORMATION)Serial

#define DEBUG_NTPClient true

#define SAVE_SD
bool SDinserted = false;
int mqttretries = 10;

unsigned long pauseONE = 10000; //10 seconds
unsigned long oldMillisONE = 0;

unsigned long pauseTWO = 10000; //10 seconds
unsigned long oldMillisTWO = 0;
long randNumber;    

struct Serving {
  int servestatus = 0;
  int pump0  = 0;
  int pump1  = 0;
  int pump2  = 0;
  int pump3  = 0;
  int pump4  = 0;
  bool tare = true;
  int weight = 0;
  int led1 = 0;
  int led2 = 1;
  int displaypage = 0;
};
Serving serving;

int olddisplay = 3;

#define ARRAYSIZE 10
String pumps[ARRAYSIZE] = { "liquid0", "liquid1", "liquid2", "liquid3", "liquid4"};
const char *shout[ARRAYSIZE] = { "/shout/woooh.mp3", "/shout/bastard.mp3", "/shout/beautiful.mp3", "/shout/shutup.mp3", "/shout/bitemy.mp3", "/shout/hellopeasants.mp3", "/shout/gonnado.mp3", "/shout/imbender.mp3", "/shout/omg.mp3", "/shout/youkidding.mp3"};

struct Config {
  char liquid0[40] = xstr(LIQUID0);
  char liquid1[40] = xstr(LIQUID1);
  char liquid2[40] = xstr(LIQUID2);
  char liquid3[40] = xstr(LIQUID3);
  char liquid4[40] = xstr(LIQUID4);

  char clientId[40] = xstr(CLIENTID);
  char ssid[60] = xstr(SSID);
  char password[60] = xstr(PASSWORD);
  char mqttserver[60] = xstr(MQTTSERVER);
  char mqttuser[60] = xstr(MQTTUSER);
  char mqttpwd[60] = xstr(MQTTPWD);
  char mqttport[5] = xstr(MQTTPORT);
  char ntpserver[40] = xstr(NTPSERVER);
  bool NETworkmode = true;
  char version[20] = xstr(VERSION);
};
Config config;

// will be used for serving relays #define LED1 16
// will be used for serving relays #define LED2 17

#define SRELAY 16 //serving relay
#define CRELAY 17 //cleaning relay

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 36;
const int LOADCELL_SCK_PIN = 26;
const int LOAD_CELL_GAIN = 32;

const int HX711_dout = 36;      //mcu > HX711 dout pin
const int HX711_sck = 26;       //mcu > HX711 sck pin

float calibrationValue = 741.58;
int oldweight = 0;

int buttonPress;
int timeout = 500;
int LoadCellok = 0;

int complete = atoi(config.liquid0) + atoi(config.liquid1) + atoi(config.liquid2) + atoi(config.liquid3) + atoi(config.liquid4);// 100% bar height ~ 40+20+150=210
float maxheight = 200;
float factor = maxheight/complete;

const char sdFormat[] = "%s, %s, %s, %2.2f, %2.2f, %2.2f, %u, %u, %u, %2.2f, %u, %u, %u, %u,%u, %d";
/*
https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
*/

const char statusFormat[] = "{\"n\":\"%s\", \"ip\":\"%s\", \"rssi\":%d, \"s\":\"ONLINE\"}";
const char servingFormat[] = "{\"p0\":\"%d\", \"p1\":\"%d\", \"p2\":\"%d\", \"p3\":\"%d\", \"p4\":\"%d\", \"w\":\"%d\"}";


const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
char measureTime[30];

char msg[1024];
char msg1[1024];
char encmsg[1024];
char sdmsg[2000];

char encTopic[] = "openmixer/cocktail/enc";
char plainTopic[] = "openmixer/cocktail/plain";
char statusTopic[] = "openmixer/cocktail/status";
char servingTopic[] = "openmixer/cocktail/serving";
char inTopic[] = "openmixer/cocktail/cmd";
char clearSDcommand[] = "clearsd";