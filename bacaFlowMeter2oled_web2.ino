#include <SPI.h>              //Library SPI
#include <Wire.h>             //Library Wire
#include <Adafruit_GFX.h>     //Library GFX
#include <Adafruit_SSD1306.h> //Library OLED SSD1306
#define SCREEN_WIDTH 128 //Panjang LCD OLED
#define SCREEN_HEIGHT 64 //Tinggi LCD OLED
#define OLED_RESET -1    //Pin reset terhubung dengan arduino
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiAP.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "ArduinoJson.h"
int sensorPin = 14;
float bootvol;
int pulseOld;
double volume;
double volume2;
double flowRate;
char fr1[10];
char fr2[10] ;
char vl1[10];
char vl2[10];
double flowRate2;
volatile long pulse;
volatile long pulse2;
RTC_DATA_ATTR char bootVol[10];

int flagWifi = 0;
unsigned long lastTime;
int flagCfg = 0;
long eventTime_1_Oled = 2000;
long eventTime_2_Post = 10000;
long eventTime_2_Old = 10000;
unsigned long eventTime_3_Bt = 5000;
unsigned long eventTime_4_wf = 1000;

unsigned long previousTime_1 = 0;
unsigned long previousTime_2 = 0;
unsigned long previousTime_3 = 0;
unsigned long previousTime_4 = 0;

String ssid = "";
String password = "";
const char*  serverName = "http://192.168.242.95:1880/update-sensor";
int bat = 0;
StaticJsonDocument<200> doc;
//blutut
int pinButton = 4  ;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// Create AsyncWebServer object on port 80
AsyncWebServer server(8080);


void setup() {
  SPIFFS.begin();
  pinMode(sensorPin, INPUT);
  pinMode(pinButton, INPUT_PULLUP);
  Serial.begin(115200);
  getConfigFs();
  connectWifi();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { //Alamat OLED
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  attachInterrupt(digitalPinToInterrupt(sensorPin), increase, RISING);
  //delay(5000);
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  setModemSleep();
}

void loop() {
  // put your main code here, to run repeatedly:
  flowRate = 2.0954 * pulse / 1000 * 30;
  flowRate2 = flowRate / 1000 * 60;

  volume = 2.0954 * pulse2 / 1000;
  volume2 = volume / 1000;
  unsigned long currentTime = millis();
  if (currentTime - previousTime_1 >= eventTime_1_Oled) {
    pulse = 0;
    lastTime = millis();
    //Serial.print(flowRate);
    //Serial.println(volume2, 6);
    tampilOled();
    previousTime_1 = currentTime;
  }
  if (currentTime - previousTime_2 >= eventTime_2_Post) {
    if (pulse2 != pulseOld) {
      Serial.println(pulse2);
      writefileSTR((String)pulse2, "/dataVol.txt");
    }
    if (flagCfg != 1) {
      if (flagWifi == 0) {
        wakeModemSleep();
        flagWifi=1;

      }
      //Serial.println(WiFi.status());
      if (WiFi.status() != WL_CONNECTED) {
        eventTime_2_Post = 1000;
        flagWifi++;
        //    Serial.println(flagWifi);
        if (flagWifi > 10) {
          setModemSleep();
          eventTime_2_Post = eventTime_2_Old;
          flagWifi = 0;
        }
      }

      else {
       if( WiFi.status() == WL_CONNECTED){
        postServer();
        sendWifiOled();
        setModemSleep();
        eventTime_2_Post = eventTime_2_Old;
        flagWifi = 0;}
      }


    }
    previousTime_2 = currentTime;
  }
  if (currentTime - previousTime_3 >= eventTime_3_Bt) {
    int btn = digitalRead(pinButton);
    if (btn == 0) {
      //Serial.println("modeAp");
      flagCfg = 1;
      ModemAp();
      eventTime_3_Bt = 60000;
      //previousMillis = millis();
    }
    else {
      if (flagCfg == 1) {
        flagCfg = 0;
        setModemSleep();
      }
      eventTime_3_Bt = 1000;
    }
    previousTime_3 = currentTime;
  }
}
ICACHE_RAM_ATTR void increase() {
  pulse++;
  pulse2++;
}
