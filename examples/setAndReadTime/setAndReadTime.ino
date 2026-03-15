
#include <Wire.h>
#define WIRE_CLOCK 100000

#include <PCF8573.h>
PCF8573 rtc (0x68);

void setup()
{
    Serial.begin(115200);

    Wire.begin();
    Wire.setClock(WIRE_CLOCK);

    rtc.setTime(time_mode_pointer::HOURS, 12);     // setting hours
    rtc.setTime(time_mode_pointer::MINUTES, 34);   // setting minutes
    rtc.setTime(time_mode_pointer::DAYS, 26);       // setting day
    rtc.setTime(time_mode_pointer::MONTHS, 5);     // setting month

    rtc.setAlarmTime(time_mode_pointer::HOURS, 12);     // setting hours
    rtc.setAlarmTime(time_mode_pointer::MINUTES,34);   // setting minutes
    rtc.setAlarmTime(time_mode_pointer::DAYS, 26);       // setting day
    rtc.setAlarmTime(time_mode_pointer::MONTHS, 5);     // setting month

    //rtc.write(RESET_SECONDS); // reset secound counter
    //rtc.resetCOMPflag();
}

void loop()
{
  // TIME
  Serial.print("\nHour:\t");
  Serial.println(rtc.readTime(time_mode_pointer::HOURS));

  Serial.print("Minute:\t");
  Serial.println(rtc.readTime(time_mode_pointer::MINUTES));

  Serial.print("Day:\t");
  Serial.println(rtc.readTime(time_mode_pointer::DAYS));

  Serial.print("Month:\t");
  Serial.println(rtc.readTime(time_mode_pointer::MONTHS));

  // ALARMS
  Serial.print("\nHourAlarm:\t");
  Serial.println(rtc.readAlarmTime(time_mode_pointer::HOURS));

  Serial.print("MinuteAlarm:\t");
  Serial.println(rtc.readAlarmTime(time_mode_pointer::MINUTES));

  Serial.print("DayAlarm:\t");
  Serial.println(rtc.readAlarmTime(time_mode_pointer::DAYS));

  Serial.print("MonthAlarm:\t");
  Serial.println(rtc.readAlarmTime(time_mode_pointer::MONTHS));

  // FLAGS
  Serial.print("POWF:\t");
  Serial.println(rtc.readFlag(flags_mode_pointer::POWF));

  Serial.print("NODA:\t");
  Serial.println(rtc.readFlag(flags_mode_pointer::NODA));

  Serial.print("COMP:\t");
  Serial.println(rtc.readFlag(flags_mode_pointer::COMP));

	delay(1000);
}