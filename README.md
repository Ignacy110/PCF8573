# PCF8573 Arduino Library

Arduino library for communicating with the PCF8573 RTC I2C chip with Power Fail Detector.

## Mode Pointer

MODE-POINTER points to a register in the module. Each register stores specific information. Registers can be divided into those that store information about:
- time
- alarms
- flags
- functions

### Time Mode Pointer

| DEC Value  | MODE-POINTER  | Function  |
| ---: | ------------- | ------------- |
| 1  | `HOURS`  |  time counter hours |
| 2  | `MINUTES`  | time counter minutes|
| 3  | `DAYS`  | time counter days|
| 4  | `MONTHS`  | time counter months|

### Alarms Mode Pointer

| DEC Value  | MODE-POINTER  | Function  |
| ---: | ------------- | ------------- |
| 4  | `ALARM_HOURS`  |  alarm register hours |
| 5  | `ALARM_MINUTES`  | alarm register minutes|
| 6  | `ALARM_DAYS`  | alarm register days|
| 7  | `ALARM_MONTHS`  | alarm register months|

<!-- ### Flags and Functions Mode Pointer

| DEC Value  | MODE-POINTER  | Function  |
| ---: | ------------- | ------------- |
| 16  | ``  |  read control/status flags |
| 32  | ``  | reset prescaler, including seconds counter; without carry for minute counter|
| 48  | ``  | time adjust, with carry for minute counter|
| 64  | ``  | reset NODA flag|
| 80  | ``  | set NODA flag|
| 96  | ``  | reset COMP flag| -->

## Inspiration

This library was inspired by the PCF8574 Arduino library by MSZ98:
https://github.com/MSZ98/pcf8574

It is an independent implementation for the PCF8573 RTC chip.
