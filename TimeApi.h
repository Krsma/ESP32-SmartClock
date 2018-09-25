#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

String RawTime(){
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://worldclockapi.com/api/jsonp/cet/now?callback=m");
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      http.end();
      payload=payload.substring(payload.indexOf("m(")+2,payload.indexOf(");"));
      return payload;
    }
    http.end();
  }
  return "None";
  
}

String DateToUnix(int Y,int M,int D,int h,int m,int s){
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String q=String(Y)+"-"+String(M)+"-"+String(D)+"%20"+String(h)+":"+String(m)+":"+String(s);
    http.begin("http://www.convert-unix-time.com/api?timezone=belgrade&date="+String(q));
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      http.end();
      return payload;
    }
    http.end();
  }
}


int getHour(String json){
  StaticJsonDocument<1000> doc;
  DeserializationError error = deserializeJson(doc, json);
  JsonObject root = doc.as<JsonObject>();
  String timex = root["currentDateTime"];
  int startc=timex.indexOf("T");
  int endc=timex.indexOf("+");
  timex=timex.substring(startc+1,endc);
  String hours=timex.substring(1,3);
  return hours.toInt();

}
String getFullTime(String json){
  StaticJsonDocument<1000> doc;
  DeserializationError error = deserializeJson(doc, json);
  JsonObject root = doc.as<JsonObject>();
  String timex = root["currentDateTime"];
  int startc=timex.indexOf("T");
  int endc=timex.indexOf("+");
  timex=timex.substring(startc+1,endc);
  return timex;
}

int getMinute(String json){
  StaticJsonDocument<1000> doc;
  DeserializationError error = deserializeJson(doc, json);
  JsonObject root = doc.as<JsonObject>();
  String timex = root["currentDateTime"];
  int startc=timex.indexOf("T");
  int endc=timex.indexOf("+");
  String minute=timex.substring(startc+4,endc);
  int minu=minute.toInt();
  return minu;
}
String getDate(String json,String format="DMY",String delimiter="/"){
  StaticJsonDocument<1000> doc;
  DeserializationError error = deserializeJson(doc, json);
  JsonObject root = doc.as<JsonObject>();
  String timex = root["currentDateTime"];
  String times = timex.substring(0,timex.indexOf("T"));
  times.replace("-","/");
  
  String y=times.substring(0,times.indexOf("/"));
  times=times.substring(times.indexOf("/")+1,times.length());
  String m=times.substring(0,times.indexOf("/"));
  times=times.substring(times.indexOf("/")+1,times.length());
  String d=times;
  if(m.toInt()<10){
      m.replace("0"," ");
  }
  if(d.toInt()<10){
      d.replace("0"," ");
  }
  times="";
  times=d+"/"+m+"/"+y;
  
  return times;
}




