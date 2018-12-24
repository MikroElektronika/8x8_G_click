/*
Example for 8x8_G Click

    Date          : Jan 2018.
    Author        : MikroE Team

Test configuration KINETIS :
    
    MCU              : MK64
    Dev. Board       : HEXIWEAR
    ARM Compiler ver : vCANT_FIND_VERSION

---

Description :

The application is composed of three sections :

- System Initialization - Intializes CS pin as output and SPI module
- Application Initialization - Driver intialization and default configration
of the 8x8 click board and settings speed scroll as Midium speed and refresh display.
- Application Task - (code snippet) - Shows one byte, then scrolls the string and image, every 1 sec.

*/

#include "Click_8x8_G_types.h"
#include "Click_8x8_G_config.h"

uint8_t demoString[11]={ ' ','-','M','i','k','r','o','E','-',' ',0 };
uint8_t demoImgOn[8]={0x08, 0x1c, 0x36, 0x22, 0x08, 0x1c, 0x36, 0x22};
uint8_t demoImgOff[8]={0xf7, 0xe3, 0xc9, 0xdd, 0xf7, 0xe3, 0xc9, 0xdd};
char demoChar = 'G';

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );
    mikrobus_spiInit( _MIKROBUS1, &_C8X8G_SPI_CFG[0] );
    Delay_100ms();
}

void applicationInit()
{
    c8x8g_spiDriverInit( (T_C8X8G_P)&_MIKROBUS1_GPIO, (T_C8X8G_P)&_MIKROBUS1_SPI );

    c8x8g_writeCmd(_C8X8G_DECODE_MODE_REG, _C8X8G_NO_DECODE);
    c8x8g_writeCmd(_C8X8G_INTENSITY_REG,   _C8X8G_INTENSITY_15);
    c8x8g_writeCmd(_C8X8G_SCAN_LIMIT_REG,  _C8X8G_DISPLAY_DIGIT_0_7);
    c8x8g_writeCmd(_C8X8G_SHUTDOWN_REG,    _C8X8G_NORMAL_OPERATION);

    c8x8g_setSpeedScroll(_C8X8G_SPEED_MEDIUM);
    c8x8g_displayRefresh();
    Delay_100ms();
}

void applicationTask()
{
    c8x8g_displayByte(demoChar);
    Delay_ms( 1000 );
    c8x8g_displayString(&demoString[0]);
    Delay_ms( 1000 );
    c8x8g_displayImage(&demoImgOn[0]);
    Delay_ms( 500 );
    c8x8g_displayImage(&demoImgOff[0]);
    Delay_ms( 1000 );
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
        applicationTask();
    }
}