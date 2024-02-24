#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {
  Serial.begin(57600);
  lcd.init();
  lcd.clear();         
  lcd.backlight();
#ifndef ESP8266
  while (!Serial);
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

}

void loop () {
    DateTime now = rtc.now();
    //UNCOMMENT BELOW CODE TO TEST RTC ALONE
    //Serial.print(now.year(), DEC);
    //Serial.print('/');
    //Serial.print(now.month(), DEC);
    //Serial.print('/');
    //Serial.print(now.day(), DEC);
    //Serial.print(" (");
    //Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    //Serial.print(") ");
    //Serial.print(now.hour(), DEC);
    //Serial.print(':');
    //Serial.print(now.minute(), DEC);
    //Serial.print(':');
    //Serial.print(now.second(), DEC);
    //Serial.println();
        lcd.setCursor(4,0);
        lcd.print(now.hour(), DEC);
        lcd.setCursor(6,0);
        lcd.print(':');
        lcd.setCursor(7,0);
        lcd.print(now.minute(), DEC);
        lcd.setCursor(9,0);
        lcd.print(':');
        lcd.setCursor(10,0);
        lcd.print(now.second(), DEC);
        delay(3);
   
}
