#include "board.h"
static void _putc(void *p, char c)
{
    uartWrite(c);
}


void checkReflash()
{
  uint32_t i;
  LEDB_ON;
  for (i=0; i<50; i++) {
    delay(100);
    uartWrite('?');
    if (i&1) {
      LEDG_ON;
      LEDR_OFF;
    } else {
      LEDG_OFF;
      LEDR_ON;
    }

    if (uartAvailable() && ('R' == uartRead())) {
      systemReset(true);      // reboot to bootloader
    }
  }
  LEDB_OFF;
  LEDG_OFF;
}

int main(void)
{
  uint8_t i,leds=7;
  systemInit();
  delay(10);
  init_printf(NULL, _putc);
  uartInit(115200);
  delay(100);
  checkReflash();
  i2cInit(I2C2);
  for (i=0; i<16; i++) {
    setPWM(i,1000+i*50);
  }
  configurePWMs();
  configureSPI();

  if (mpu6050Detect(256, &i)) {
    printf("MPU detected, scale %d\n",i);
    mpu6050AccInit();
    mpu6050GyroInit();
  } else {
    printf("MPU not detected?\n");
  }

  // loopy
  while (1) {

    uartWrite('U');

    if (leds&8) {
      LEDR_ON;
    } else {
      LEDR_OFF;
    }
    if (leds&16) {
      LEDG_ON;
    } else {
      LEDG_OFF;
    }
    if (leds&32) {
      LEDB_ON;
    } else {
      LEDB_OFF;
    }
    leds<<=1;
    if (!leds) leds=7;

    while (uartAvailable()) {
      uint8_t c = uartRead();
      printf("Got (%x)\n",c);
      if (c == 'R') {
	systemReset(true);      // reboot to bootloader
      }
    }

    printf("RFM1: reg0=%x reg1=%x",rfmReadRegister(1,0),rfmReadRegister(1,1));
    printf("RFM2: reg0=%x reg1=%x",rfmReadRegister(2,0),rfmReadRegister(2,1));

    {
      int16_t data[3];
      mpu6050AccRead(data);
      printf("ACC\t%d\t%d\t%d\t",data[0],data[1],data[2]);
      mpu6050GyroRead(data);
      printf("GYR\t%d\t%d\t%d\r\n",data[0],data[1],data[2]);
    }


    delay(100);
  }
}
