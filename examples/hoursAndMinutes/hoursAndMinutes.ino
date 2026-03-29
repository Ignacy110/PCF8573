
// hoursAndMinutes.ino example
// In this example, we set the time once in void setup(), then read it and display it in the serial monitor (void loop()). As time progresses, the minutes and hours will increment.

#include <Wire.h> // library required for I2C communication
#define WIRE_CLOCK 100000 // set the wire transmission clock

#include <PCF8573.h> // PCF8573 library
PCF8573 rtc(0x68); // create an rtc object with address of our PCF8573 chip

void setup()
{
  Serial.begin(115200); // start serial communication for serial monitor

  Wire.begin(); // start I2C communication to communicate with PCF8573 chip
  Wire.setClock(WIRE_CLOCK); // set defined wire transmission clock

  rtc.setTime(PCF8573::time::HOURS, 12);     // setting hours
  rtc.setTime(PCF8573::time::MINUTES, 34);   // setting minutes
}

void loop()
{
  Serial.print("\nHour:\t");
  Serial.println(rtc.readTime(PCF8573::time::HOURS));   // display hours

  Serial.print("Minute:\t");
  Serial.println(rtc.readTime(PCF8573::time::MINUTES)); // display minutes

  delay(5000);
}