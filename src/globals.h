#define xstr(a) str(a)
#define str(a) #a

#define DEBUG_ERRORS true
#define DEBUG_ERROR_SERIAL if(DEBUG_ERRORS)Serial

#define DEBUG_SENSOR true
#define DEBUG_SENSOR_SERIAL if(DEBUG_SENSOR)Serial

#define DEBUG_INFORMATION true
#define DEBUG_INFORMATION_SERIAL if(DEBUG_INFORMATION)Serial

#define SAVE_SD
bool SDinserted = false;

#define FWURL "http://www.mrtarantl.online/ota/openmixer/alex/openmixer_v" 

String fwVersionURL = "";

int totalLength;       //total size of firmware
int currentLength = 0; //current size of written firmware

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
  int pump5  = 0;
  int pump6  = 0;
  int pump7  = 0;
  bool tare = true;
  int weight = 0;
  int led1 = 0;
  int led2 = 1;
  int displaypage = 0;
};
Serving serving;

int olddisplay = 3;
int reconretries = 0;

#define ARRAYSIZE 10
#define FWversion xstr(VERSION)

String pumps[ARRAYSIZE] = { "liquid0", "liquid1", "liquid2", "liquid3", "liquid4", "liquid5", "liquid7", "liquid7"};
const char *shout[ARRAYSIZE] = { "/shout/woooh.mp3", "/shout/bastard.mp3", "/shout/beautiful.mp3", "/shout/shutup.mp3", "/shout/bitemy.mp3", "/shout/hellopeasants.mp3", "/shout/gonnado.mp3", "/shout/imbender.mp3", "/shout/omg.mp3", "/shout/youkidding.mp3"};

struct Config {
  char liquid0[40] = xstr(LIQUID0);
  char liquid1[40] = xstr(LIQUID1);
  char liquid2[40] = xstr(LIQUID2);
  char liquid3[40] = xstr(LIQUID3);
  char liquid4[40] = xstr(LIQUID4);
  char liquid5[40] = xstr(LIQUID5);
  char liquid6[40] = xstr(LIQUID6);
  char liquid7[40] = xstr(LIQUID7);

  char clientId[40] = xstr(CLIENTID);
  char ssid[60] = xstr(SSID);
  char password[60] = xstr(PASSWORD);
  bool NETworkmode = true;
  char version[20] = xstr(VERSION);
  char mode[20] = xstr(MODE);
  char pumps[5] = xstr(PUMPS);
};
Config config;

// will be used for serving relays #define LED1 16
// will be used for serving relays #define LED2 17



// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 36;
const int LOADCELL_SCK_PIN = 26;
const int LOAD_CELL_GAIN = 32;

const int HX711_dout = 36;      //mcu > HX711 dout pin
const int HX711_sck = 26;       //mcu > HX711 sck pin

float calibrationValue = 1020;
int oldweight = 0;
int16_t configNum = 0;

int buttonPress;
int timeout = 500;
int LoadCellok = 0;

int complete = atoi(config.liquid0) + atoi(config.liquid1) + atoi(config.liquid2) + atoi(config.liquid3) + atoi(config.liquid4) + atoi(config.liquid5) + atoi(config.liquid6) + atoi(config.liquid7);
float maxheight = 200;
float factor = maxheight/complete;

const char sdFormat[] = "%s, %s, %s, %2.2f, %2.2f, %2.2f, %u, %u, %u, %2.2f, %u, %u, %u, %u,%u, %d";
/*
https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
*/

const char statusFormat[] = "{\"n\":\"%s\", \"ip\":\"%s\", \"rssi\":%d, \"s\":\"ONLINE\"}";
const char servingFormat[] = "{\"p0\":\"%d\", \"p1\":\"%d\", \"p2\":\"%d\", \"p3\":\"%d\", \"p4\":\"%d\", , \"p5\":\"%d\", \"p6\":\"%d\", \"p7\":\"%d\", \"w\":\"%d\"}";


const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
char measureTime[30];

char msg[1024];
char msg1[1024];
char encmsg[1024];
char sdmsg[2000];

/*char encTopic[] = "openmixer/cocktail/enc";
char plainTopic[] = "openmixer/cocktail/plain";
char statusTopic[] = "openmixer/cocktail/status";
char servingTopic[] = "openmixer/cocktail/serving";
char inTopic[] = "openmixer/cocktail/cmd";
char clearSDcommand[] = "clearsd";*/

