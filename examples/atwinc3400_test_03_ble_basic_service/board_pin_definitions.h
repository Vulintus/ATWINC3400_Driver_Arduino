#ifndef __BOARD_PIN_DEFINITIONS_H
#define __BOARD_PIN_DEFINITIONS_H

#define BOARD_SAMD21_XPLAINED_PRO               1
#define BOARD_VULINTUS_HABITRAK_V1              2

#ifndef BOARD_TYPE
#define BOARD_TYPE      BOARD_VULINTUS_HABITRAK_V1
#endif

#if (BOARD_TYPE == BOARD_SAMD21_XPLAINED_PRO)

/*
 * These pinouts assume the following:
 * 1. The board you are using is the SAMD21 Xplained Pro with a SAMD21J18A
 * 2. The ATWINC3400 is on a WINC3400 Xplained Pro board attached to EXT1.
 * 3. You have installed the SAMD21 Xplained Pro board package for the Arduino IDE
 *      from the AtmelUniversityFrance Github page. The URL is here:
 * https://github.com/AtmelUniversityFrance/atmel-samd21-xpro-boardmanagermodule/wiki/GettingStarted:-SAMD21-Xplained-Pro
 * 
 * If the above conditions are not true, the pinouts should be changed to match
 * your setup.
 */
#define WINC_IRQ          	6     		//Digital input for the ATWINC3400 interrupt output.
#define WINC_SS 			PIN_SPI_SS  //Digital output for the ATWINC3400 SPI slave select.	
#define WINC_RESET        	A1          //Digital output for the ATWINC3400 reset input.
#define WINC_EN		       	7           //Digital output for the ATWINC3400 enable input.

#elif (BOARD_TYPE == BOARD_VULINTUS_HABITRAK_V1)

#define WINC_IRQ          	9     		//Digital input for the ATWINC3400 interrupt output.
#define WINC_SS 			10          //Digital output for the ATWINC3400 chip select.	
#define WINC_RESET        	7           //Digital output for the ATWINC3400 reset input.
#define WINC_EN		       	8           //Digital output for the ATWINC3400 enable input.

#define LED_BUILTIN         30          //Status LED

#endif

#endif /* __BOARD_PIN_DEFINITIONS_H */