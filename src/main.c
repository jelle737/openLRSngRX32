#include "board.h"
static void _putc(void *p, char c)
{
    uartWrite(c);
}


void checkReflash()
{
  uint32_t time,i=0;
  time=millis();
  LEDB_ON;
  while ((millis() - time) < 2000) {
    delay(100);
    if ((i++)&1) {
      LEDG_ON;
    } else {
      LEDG_OFF;
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
  init_printf(NULL, _putc);
  uartInit(115200);
  delay(100);
  checkReflash();
  configureSPI();
  configurePWMs();
  for (i=0; i<16; i++) {
    setPWM(i,1000+i*50);
  }

  // loopy
  while (1) {

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
      printf("Got (%c)\n");
      if (c == 'R') {
	systemReset(true);      // reboot to bootloader
      }
    }

    printf("reg0=%x\r\n",rfmReadRegister(1,0));
    printf("reg1=%x\r\n",rfmReadRegister(1,1));

    delay(100);
  }
}
