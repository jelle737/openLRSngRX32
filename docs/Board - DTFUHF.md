# Board - DTFUHF-10ch-32

A writedown of the hardware as seen from the DipTrace files to be found on GitHub (https://github.com/akadamson/DTFUHF-10ch-32). 

## Serial Ports

| Value | Identifier   | RX         | TX            | Notes                            |
| ----- | ------------ | ---------- | ------------- | -------------------------------- |
| 1     | USART1       | RX  / PA10 | TX  / PA9     | Internally connected to USB port via CP2102 IC |
| 2     | USART2       | RC4 / PA3  | RC3 / PA2     |                                  |
| 3     | USART3       | SDA / PB11 | SCL / PB10    | Max 3.3v                         |
| 4     | SOFTSERIAL1  | RC5 / PA6  | RC6 / PA7     |                                  |
| 5     | SOFTSERIAL2  | RC7 / PB0  | RC8 / PB1     |                                  |

* You cannot use USART1/TX pins at the same time. 
* You may encounter flashing problems if you have something connected to the RX/TX pins.  Try disconnecting RX/TX.

## Pinouts

The 10 pin RC I/O connector has the following pinouts when used in RX_PPM/RX_SERIAL mode.

| Pin | Identifier | STM32 | Function               | Notes                            |
| --- | ---------- | ----- | ---------------------- | -------------------------------- |
| 1   | (PWM)1     | PA0   | ~RX_PPM                |                                  |
| 2   | (PWM)2     | PA1   | ~RSSI_ADC              |                                  |
| 3   | 3          | PA2   | USART2 TX              |                                  | 
| 4   | 4          | PA3   | USART2 RX              |                                  | 
| 5   | 5          | PA6   | ~LED_STRIP             | ~Enable `feature LED_STRIP`      | 
| 6   | 6          | PA7   | ~unused                |                                  | 
| 7   | 7          | PB0   | ~Sonar Trigger         |                                  |
| 8   | 8          | PB1   | ~Sonar Echo / CURRENT  | ~Enable `feature CURRENT_METER`  |
| 9   | RSSI       | PB9   |                        | Naze32.OUT6                      |
| 10  | PPM        | PA8   |                        | Naze32.OUT1                      |

When SOFTSERIAL is enabled, LED_STRIP and CURRENT_METER are unavailable, but two SoftSerial ports are made available to use instead.

| Pin | Identifier | STM32 | Function               | Notes                            |
| --- | ---------- | ----- | ---------------------- | -------------------------------- |
| 5   | (PWM)5     | PA6   | SOFTSERIAL1 RX         | Enable `feature SOFTSERIAL`      |
| 6   | (PWM)6     | PA7   | SOFTSERIAL1 TX         |                                  |
| 7   | (PWM)7     | PB0   | SOFTSERIAL2 RX         |                                  |
| 8   | (PWM)8     | PB1   | SOFTSERIAL2 TX         |                                  |

The FTDI programmer head has the following pinout

| Pin | Identifier | STM32 | Function               | Notes                            |
| --- | ---------- | ----- | ---------------------- | -------------------------------- |
| 1   | GND        | -     | Ground                 |                                  |
| 2   | SCL        | PB10  | USART3 TX              | Max 3.3v                         |
| 3   | SDA        | PB11  | USART3 RX              |                                  | 
| 4   | 5V         | -     | +5V                    |                                  | 
| 5   | TX         | PA9   | USART1 TX              | Internally connected to USB port via CP2102 IC | 
| 6   | RX         | PA10  | USART1 RX              | Max 3.3v                         | 
| 7   | GND        | -     | Ground                 |                                  |

Some SMD pads across front and back of the board with silkscreens

| Pin | Identifier | STM32 | Function               | Notes                            |
| --- | ---------- | ----- | ---------------------- | -------------------------------- |
| 1   | swclk      | PA14  |                        |                                  |
| 2   | swdio      | PA13  |                        |                                  |
| 3   | rst        | NRST  |                        |                                  | 

## LED lights

The green and red leds are connected to the STM32F103 using the following pinouts.

| Led | Identifier | STM32 | Function               | Notes                            |
| --- | ---------- | ----- | ---------------------- | -------------------------------- |
| 1   | RED        | PA11  |                        | Naze32.OUT2                      |
| 2   | GREEN      | PA12  |                        | Naze32.BEEPER                    |


## Interconnections to FRM22SMD

The FRM22SMD is connected to the STM32F103 using the following pinouts.

| Pin | Identifier | STM32 | Function               | Notes                            |
| --- | ---------- | ----- | ---------------------- | -------------------------------- |
| 10  | SDO        | PB14  |                        | Cleanflight.SPI2                 |
| 11  | SDI        | PB15  |                        |                                  |
| 12  | SCLK       | PB13  |                        |                                  |
| 13  | NSEL       | PB12  |                        | Naze32.NAZE_SPI_CS_PIN           |
| 14  | NIRQ       | P**C**13  |                        | Naze32.MPU_INT_EXTI              |

## Recovery

### Board
+ Short the two pads labeled 'FLASH' (Connected to BOOT0)
+ Apply power to the board
+ Remove the short on the board

### Configurator
+ Select the correct hardware and the desired release of the firmware
+ Put a check in the "No reboot sequence" 
+ Flash firmware

```
/-----------------------\
|[]                     |
|[]             Boot [] |
|[]              GND [] |
|[]                     |
|[]     [][][]          |
\--[USB]----------------/
```

