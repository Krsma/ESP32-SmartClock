#include <DHT.h>
#include <WiFi.h>
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "TimeApi.h"
#include "font14.h"
#include "font10.h"
#include "font.h"
//#include "tools.h"
#include "weather.h"
#include "wolfram.h"
//                             __
//                            |  |
//              ___       ____|  |____
//            /  _  \    |____    ____|
//           /  / \  \        |  |
//          /  /___\  \       |__|
//         /   _____   \      
//        /   /     \   \
//       /   /       \   \
//      /___/         \___\
//
//
//Setup pins
//static const uint8_t D0   = 16;
//static const uint8_t D1   = 5;
//static const uint8_t D2   = 4;
//static const uint8_t D3   = 0;
//static const uint8_t D4   = 2;
//static const uint8_t D5   = 14;
//static const uint8_t D6   = 12;
//static const uint8_t D7   = 13;
//static const uint8_t D8   = 15;
//static const uint8_t D9   = 3;
//static const uint8_t D10  = 1;
static const uint8_t BP  = 22;
bool state=false;
String arr[][4]={
              {"50","10","Temperatura:",""},
              {"72","10","Sobna temperatura:",""},
              {"94","10","Osecaj temperature:",""},
              {"116","10","Vazdusni pritisak:",""},
              {"138","10","Vlaznost vazduha:",""},
              {"160","10","Sobna vlaznost vazduha:",""},
              {"182","10","Izlazak-Zalazak:",""},
              {"204","10","Vetar:","m/s"},
              {"204","150","Vreme:","20:43"},
              {"226","10","Oblacnost:","100%"},
              {"226","150","Datum:","25/8/18"},
              };


String arout[13];
#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();


const char* ssid = "JJZ";
const char* password = "JJZ_akademik4";
//const char* ssid = "Nemanja";
//const char* password = "index1894";
//const char* ssid = "Ognjanovic";
//const char* password = "arhitekta38";

int previd=0;

#define BG 1535
//Setup Display
int countChr(String string,String item){
  int counter=0;
  while(string.indexOf(item)!=-1){
    yield();
    counter++;
    string=string.substring(string.indexOf(item)+1,string.length());
  }
  return counter;
}
#define TFT_DC 4
#define TFT_CS 15
#define TFT_RST 2
#define TFT_MISO 23
#define TFT_MOSI 18
#define TFT_CLK 19

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
//Setup DHT
//DHT dht(2, DHT11);
class Weather{
  public:
    void load(){
      //Draw stationary objects
      tft.setTextColor(ILI9341_WHITE);
      tft.fillRect(0,0,320,30,tft.color565(0, 150, 205));
      tft.drawLine(0,30,320,30,ILI9341_WHITE);
      tft.drawLine(0,31,320,31,ILI9341_WHITE);
      tft.drawLine(0,32,320,32,ILI9341_WHITE);
      //tft.drawLine(160,188,160,230,ILI9341_WHITE);
      tft.setFont(&Supermarketed14pt7b);
      tft.setCursor(120,26);
      tft.println("Vreme");
      
      //reset wdt
      yield();
    }
    void reload(){
      tft.setTextColor(ILI9341_WHITE);
      tft.fillRect(0,33,320,240,tft.color565(0, 191, 255));
      tft.setFont(&Supermarketed10pt7b);
      
      arr[0][3]=String(String(temperature()).toInt())+"°C";
//      arr[1][3]=String((temprature_sens_read()-32)/1.8)+"°C";
      arr[2][3]=String(heatIndex()).substring(0,String(heatIndex()).indexOf(".")+2)+"°C";
      arr[3][3]=String(String(pressure()).toInt())+"hPa";
      arr[4][3]=String(String(humidity()).toInt())+"%";
      arr[7][3]=String(wind()).substring(0,String(wind()).indexOf(".")+2)+"m/s";
      arr[8][3]=getFullTime(RawTime());
      arr[9][3]=String(clouds()).substring(0,String(clouds()).indexOf(".")+1)+"%";
      Serial.println(DateToUnix(2018,9,20,2,40,10));
      arr[10][3]=getDate(RawTime());
      
      
      for(int i=55;i<240;i+=22){
        tft.drawLine(0,i,320,i,ILI9341_WHITE);
        yield();
      }
      for(int i=0;i<=10;i++){
        tft.setCursor(arr[i][1].toInt(),arr[i][0].toInt());
        tft.println(arr[i][2]+arr[i][3]);  
      }
      tft.drawLine(140,188,140,230,ILI9341_WHITE);
    }
};
class Home{
  public:
    String request;
    void load(){
      tft.fillScreen(ILI9341_CYAN);
      yield();
      tft.fillRect(0,180,320,100,ILI9341_GREEN);
      tft.fillCircle(20,20,30,ILI9341_YELLOW);
      yield();
      tft.fillTriangle(-20,180,60,50,200,180,ILI9341_PINK);
      tft.fillTriangle(130,180,60,50,200,180,tft.color565(144,84,204));
      yield();
      tft.fillCircle(280,70,30,ILI9341_WHITE);
      tft.fillCircle(200,70,30,ILI9341_WHITE);
      yield();
      tft.fillCircle(250,50,40,ILI9341_WHITE);
      tft.fillCircle(210,40,10,ILI9341_WHITE);
      yield();
      tft.fillRect(200,40,80,61,ILI9341_WHITE);
      tft.setFont(&Supermarketed24pt7b);
      yield();
    }
    void reload(){
      request=getFullTime(RawTime());
      tft.fillCircle(280,70,30,ILI9341_WHITE);
      tft.fillCircle(200,70,30,ILI9341_WHITE);
      tft.fillCircle(250,50,40,ILI9341_WHITE);
      tft.fillCircle(210,40,10,ILI9341_WHITE);
      tft.fillRect(200,40,80,61,ILI9341_WHITE);
      if(countChr(request,"1")==0){
        tft.setCursor(182, 90);
      }else if(countChr(request,"1")==1){
        tft.setCursor(195, 90);
      }else if(countChr(request,"1")==2){
        tft.setCursor(200, 90);
      }else if(countChr(request,"1")==3){
        tft.setCursor(210, 90);
      }else{
        tft.setCursor(218, 90);
      }
      tft.setTextColor(ILI9341_CYAN);
      tft.setTextSize(1);
      yield();
      tft.println(request);
      yield();
    }
};
Weather Weather;
Home Home;
void setup() {
  //Display configuration
  tft.begin();
  //int BG=tft.color565(0, 191, 255);
  tft.setTextWrap(false);
  tft.setRotation(3);
  tft.fillScreen(BG);
  tft.setFont(&Supermarketed24pt7b);
  tft.setCursor(85,135);
  tft.println("AlexaOS");
  //dht.begin();
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  //buttons (unfinished)
  pinMode(BP,INPUT_PULLUP);
  //wifi to respond...
  int i=0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if(i>20){
      Serial.println("No internet connection!");
      break;
    }
    i++;
  }
  Home.load();
  Home.reload();
}


bool current;
int start=millis();
void loop() {
  if(digitalRead(BP)==LOW){
    if(state==false){
      state=true;
    }else{
      state=false;
    }
    current=true;
  }
  if(current==true){
    if(state==true){
      Weather.load();
      Weather.reload();
    }else{
      
      Home.load();
      Home.reload();
    }
  }
  if(millis()-start>60000 && state==false){
    start+=60000;
    Home.reload();
  }else if(millis()-start>60000 && state==true){
    start+=60000;
    Weather.reload();
  }
  current=false;
  delay(1);
}












