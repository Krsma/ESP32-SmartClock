#include <HTTPClient.h>
#include <WiFi.h>

String query(String text){
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    text.replace("%","%25");
    text.replace("+","%2B");
    text.replace("-","-");
    text.replace("/","/");
    text.replace("*","%2A");
    text.replace("°","%C2%B0");
    text.replace("α","%CE%B1");
    text.replace("ß","%C3%9F");
    text.replace("<","%3C");
    text.replace("÷","%C3%B7");
    text.replace("ε","%CE%B5");
    text.replace("^","%5E");
    text.replace("∩","%E2%88%A9");
    text.replace("⌡","%E2%8C%A1");
    text.replace(">","%3E");
    text.replace("±","%C2%B1");
    text.replace("⌠","%E2%8C%A0");
    text.replace("≤","%E2%89%A4");
    text.replace("ƒ","%C6%92");
    text.replace("&","%26");
    text.replace("≈","%E2%89%88");
    text.replace("σ","%CF%83");
    text.replace("Θ","%CE%98");
    text.replace("τ","%CF%84");
    text.replace("∞","%E2%88%9E");
    text.replace("Σ","%CE%A3");
    text.replace("≥","%E2%89%A5");
    text.replace("δ","%CE%B4");
    text.replace("√","%E2%88%9A");
    text.replace("Γ","%CE%93");
    text.replace("π","%CF%80");
    text.replace("Φ","%CE%A6");
    text.replace("φ","%CF%86");
    text.replace("Ω","%CE%A9");
    text.replace("µ","%C2%B5");
    //this is full api doesnt work cuze json memory http.begin("http://api.wolframalpha.com/v2/query?appid=WHLX88-EA7HXH4HK6&output=json&input="+input);
    //http://api.wolframalpha.com/v1/result?appid=WHLX88-EA7HXH4HK6&output=json&input=
    http.begin("http://api.wolframalpha.com/v1/result?appid=WHLX88-EA7HXH4HK6&output=json&input="+text);
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      http.end();
      return payload;
    }
    http.end();

  }
  return "Internet fail.";
}
