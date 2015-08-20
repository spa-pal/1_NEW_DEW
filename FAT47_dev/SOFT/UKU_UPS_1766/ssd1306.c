#include "i2c.h"
#include "ssd1306.h"
#include "LPC17xx.H"
#include "main.h"





void ssd1306SendByte(uint8_t byte)
{
i2c_Start();
i2c_SendByte(0x78);
if(i2c_ReadAcknowledge()) goto Stop_label_ssd1306_command;
i2c_SendByte(0x00);
if(i2c_ReadAcknowledge()) goto Stop_label_ssd1306_command;
i2c_SendByte(byte);
i2c_ReadAcknowledge();
Stop_label_ssd1306_command: 
i2c_Stop();
}

//-----------------------------------------------
void ssd1306_command(char cmnd)
{
i2c_Start();
i2c_SendByte(0x78);
if(i2c_ReadAcknowledge()) goto Stop_label_ssd1306_command;
i2c_SendByte(0x00);
if(i2c_ReadAcknowledge()) goto Stop_label_ssd1306_command;
i2c_SendByte(cmnd);
i2c_ReadAcknowledge();
Stop_label_ssd1306_command: 
i2c_Stop();
}

//-----------------------------------------------
void ssd1306_data(char data)
{
i2c_Start();
i2c_SendByte(0x78);
if(i2c_ReadAcknowledge()) goto Stop_label_ssd1306_command;
i2c_SendByte(0x40);
if(i2c_ReadAcknowledge()) goto Stop_label_ssd1306_command;
i2c_SendByte(data);
i2c_ReadAcknowledge();
Stop_label_ssd1306_command: 
i2c_Stop();
}


//-----------------------------------------------
void ssd1306_init(uint8_t vccstate)
{

 // Initialisation sequence
  CMD(SSD1306_DISPLAYOFF);                    // 0xAE
  CMD(SSD1306_SETLOWCOLUMN | 0x0);            // low col = 0
  CMD(SSD1306_SETHIGHCOLUMN | 0x0);           // hi col = 0
  CMD(SSD1306_SETSTARTLINE | 0x0);            // line #0
  CMD(SSD1306_SETCONTRAST);                   // 0x81
  if (vccstate == SSD1306_EXTERNALVCC) 
    { CMD(0x9F) }
  else 
    { CMD(0xCF) }
  CMD(0xa1);                                  // setment remap 95 to 0 (?)
  CMD(SSD1306_NORMALDISPLAY);                 // 0xA6
  CMD(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
  CMD(SSD1306_SETMULTIPLEX);                  // 0xA8
  CMD(0x3F);                                  // 0x3F 1/64 duty
  CMD(SSD1306_SETDISPLAYOFFSET);              // 0xD3
  CMD(0x00);                                   // no offset
  CMD(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
  CMD(0x80);                                  // the suggested ratio 0x80
  CMD(SSD1306_SETPRECHARGE);                  // 0xd9
  if (vccstate == SSD1306_EXTERNALVCC) 
    { CMD(0x22) }
  else 
    { CMD(0xF1) }
  CMD(0x2E); // отключен скролл
  CMD(0xB0);
  CMD(SSD1306_SETCOMPINS);                    // 0xDA
  CMD(0x12);                                  // disable COM left/right remap
  CMD(SSD1306_SETVCOMDETECT);                 // 0xDB
  CMD(0x40);                                  // 0x20 is default?
  CMD(SSD1306_MEMORYMODE);                    // 0x20
  CMD(0x00);                                  // 0x0 act like ks0108
  CMD(SSD1306_SEGREMAP | 0x1);
  CMD(SSD1306_COMSCANDEC);
  CMD(SSD1306_CHARGEPUMP);                    //0x8D
  if (vccstate == SSD1306_EXTERNALVCC) 
    { CMD(0x10) }
  else 
    { CMD(0x14) }

  // Enabled the OLED panel
  CMD(SSD1306_DISPLAYON);
}

