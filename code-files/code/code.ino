//Code by Atul Ravi ESC crasci 2023 
//esccrasci.in
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h> 
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const String dataURL = "http://worldtimeapi.org/api/timezone/Asia/Kolkata.json"; 
String x;
String hourss;
String minss;
String secs;
int hourint;
int minsint;
int secsint;

void setup() { 
  WiFi.mode(WIFI_STA); 
  WiFiManager wm;
  wm.resetSettings();
  bool res;
  res = wm.autoConnect("AutoConnectAP","password"); // password protected ap
  Serial.begin(57600);
  lcd.init();
  lcd.clear();         
  lcd.backlight();
} 
void loop() { 
  if(WiFi.status() == WL_CONNECTED) { 
    HTTPClient http; 
    http.begin(dataURL); 
    int httpCode = http.GET(); 
 
   if(httpCode> 0) { 
      if(httpCode == HTTP_CODE_OK) { 
        String payload = http.getString(); 
        //Getting parts of time
        x= payload.substring(73,82);
        hourss = payload.substring(73,76);
        minss = payload.substring(76,78);
        secs = payload.substring(79,81);
        Serial.println (hourss);
        Serial.println (minss);
        Serial.println (secs);
        hourint = hourss.toInt();
        minsint = minss.toInt();
        secsint = secs.toInt();
        //LCD Code
        lcd.setCursor(4,0);
        lcd.print(hourint, DEC);
        lcd.setCursor(6,0);
        lcd.print(':');
        lcd.setCursor(7,0);
        lcd.print(minsint, DEC);
        lcd.setCursor(9,0);
        lcd.print(':');
        lcd.setCursor(10,0);
        lcd.print(secsint, DEC);
        delay(3);
      }
    delay(10); 
    }
  }
}
