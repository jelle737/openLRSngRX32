#include "board.h"
static void _putc(void *p, char c)
{
    uartWrite(c);
}


int main(void)
{
  uint8_t i,leds=7;
  systemInit();
  init_printf(NULL, _putc);
  uartInit(115200);

  configurePWMs();
  configureSPI();
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
    printf("uptime is %d\n",micros());
    
    while (uartAvailable()) {
      uint8_t c = uartRead();
      printf("Got (%c)\n");
      if (c == 'R') {
	systemReset(true);      // reboot to bootloader
      }
    }
    
    SPI_I2S_SendData(SPI2, 0x55);
    delay(100);
  }
}
