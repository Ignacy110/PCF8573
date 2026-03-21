
// allMethods.ino example
// This example demonstrates all methods available in the PCF8573 library.
// All data read from the PCF8573 chip is printed to the Serial Monitor.

#include <Wire.h> // library required for I2C communication
#define WIRE_CLOCK 100000 // set the wire transmission clock

#include <PCF8573.h> // PCF8573 library
PCF8573 rtc (0x68); // create an rtc object with address of our PCF8573 chip

void setup()
{
  Serial.begin(115200); // start serial communication for serial monitor

  Wire.begin(); // start I2C communication to communicate with PCF8573 chip
  Wire.setClock(WIRE_CLOCK); // set defined wire transmission clock

  rtc.setTime(PCF8573::time::HOURS, 9);     // setting hours
  rtc.setTime(PCF8573::time::MINUTES, 0);   // setting minutes
  rtc.setTime(PCF8573::time::DAYS, 26);     // setting day
  rtc.setTime(PCF8573::time::MONTHS, 5);    // setting month

  rtc.setAlarmTime(PCF8573::time::HOURS, 9);    // setting alarm hours
  rtc.setAlarmTime(PCF8573::time::MINUTES,1);   // setting alarm minutes
  rtc.setAlarmTime(PCF8573::time::DAYS, 26);    // setting alarm day
  rtc.setAlarmTime(PCF8573::time::MONTHS, 5);   // setting alarm month

  rtc.resetPrescaler(); // reset seconds counter

  rtc.resetNODAflag();  // reset NODA flag (1 to 0 flag state)
  rtc.resetCOMPflag();  // reset COMP flag (1 to 0 flag state)

  rtc.setNODAflag();    // set NODA flag (0 to 1 flag state)
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
  Serial.println(rtc.readAlarmTime(PCF8573::time::MONTHS));

  // FLAGS
  Serial.print("POWF:\t");
  Serial.println(rtc.readFlag(PCF8573::flag::POWF));

  Serial.print("NODA:\t");
  Serial.println(rtc.readFlag(PCF8573::flag::NODA));

  Serial.print("COMP:\t");
  Serial.println(rtc.readFlag(PCF8573::flag::COMP));

  delay(5000);
}