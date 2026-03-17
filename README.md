# PCF8573 Arduino Library

Arduino library for communicating with the PCF8573 RTC I2C chip with Power Fail Detector.

The library allows you to easily set and read time, configure alarm registers and access status flags of the PCF8573 chip.

### List of Contents:
1. [Installation](#1-installation)
2. [Connecting the PCF8573 chip and pinout](#2-connecting-the-pcf8573-chip-and-pinout)
3. [Usage](#3-usage)
4. [Methods](#4-methods)
5. [Power Fail Detector](#5-power-fail-detector)
6. [Inspiration](#6-inspiration)

## 1. Installation

1. Download the repository as .ZIP file.
2. In Arduino IDE select:
*Sketch → Include Library → Add .ZIP Library*
3. Select the downloaded .ZIP file.

## 2. Connecting the PCF8573 chip and pinout

### 2.1 Hardware requirements:

The PCF8573 chip requires the following components:
- **Crystal** oscillator (32.768 kHz) - connected between OSCI and OSCO pins
    - the **trim capacitor** can be added to fine-tune the precision of timekeeping - a trimmer is connected between OSCI and VDD pins
- SDA and SCL **pull-up resistors** (4.7 kΩ) - if your board does not have such resistors
- **100 nF capacitor** between VDD and VSS1

> [!WARNING]
> The **100 nF capacitor** can be omitted, but is not recommended. In the final version of the project with this or other integrated circuits it is worth including it.

### 2.2 Pinout and how to connect:

|Symbol| Pin | Description |I/O| How to connect |
| --- | :-: | --- | :-: | --- |
|A0|1|address input|input| to GND |
|A1|2|address input|input| to GND |
|COMP|3|comparator output|output| not connected |
|SDA|4|I2C SDA|transmission| to SDA pin in your microcontroller|
|SCL|5|I2C SCL|transmission| to SCL pin in your microcontroller|
|EXTPF|6|enable power fail flag input|input|to GND|
|PFIN|7|power fail flag input|input|to GND|
|VSS2|8|**GND** for the I2C interface|power|to GND|
|MIN|9|one pulse per minute output|output|not connecedt|
|SEC|10|one pulse per second output|output|not connected|
|FSET|11|oscillator tuning output|output|not connected|
|TEST|12|test input|input|to GND|
|OSCI|13|oscillator input|osc. input|Crystal oscillator (32.768 kHz)|
|OSCO|14|oscillator input/output|osc. input/output|Crystal oscillator (32.768 kHz)|
|VSS1|15|**GND** for the clock (RTC)|power|to GND|
|VDD|16|**5V** (typical value) common positive supply|power|to VCC|

The last column shows the simplest way to connect the PCF8573 chip.

> [!NOTE]
> If the outputs are not used they may not be connected.
 
> [!CAUTION]
> Don't leave inputs unconnected to VCC or GND. Outputs not connected to VCC or GND may cause incorrect operation of the system!

Depending on your application, you may connect the chip differently. For instance, output pins can be used to read the COMP flag or the one-second/one-minute pulses directly in hardware. Additionally, setting inputs to VCC instead of GND allows you to modify the PCF8573 I2C address or change the behavior of the Power Fail Detector.

The address of the PCF8573 chip is set via inputs A0 and A1. Table of assigned addresses:
|A1 input state|A0 input state|PCF8573 address|
|:-:|:-:|:-:|
|GND|GND|`0x68`|
|GND|VCC|`0x69`|
|VCC|GND|`0x6A`|
|VCC|VCC|`0x6B`|

## 3. Usage

### 3.1 Basic setup

To use this library the aplication need to use the `<Wire.h>` library in your sketch, which allows communication with the chip via I2C. In addition to include, we need to properly initiate and start the transmission.

Include this library `<PCF8573.h>`.

Before using the library methods you need to create an instance of the `PCF8573` class e.g. `PCF8573 rtc (0x68);` where the parameter takes the value of the I2C address set via pins A0 and A1. In short this object represents the physical PCF8573 chip with a given address *0x68* connected via I2C.

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

All available methods and their syntax are described in  [paragraph 4](#4-methods).

#### Simple example of use:
This program sets the time to 12:34 and display it on the Serial Monitor (in Arduino IDE). We can see how minutes and later hours increment.
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

To set the time, use the `setTime()` method which requires a time field identifier and your value e.g. `setTime(PCF8573::time::HOURS, 7)` that means set the *hours register* to 7.

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
> Incorrect values ​​sent may cause the chip to malfunction!

> [!IMPORTANT]
> Leap year support (February 29) must be handled externally because the PCF8573 does not have a year counter.

#### 4.1.2 Read the time

To read the time, use the `readTime()` method which requires a time field identifier e.g. `readTime(PCF8573::time::MINUTES)` that means read the *minutes register*. This method returns a `uint8_t` value.

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

To set the alarm time, use the `setAlarmTime()` method which requires a time field identifier and your value e.g. `setAlarmTime(PCF8573::time::DAYS, 21)` that means set the *days alarm register* to 21.

**setAlarmTime()** parameters:

|Function| setAlarmTime() | accepted values |
| :--- | --- | ------------- |
|Set alarm hours| `setAlarmTime(PCF8573::time::HOURS, value);` | 0 to 23 |
|Set alarm minutes| `setAlarmTime(PCF8573::time::MINUTES, value);` | 0 to 59 |
|Set alarm days| `setAlarmTime(PCF8573::time::DAYS, value);` | 1 to 28 / 29 <br> 1 to 30 <br> 1 to 31 |
|Set alarm months| `setAlarmTime(PCF8573::time::MONTHS, value);` | 1 to 12 |

#### 4.2.2 Read the alarm time

To read the alarm time, use the `readAlarmTime()` method which requires a time field identifier e.g. `readAlarmTime(PCF8573::time::MONTHS)` that means read the *months alarm register*. This method returns a `uint8_t` value.

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
|POWF|The flag indicates a detected power failure<br>[More information about Power Fail Detector and POWF flag in chapter 5](#5-power-fail-detector)|When a power failure occurs|By setting the time or alarm time|
|COMP|The flag signals that the alarm has sounded|When *alarm time* is the same as RTC *time*|By user|
|NODA|The flag says to ignore the date when comparing the alarm and time (when comparing we only look at hours and minutes)|By user|By user|

#### 4.3.1 Read the flag

To read the flag, use the `readFlag()` method which requires a time field identifier e.g. `readFlag(PCF8573::flag::COMP)` that means read the *COMP flag register*. This method returns a `bool` value.

**readFlag()** parameters:

|Function| readFlag() |
| :--- | --- |
|Read POWF flag| `readFlag(PCF8573::flag::POWF);` |
|Read COMP flag| `readFlag(PCF8573::flag::COMP);` |
|Read NODA flag| `readFlag(PCF8573::flag::NODA);` |

#### 4.3.2 Reset the flag

To reset the flag, use the `resetCOMPflag()` or `resetNODAflag()` method. Reset means changing the state of the flag from 1 to 0.

#### 4.3.3 Set the flag

To set the flag, use the `setNODAflag()` method. Set means changing the state of the flag from 0 to 1.

> [!NOTE]
> Using methods for flags, you can:
> - read one of three flags: `POWF`, `COMP`, `NODA`;
> - reset one of two flags: `COMP`, `NODA`;
> - set one: `NODA`;

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

## 5. Power Fail Detector

Power Fail Detector sets the `POWF` flag to 1 when a power failure occurs.

There are two types of power failure detection - **internal** and **external**.

**Internal mode:**
The flag indicates a detected power failure - VDD-VSS1 voltage reaches approximately 1.2V or less (Voltage of 1.2V due to the design of the PCF8573 chip to work with 1.2 V nickel cadmium battery).

**External mode:**
To use external power failure detection, the *EXTPF* input must be at logic HIGH (e.g. connected to VCC).

The `POWF` flag is set based on the *PFIN* input. If it goes to LOW state, the system interprets it as a power failure.

|EXTPF input state| PFIN input state | Function |
| :--: | :-: | --- |
|LOW| LOW | Power Fail Detector - **Internal mode**|
|LOW| HIGH | test mode - don't use
|HIGH| LOW | Power Fail Detector - **External mode** - **power supply status incorrect**|
|HIGH| HIGH | Power Fail Detector - **External mode** - **power supply status correct**|

> [!IMPORTANT]
> Power Fail Detector does not reset the `POWF` flag to 0. To reset this flag, you must set the time or alarm time.

## 6. Inspiration

This library was inspired by the PCF8574 Arduino library by MSZ98:
https://github.com/MSZ98/pcf8574

It is an independent implementation for the PCF8573 RTC chip.