/*
*   This file was created by David Pruitt.
*   This file does not exist in the original Atmel/Microchip code.
*   It is meant to support the Vulintus BLE library.
*
*   Date: 1 December 2020
*/

#include "common/include/nm_debug.h"

void (*application_specific_printf_function) (const char* fmt, ...);