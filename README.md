# PCF8573 Arduino Library

Arduino library for communicating with the PCF8573 RTC I2C chip with Power Fail Detector.

## 1. Requirements

### 1.1 Hardware requirements
The PCF8573 module requires for its operation:
- **Crystal** oscillator (32.768 kHz) - connected between OSCI nad OSCO pins
    - you can add **trim capacitor** to fine-tune the precision of timekeeping - a trimmer is connected between OSCI and VDD
- SDA and SCL **pull-up resistors** (4,7kOhm) - if your board does not have such resistors
- **100nF capacitor** between VDD and VSS1 (for module testing this can be omitted)

### 1.2 Software requirements

To use this library you need to include the `<Wire.h>` library, which allows communication with the module via I2C.
What needs to be in your code besides this library:
```
#include <Wire.h>
#define WIRE_CLOCK 100000

#include <PCF8573.h>
PCF8573 rtc (0x68);

void setup()
{
    Wire.begin();
    Wire.setClock(WIRE_CLOCK);

    // your code...
}

void loop()
{
    // your code...
}
```

## 2. Mode Pointer

The MODE-POINTER selects an operation inside the PCF8573 module.
Depending on its value it can:
1. select a time register
2. select an alarm register
3. read status flags
4. trigger control functions inside the RTC

### 2.1 Mode Pointer - select a time register

| HEX | MODE-POINTER  | Function  | accepted values |
| ---: | ------------- | ------------- | ------------- |
| `0x00`  | `HOURS`  |  time counter hours | 0 to 23 |
| `0x01`  | `MINUTES`  | time counter minutes| 0 to 59 |
| `0x02`  | `DAYS`  | time counter days| 0 to 28 / 29 <br> 0 to 30 <br> 0 to 31 |
| `0x03`  | `MONTHS`  | time counter months| 0 to 12 |

> [!NOTE]
> The **DAYS** register accepts values ​​appropriate to the month.

> [!IMPORTANT]
> Leap year support (February 29) must be handled externally because the PCF8573 does not have a year counter.

### 2.2 Mode Pointer - select an alarm register

| HEX | MODE-POINTER  | Function  | accepted values |
| ---: | ------------- | ------------- | ------------- |
| `0x04`  | `ALARM_HOURS`  |  alarm register hours | 0 to 23 |
| `0x05`  | `ALARM_MINUTES`  | alarm register minutes | 0 to 59 |
| `0x06`  | `ALARM_DAYS`  | alarm register days | 0 to 28 / 29 <br> 0 to 30 <br> 0 to 31 |
| `0x07`  | `ALARM_MONTHS`  | alarm register months | 0 to 12 |

> [!NOTE]
> Only after selecting **Time** or **Alarms Mode Pointer** you can send data.

> [!WARNING]
> If you send incorrect values, the module may not work properly.

<!-- ### 2.3 Mode Pointer - flags and functions

| DEC Value  | MODE-POINTER  | Function  |
| ---: | ------------- | ------------- |
| `0x10`  | `READ_FLAGS`  |  read control/status flags |
| `0x20`  | `RESET_PRESCALER`  | reset prescaler, including seconds counter; without carry for minute counter|
| `0x30`  | `TIME_ADJUST`  | time adjust, with carry for minute counter|
| `0x40`  | `RESET_NODA`  | reset NODA flag|
| `0x50`  | `SET_NODA`  | set NODA flag|
| `0x60`  | `RESET_COMP`  | reset COMP flag| -->

## Inspiration

This library was inspired by the PCF8574 Arduino library by MSZ98:
https://github.com/MSZ98/pcf8574

It is an independent implementation for the PCF8573 RTC chip.
