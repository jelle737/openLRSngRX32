#include "board.h"

/* RX32 SPI layout
  PB13 SPI2 SCK
  PB14 SPI2 MISO
  PB15 SPI2 MOSI
  PB12 GPIO (SPI2NSS) RFM1CS
  PC15 GPIO RFM2CS
*/

void configureSPI()
{
  //  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef SPI_InitStruct;
  SPI_I2S_DeInit(SPI2);

  // Init pins
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15; // SCK,MOSI
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; // MISO
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; // CS1
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; // CS2
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);



  SPI_StructInit(&SPI_InitStruct);
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  SPI_Cmd(SPI2, ENABLE);
  SPI_Init(SPI2, &SPI_InitStruct);
  SPI_NSSInternalSoftwareConfig(SPI2, SPI_NSSInternalSoft_Set);
}



