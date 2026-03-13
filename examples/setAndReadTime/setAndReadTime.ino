
#include <Wire.h>
#define WIRE_CLOCK 100000

#include "pcf8573.h"
PCF8573 rtc (0x68);

uint8_t hour;
uint8_t minutes;
uint8_t day;
uint8_t month;

void setup()
{
    Serial.begin(115200);

    Wire.begin();
    Wire.setClock(WIRE_CLOCK);

    rtc.setTime(HOURS, 12);     // setting hours
    rtc.setTime(MINUTES, 34);   // setting minutes
    rtc.setTime(DAYS, 26);       // setting day
    rtc.setTime(MONTHS, 5);     // setting month

    rtc.write(RESET_SECONDS); // reset secound counter
}

void loop()
{
  hour = rtc.readTime(HOURS);
  minutes = rtc.readTime(MINUTES);
  day = rtc.readTime(DAYS);
  month = rtc.readTime(MONTHS);

  Serial.print("Hour: ");
  Serial.println(hour);

  Serial.print("Minutes: ");
  Serial.println(minutes);

  Serial.print("Day: ");
  Serial.println(day);

  Serial.print("Month: ");
  Serial.println(month);

	delay(1000);
}