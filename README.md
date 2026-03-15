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

To use this library you need to include the `<Wire.h>` library in your sketch, which allows communication with the module via I2C.

## 2. Usage

When you use the PCF8573 module, you can:
1. read and set the time
2. read and set the alarm time
3. read flags
4. call functions, e.g., set flags

### 2.1 Time operations

#### 2.1.1 Set the time

To set the time you use `setTime()` method which requires a time field identifier and your value e.g. `setTime(PCF8573::time::HOURS, 7)` that means set the *hours register* to 7.

`setTime()` parameters:

|Function| setTime() | accepted values |
| :--- | --- | ------------- |
|Set hours| `setTime(PCF8573::time::HOURS, value);` | 0 to 23 |
|Set minutes| `setTime(PCF8573::time::MINUTES, value);` | 0 to 59 |
|Set days| `setTime(PCF8573::time::DAYS, value);` | 0 to 28 / 29 <br> 0 to 30 <br> 0 to 31 |
|Set months| `setTime(PCF8573::time::MONTHS, value);` | 0 to 12 |

> [!NOTE]
> The **DAYS** register accepts values ​​appropriate to the month.

> [!WARNING]
> If you send incorrect values, the module may not work properly.

> [!IMPORTANT]
> Leap year support (February 29) must be handled externally because the PCF8573 does not have a year counter.

#### 2.1.2 Read the time

To read the time you use `readTime()` method which requires a time field identifier e.g. `readTime(PCF8573::time::MINUTES)` that means read the *minutes register*. This method return `uint8_t` value.

`readTime()` parameters:

|Function| readTime() |
| :--- | --- |
|Read hours| `readTime(PCF8573::time::HOURS);` |
|Read minutes| `readTime(PCF8573::time::MINUTES);` |
|Read days| `readTime(PCF8573::time::DAYS;` |
|Read months| `readTime(PCF8573::time::MONTHS);` |

### 2.2 Alarm time operations

The alarm works like an alarm clock. When the hour strikes, the **COMP flag** is set to 1, indicating that the hour has struck. More details in section [2.3 Flags operation](#2.3-Flags-operation).

#### 2.2.1 Set the alarm time

It is similar to setting the time but to set the alarm time you use `setAlarmTime()` method which requires a time field identifier and your value e.g. `setAlarmTime(PCF8573::time::DAYS, 21)` that means set the *days register* to 21.

`setAlarmTime()` parameters:

|Function| setAlarmTime() | accepted values |
| :--- | --- | ------------- |
|Set alarm hours| `setAlarmTime(PCF8573::time::HOURS, value);` | 0 to 23 |
|Set alarm minutes| `setAlarmTime(PCF8573::time::MINUTES, value);` | 0 to 59 |
|Set alarm days| `setAlarmTime(PCF8573::time::DAYS, value);` | 0 to 28 / 29 <br> 0 to 30 <br> 0 to 31 |
|Set alarm months| `setAlarmTime(PCF8573::time::MONTHS, value);` | 0 to 12 |

#### 2.2.2 Read the alarm time

It is similar to reading the time but read the time you use `readAlarmTime()` method which requires a time field identifier e.g. `readAlarmTime(PCF8573::time::MONTHS)` that means read the *months register*. This method return `uint8_t` value.

`readAlarmTime()` parameters:

|Function| readAlarmTime() |
| :--- | --- |
|Read alarm hours| `readAlarmTime(PCF8573::time::HOURS);` |
|Read alarm minutes| `readAlarmTime(PCF8573::time::MINUTES);` |
|Read alarm days| `readTAlarmime(PCF8573::time::DAYS;` |
|Read alarm months| `readAlarmTime(PCF8573::time::MONTHS);` |

### 2.3 Flags operation

The PCF8573 module has 3 flags:
|Flag|Description|method of set (0 to 1)|method of reset (1 to 0)|
|---|---|---|---|
|POWF|The flag indicates a detected power failure.|When a power failure occurs||
|COMP|The flag signals that the alarm has sounded|When *alarm time* is the same as RTC *time*|By user|
|NODA|The flag says to ignore the date when comparing the alarm and time (we only compare hours and minutes)|By user|By user|

#### 2.3.1 Read the flag

We can read one of the three flags. To read the time you use `readFlag()` method which requires a time field identifier e.g. `readFlag(PCF8573::time::COMP)` that means read the *COMP flag register*. This method return `bool` value.

`readFlag()` parameters:

|Function| readAlarmTime() |
| :--- | --- |
|Read POWF flag| `readFlag(PCF8573::time::POWF);` |
|Read COMP flag| `readFlag(PCF8573::time::COMP);` |
|Read NODA flag| `readFlag(PCF8573::time::NODA);` |

#### 2.3.2 Reset the flag

We can reset COMP or NODA flag by functions: `resetCOMPflag()` or `resetNODAflag()`. Reset means changing the state of the flag from 1 to 0.

#### 2.3.3 Set the flag

We can only set NODA flag by function: `setNODAflag()` Set means changing the state of the flag from 0 to 1.

## 3. Inspiration

This library was inspired by the PCF8574 Arduino library by MSZ98:
https://github.com/MSZ98/pcf8574

It is an independent implementation for the PCF8573 RTC chip.