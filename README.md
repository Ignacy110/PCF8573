# PCF8573 Arduino Library

Arduino library for communicating with the PCF8573 RTC I2C chip with Power Fail Detector.

The library allows you to easily set and read time, configure alarm registers and access status flags of the PCF8573 chip.

### List of Contents:
1. [Installation](#1-installation)
2. [Connecting the PCF8573 chip and pinout](#2-connecting-the-pcf8573-chip-and-pinout)
3. [Usage](#3-usage)
4. [Methods](#4-methods)
5. [Inspiration](#5-inspiration)

## 1. Installation

1. Download the repository as .ZIP file.
2. In Arduino IDE select:
*Sketch → Include Library → Add .ZIP Library*
3. Select the downloaded .ZIP file.

## 2. Connecting the PCF8573 chip and pinout

### 2.1 Hardware requirements:

The PCF8573 chip requires the following components:
- **Crystal** oscillator (32.768 kHz) - connected between OSCI and OSCO pins
    - you can add **trim capacitor** to fine-tune the precision of timekeeping - a trimmer is connected between OSCI and VDD
- SDA and SCL **pull-up resistors** (4.7 kΩ) - if your board does not have such resistors
- **100 nF capacitor** between VDD and VSS1

> [!WARNING]
> The **100 nF capacitor** can be omitted, but is not recommended. In the final version of the project with this or other integrated circuits it is worth including it.

### 2.2 Pinout and how to connect:

|Symbol| Pin | Description |I/O| How to connect |
| --- | :-: | --- | :-: | --- |
|A0|1|address input|input| to GND |
|A1|2|address input|input| to GND |
|COMP|3|comparator output|output| not connect |
|SDA|4|I2C SDA|transmission| to SDA pin in your microcontroller|
|SCL|5|I2C SCL|transmission| to SDL pin in your microcontroller|
|EXTPF|6|enable power fail flag input|input|to GND|
|PFIN|7|power fail flag input|input|to GND|
|VSS2|8|**GND** for the I2C interface|power|to GND|
|MIN|9|one pulse per minute output|output|not connect|
|SEC|10|one pulse per second output|output|not connect|
|FSET|11|oscillator tuning output|output|not connect|
|TEST|12|test input|input|to GND|
|OSCI|13|oscillator input|osc. input|Crystal oscillator (32.768 kHz)|
|OSCO|14|oscillator input/output|osc. input/output|Crystal oscillator (32.768 kHz)|
|VSS1|15|**GND** for the clock (RTC)|power|to GND|
|VDD|16|**5V** (typical value) common positive supply|power|to VCC|

The last column shows the simplest way to connect the PCF8573 chip.

Depending on your needs, you can use your own connection methods. For example, you can use the output pins to read the COMP flag or the seconds/minutes pulses in hardware. You can also specify VCC at the inputs, not GND, to change the PCF8573 address or the operation of the power fail detector.
 
> [!WARNING]
> If you do not connect the inputs to VCC or GND, the system may not function properly!

The address of the PCF8573 chip is set via inputs A0 and A1. Table of assigned addresses:
|A1 input state|A0 input state|PCF8573 address|
|:-:|:-:|:-:|
|GND|GND|`0x68`|
|GND|VCC|`0x69`|
|VCC|GND|`0x6A`|
|VCC|VCC|`0x6B`|

## 3. Usage

### 3.1 Basic setup

To use this library you need to use the `<Wire.h>` library in your sketch, which allows communication with the chip via I2C. In addition to include, we need to properly initiate and start the transmission.

Of course, we cannot forget to import this library `<PCF8573.h>`.

Before using the library methods you need to create an instance of the `PCF8573` class e.g. `PCF8573 rtc (0x68);` where the parameter takes the value of the I2C address set via pins A0 and A1. In short this object represents the physical PCF8573 chip with a given address *(0x68)* connected via I2C.

Example:
```cpp
#include <Wire.h> // library required for I2C communication
#define WIRE_CLOCK 100000 // set the wire transmission clock

#include <PCF8573.h> // PCF8573 library
PCF8573 rtc (0x68); // create an rtc object with address of our PCF8573 chip

void setup()
{
    Wire.begin(); // start I2C communication to communicate with PCF8573 chip
    Wire.setClock(WIRE_CLOCK); // set defined wire transmission clock
}
```

### 3.2 Use library methods
#### Simple example of use
This program sets the time to 12:34 and display it from our chip on serial monitor (in Arduino IDE). We can see how minutes and later hours increment.
```cpp
#include <Wire.h> // library required for I2C communication
#define WIRE_CLOCK 100000 // set the wire transmission clock

#include <PCF8573.h> // PCF8573 library
PCF8573 rtc (0x68); // create an rtc object with address of our PCF8573 chip

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
```
> [!TIP]
> More examples are in the *examples* folder.

> [!TIP]
> All available methods are described in paragraph 5.

## 4. Methods

With the PCF8573 chip you can:
1. set and read the time
2. set and read the alarm time
3. set and read flags
4. call functions

> [!IMPORTANT]
> All methods provided by this library are member functions of the `PCF8573` class.  
> Therefore they must be called using the created object, for example `rtc`.

You can use the following methods to perform these activities:

### 4.1 Time operations

#### 4.1.1 Set the time

To set the time you use `setTime()` method which requires a time field identifier and your value e.g. `setTime(PCF8573::time::HOURS, 7)` that means set the *hours register* to 7.

**setTime()** parameters:

|Function| setTime() | accepted values |
| :--- | --- | ------------- |
|Set hours| `setTime(PCF8573::time::HOURS, value);` | 0 to 23 |
|Set minutes| `setTime(PCF8573::time::MINUTES, value);` | 0 to 59 |
|Set days| `setTime(PCF8573::time::DAYS, value);` | 1 to 28 / 29 <br> 1 to 30 <br> 1 to 31 |
|Set months| `setTime(PCF8573::time::MONTHS, value);` | 1 to 12 |

> [!NOTE]
> The **DAYS** register accepts values ​​appropriate to the month.

> [!WARNING]
> If you send incorrect values, the chip may not work properly!

> [!IMPORTANT]
> Leap year support (February 29) must be handled externally because the PCF8573 does not have a year counter.

#### 4.1.2 Read the time

To read the time you use `readTime()` method which requires a time field identifier e.g. `readTime(PCF8573::time::MINUTES)` that means read the *minutes register*. This method return a `uint8_t` value.

**readTime()** parameters:

|Function| readTime() |
| :--- | --- |
|Read hours| `readTime(PCF8573::time::HOURS);` |
|Read minutes| `readTime(PCF8573::time::MINUTES);` |
|Read days| `readTime(PCF8573::time::DAYS);` |
|Read months| `readTime(PCF8573::time::MONTHS);` |

### 4.2 Alarm time operations

The alarm works like an alarm clock. When the hour strikes, the **COMP flag** is set to 1, indicating that the hour has struck. More details in section [4.3 Flags operation](#43-flags-operation).

#### 4.2.1 Set the alarm time

It is similar to setting the time but to set the alarm time you use `setAlarmTime()` method which requires a time field identifier and your value e.g. `setAlarmTime(PCF8573::time::DAYS, 21)` that means set the *days alarm register* to 21.

**setAlarmTime()** parameters:

|Function| setAlarmTime() | accepted values |
| :--- | --- | ------------- |
|Set alarm hours| `setAlarmTime(PCF8573::time::HOURS, value);` | 0 to 23 |
|Set alarm minutes| `setAlarmTime(PCF8573::time::MINUTES, value);` | 0 to 59 |
|Set alarm days| `setAlarmTime(PCF8573::time::DAYS, value);` | 1 to 28 / 29 <br> 1 to 30 <br> 1 to 31 |
|Set alarm months| `setAlarmTime(PCF8573::time::MONTHS, value);` | 1 to 12 |

#### 4.2.2 Read the alarm time

It is similar to reading the time but to read the time you use `readAlarmTime()` method which requires a time field identifier e.g. `readAlarmTime(PCF8573::time::MONTHS)` that means read the *months alarm register*. This method return a `uint8_t` value.

**readAlarmTime()** parameters:

|Function| readAlarmTime() |
| :--- | --- |
|Read alarm hours| `readAlarmTime(PCF8573::time::HOURS);` |
|Read alarm minutes| `readAlarmTime(PCF8573::time::MINUTES);` |
|Read alarm days| `readAlarmTime(PCF8573::time::DAYS);` |
|Read alarm months| `readAlarmTime(PCF8573::time::MONTHS);` |

### 4.3 Flags operation

The PCF8573 chip has 3 flags:
|Flag|Description|method of set (0 to 1)|method of reset (1 to 0)|
|---|---|---|---|
|POWF|The flag indicates a detected power failure|When a power failure occurs||
|COMP|The flag signals that the alarm has sounded|When *alarm time* is the same as RTC *time*|By user|
|NODA|The flag says to ignore the date when comparing the alarm and time (when comparing we only look at hours and minutes)|By user|By user|

#### 4.3.1 Read the flag

We can read one of the three flags. To read the time you use `readFlag()` method which requires a time field identifier e.g. `readFlag(PCF8573::flag::COMP)` that means read the *COMP flag register*. This method return a `bool` value.

**readFlag()** parameters:

|Function| readFlag() |
| :--- | --- |
|Read POWF flag| `readFlag(PCF8573::flag::POWF);` |
|Read COMP flag| `readFlag(PCF8573::flag::COMP);` |
|Read NODA flag| `readFlag(PCF8573::flag::NODA);` |

#### 4.3.2 Reset the flag

We can reset COMP or NODA flag by methods: `resetCOMPflag()` or `resetNODAflag()`. Reset means changing the state of the flag from 1 to 0.

#### 4.3.3 Set the flag

We can only set NODA flag by method: `setNODAflag()` Set means changing the state of the flag from 0 to 1.

### 4.4 Functions

#### 4.4.1 Reset prescaler - reset seconds

`resetPrescaler()` method - reset prescaler, including seconds counter, without carry for minute counter

> [!TIP]
> It is good to use `resetPrescaler()` method when you set minutes. Because this method reset seconds counter so you can start counting minutes precisely from a given moment.
>In your code:
>```cpp
>rtc.setTime(PCF8573::time::HOURS, 9);      // setting hours
>rtc.setTime(PCF8573::time::MINUTES, 11);   // setting minutes
>rtc.resetPrescaler();   // resetting seconds counter
>```
>In this example we set time 09:11:00.
>Without `resetPrescaler()` function we can set 09:11:xx where *xx* has the value at which the chip stopped counting (so random value).

## 5. Inspiration

This library was inspired by the PCF8574 Arduino library by MSZ98:
https://github.com/MSZ98/pcf8574

It is an independent implementation for the PCF8573 RTC chip.