
#include <Wire.h>
#define WIRE_CLOCK 100000

#include <PCF8573.h>
PCF8573 rtc (0x68);

void setup()
{
    Serial.begin(115200);

    Wire.begin();
    Wire.setClock(WIRE_CLOCK);

    rtc.setTime(PCF8573::time::HOURS, 12);     // setting hours
    rtc.setTime(PCF8573::time::MINUTES, 34);   // setting minutes
    rtc.setTime(PCF8573::time::DAYS, 26);       // setting day
    rtc.setTime(PCF8573::time::MONTHS, 5);     // setting month

    rtc.setAlarmTime(PCF8573::time::HOURS, 12);     // setting hours
    rtc.setAlarmTime(PCF8573::time::MINUTES,34);   // setting minutes
    rtc.setAlarmTime(PCF8573::time::DAYS, 26);       // setting day
    rtc.setAlarmTime(PCF8573::time::MONTHS, 5);     // setting month

    //rtc.write(RESET_SECONDS); // reset secound counter
    //rtc.resetCOMPflag();
}

void loop()
{
  // TIME
  Serial.print("\nHour:\t");
  Serial.println(rtc.readTime(PCF8573::time::HOURS));

  Serial.print("Minute:\t");
  Serial.println(rtc.readTime(PCF8573::time::MINUTES));

  Serial.print("Day:\t");
  Serial.println(rtc.readTime(PCF8573::time::DAYS));

  Serial.print("Month:\t");
  Serial.println(rtc.readTime(PCF8573::time::MONTHS));

  // ALARMS
  Serial.print("\nHourAlarm:\t");
  Serial.println(rtc.readAlarmTime(PCF8573::time::HOURS));

  Serial.print("MinuteAlarm:\t");
  Serial.println(rtc.readAlarmTime(PCF8573::time::MINUTES));

  Serial.print("DayAlarm:\t");
  Serial.println(rtc.readAlarmTime(PCF8573::time::DAYS));

  Serial.print("MonthAlarm:\t");
  Serial.println(rtc.readAlarmTime(tPCF8573::ime::MONTHS));

  // FLAGS
  Serial.print("POWF:\t");
  Serial.println(rtc.readFlag(PCF8573::flag::POWF));

  Serial.print("NODA:\t");
  Serial.println(rtc.readFlag(PCF8573::flag::NODA));

  Serial.print("COMP:\t");
  Serial.println(rtc.readFlag(PCF8573::flag::COMP));

	delay(1000);
}