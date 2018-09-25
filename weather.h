#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

String rawforecast(){
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://api.openweathermap.org/data/2.5/weather?appid=26a1f9e391fb15bf1c28c5c3cf9b910c&units=metric&q=Novi%20Sad");
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      http.end();
      return payload;
    }
    http.end();

  }
  return "None";
}

//String unixConversion(long int unixtime){
//    unixtime/=86400;
//    int i=0;
//    while(unixtime>=365){
//        i++;
//        if((i+1970)%4==0){
//            unixtime-=366;
//        }else{
//            unixtime-=365;
//        }
//    }
//    int year=i+1970;
//    int mounth[][2]={{1,31},{2,28},{3,31},{4,30},{5,31},{6,30},{7,31},{8,31},{9,30},{10,31},{11,30},{12,31}};
//    if(year%4==0){
//      mounth[1][1]=29;
//    }
//    int mounthf=0;
//    for(int j=0;j<=12;j++){
//      if(unixtime-mounth[j][1]>0){
//          unixtime-=mounth[j][1];
//          mounthf+=1;
//      }else{
//        break;  
//      }
//    }
//    mounthf+=1;
//    return "Y"+String(year)+"Y2:M"+String(mounthf)+"M2:D"+String(unixtime+1)+"D2";
//    
//}


    

float temperature(){
  StaticJsonDocument<1000> doc;
  String json=rawforecast();
  DeserializationError error = deserializeJson(doc, json);
  JsonObject root = doc.as<JsonObject>();
  float temp = root["main"]["temp"];
  return temp;
}

//String fivedays(){
//    if (WiFi.status() == WL_CONNECTED) {
//    HTTPClient http;
//    http.begin("http://api.openweathermap.org/data/2.5/weather?appid=26a1f9e391fb15bf1c28c5c3cf9b910c&units=metric&q=Novi%20Sad");
//    int httpCode = http.GET();
//    if (httpCode > 0) {
//      String payload = http.getString();
//      http.end();
//      return payload;
//    }
//    http.end();
//
//  }
//  return "Internet fail.";
//}



String weather(){
  StaticJsonDocument<1000> doc;
  String json=rawforecast();
  DeserializationError error = deserializeJson(doc, json);
  JsonObject root = doc.as<JsonObject>();
  String weather = root["weather"][0]["main"];
  return weather;
}





float pressure(){
  StaticJsonDocument<1000> doc;
  String json=rawforecast();
  DeserializationError error = deserializeJson(doc, json);
  JsonObject root = doc.as<JsonObject>();
  float pressure = root["main"]["pressure"];
  return pressure;
}





float humidity(){
  StaticJsonDocument<1000> doc;
  String json=rawforecast();
  DeserializationError error = deserializeJson(doc, json);
  JsonObject root = doc.as<JsonObject>();
  float humidity = root["main"]["humidity"];
  return humidity;
}



float wind(){
  StaticJsonDocument<1000> doc;
  String json=rawforecast();
  DeserializationError error = deserializeJson(doc, json);
  JsonObject root = doc.as<JsonObject>();
  float wind = root["wind"]["speed"];
  return wind;
}




float clouds(){
  StaticJsonDocument<1000> doc;
  String json=rawforecast();
  DeserializationError error = deserializeJson(doc, json);
  JsonObject root = doc.as<JsonObject>();
  float clouds = root["clouds"]["all"];
  return clouds;
}

//double heatIndex()
//{
//  double tempF=temperature()*1.8-32;
//  double hum=humidity();
//  double c1 = -42.38, c2 = 2.049, c3 = 10.14, c4 = -0.2248, c5= -6.838e-3, c6=-5.482e-2, c7=1.228e-3, c8=8.528e-4, c9=-1.99e-6  ;
//  double T = tempF;
//  double R = hum;
//  
//  double A = (( c5 * T) + c2) * T + c1;
//  double B = ((c7 * T) + c4) * T + c3;
//  double C = ((c9 * T) + c8) * T + c6;
//  
//  double rv = (C * R + B) * R + A;
//  return (rv-32)/1.8;
//}
double heatIndex()
{
  double tempF=temperature()*1.8+32;
  double hum=humidity();
  double c1 = -42.38, c2 = 2.049, c3 = 10.14, c4 = -0.2248, c5= -6.838e-3, c6=-5.482e-2, c7=1.228e-3, c8=8.528e-4, c9=-1.99e-6 ; 
  double T = tempF;
  double R = hum;
  double T2 = T*T;
  double R2 = R*R;
  double TR = T*R;
  double rv = c1 + c2*T + c3*R + c4*T*R + c5*T2 + c6*R2 + c7*T*TR + c8*TR*R + c9*T2*R2;
  return (rv-32)/1.8;
}

String image(){
  StaticJsonDocument<1000> doc;
  String json=rawforecast();
  DeserializationError error = deserializeJson(doc, json);
  JsonObject root = doc.as<JsonObject>();
  String image = root["weather"][0]["icon"];
  return image;
}
