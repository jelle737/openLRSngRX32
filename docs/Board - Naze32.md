# Board - AbuseMark Naze32

The Naze32 target supports all Naze hardware revisions.  Revision 4 and 5 are used and
frequently flown by the primary maintainer.  Previous Naze hardware revisions may have issues,
if found please report via the [github issue tracker](https://github.com/cleanflight/cleanflight/issues).

## Serial Ports

| Value | Identifier   | RX         | TX                 | Notes                                                                                       |
| ----- | ------------ | ---------- | ------------------ | ------------------------------------------------------------------------------------------- |
| 1     | USART1       | RX  / PA10 | TX  / PA9 / TELEM  | TELEM output is always inverted (for FrSky). Internally connected to USB port via CP2102 IC |
| 2     | USART2       | RC4 / PA3  | RC3 / PA2          |                                                                                             |
| 3     | USART3       |     / PB11 |     / PB10         | UART3 is only available directly on STM32F10x and is beeing used as I2C**2**                |
| 4     | SOFTSERIAL1  | RC5 / PA6  | RC6 / PA7          |                                                                                             |
| 5     | SOFTSERIAL2  | RC7 / PB0  | RC8 / PB1          |                                                                                             |

* You cannot use USART1/TX/TELEM pins at the same time. 
* You may encounter flashing problems if you have something connected to the RX/TX pins.  Try disconnecting RX/TX.

## Pinouts

The 10 pin RC I/O connector has the following pinouts when used in RX_PPM/RX_SERIAL mode.

| Pin | Identifier | STM32 | Function                    | Notes                            |
| --- | ---------- | ----- | --------------------------- | -------------------------------- |
| 1   |            |       | Ground                      |                                  |
| 2   | Circle     |       | +5V                         |                                  |
| 3   | 1          | PA0   | RX_PPM                      | Enable `feature RX_PPM`          | 
| 4   | 2          | PA1   | RSSI_ADC                    | Enable `feature RSSI_ADC`.  Connect to the output of a PWM-RSSI conditioner, 0v-3.3v input | 
| 5   | 3          | PA2   | USART2 TX                   |                                  | 
| 6   | 4          | PA3   | USART2 RX                   |                                  | 
| 7   | 5          | PA6   | LED_STRIP                   | Enable `feature LED_STRIP`       |
| 8   | 6          | PA7   | unused                      |                                  |
| 9   | 7          | PB0   | Sonar Trigger               |                                  |
| 10  | 8          | PB1   | Sonar Echo / CURRENT        | Enable `feature CURRENT_METER`  Connect to the output of a current sensor, 0v-3.3v input |

When SOFTSERIAL is enabled, LED_STRIP and CURRENT_METER are unavailable, but two SoftSerial ports are made available to use instead.

| Pin | Identifier | STM32 | Function               | Notes                            |
| --- | ---------- | ----- | ---------------------- | -------------------------------- |
| 7   | 5          | PA6   | SOFTSERIAL1 RX         | Enable `feature SOFTSERIAL`      |
| 8   | 6          | PA7   | SOFTSERIAL1 TX         |                                  |
| 9   | 7          | PB0   | SOFTSERIAL2 RX         |                                  |
| 10  | 8          | PB1   | SOFTSERIAL2 TX         |                                  |

Motor output pins

| Pin | Identifier | STM32 | Function               | Notes                            |
| --- | ---------- | ----- | ---------------------- | -------------------------------- |
| 1   | 1          | PA8   |                        |                                  |
| 2   | 2          | PA11  |                        |                                  |
| 3   | 3          | PB6   |                        |                                  | 
| 4   | 4          | PB7   |                        |                                  | 
| 5   | 5          | PB8   |                        |                                  | 
| 6   | 6          | PB9   |                        |                                  | 

Some SMD pads across front and back of the board with silkscreens

| Pin | Identifier | STM32 | Function               | Notes                            |
| --- | ---------- | ----- | ---------------------- | -------------------------------- |
| 1   | VBAT       | PA4   |                        |                                  |
| 2   | BUZZ       | PA12  | BEEPER                 |                                  |
| 3   | TELEM      | PA9   |                        | Internally connected to USB port via CP2102 IC | 
| 4   | SDA        | PB11  | I2C Connector          | 3.3v, is UART3                   | 
| 5   | SCL        | PB10  | I2C Connector          | 3.3v                             | 
| 6   | ADC        | PA5   |                        | 3.3v EXTERNAL1_ADC_PIN           | 
| 7   | GPIO/FT    | PA15  |                        | 5v tollerant                     | 
| 8   | GPIO       | PB5   |                        | 3.3v                             | 
| 9   | RX         | PA10  |                        |                                  | 
| 10  | TX         | PA9   |                        | Internally connected to USB port via CP2102 IC | 
| 11  | SWD        |       |                        | Standaard debug connector        |

## Led Lights

The naze has 3 led's connected as follows to the STM32F103 using the following pinouts.

| Led | Identifier | STM32 | Function               | Notes                            |
| --- | ---------- | ----- | ---------------------- | -------------------------------- |
| 0   | RED/GREEN  | PB3   |                        |                                  |
| 1   | GREEN/RED  | PB4   |                        |                                  |
| 2   | BLUE       | -     | +5V                    |                                  |

## Interconnections to SPI2

The Naze32 AfroFlight rev5 board has the SPI2 connections displayed in smd format to be used for the M25P16/W25Q128/... memory chip. This chip has 8 pins.

| Pin | Identifier | STM32 | Function               | Notes                            |
| --- | ---------- | ----- | ---------------------- | -------------------------------- |
| 1   | /CS        | PB12  | SPI2_NSS               |                                  |
| 2   | DO(IO1)    | PB14  | SPI2_MISO              |                                  |
| 3   | /WP(IO2)   | 3.3v  |                        |                                  | 
| 4   | GND        | GND   |                        |                                  | 
| 5   | DI(IO0)    | PB15  | SPI2_MOSI              |                                  | 
| 6   | CLK        | PB13  | SPI2_SCK               |                                  | 
| 7   | /HOLD      | 3.3v  |                        |                                  | 
| 8   | VCC        | 3.3v  |                        |                                  | 

## Recovery

### Board
+ Short the two pads labelled 'Boot' **taking extra care not to touch the 5V pad**
+ Apply power to the board
+ Remove the short on the board

### Cleanflight configurator
+ Select the correct hardware and the desired release of the Cleanflight firmware
+ Put a check in the "No reboot sequence" 
+ Flash firmware

```
/-------------------\
|O                 O|
| []5V              |
| [][]Boot          |
|                   |
|                   |
|                   |
|                   |
|O                 O|
\-------[USB]-------/
```

