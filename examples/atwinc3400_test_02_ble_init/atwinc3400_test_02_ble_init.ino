#include <Vulintus_WiFi3400.h>
#include <Vulintus_BLE3400.h>

#include "board_pin_definitions.h"

sint8 status;

void setup()
{
    //Initialize the serial port
    Serial.begin(115200);

    //Countdown to initialization
    Serial.print("Setup wil begin in... ");
    for (int i = 10; i > 0; i--)
    {
        Serial.print(" ");
        Serial.print(i);
        Serial.print(" ");
        delay(1000);
    }

    Serial.println("Setup begins now...");

    //Initialize the built-in LED on the SAMD21 Xplained Pro.
    pinMode(LED_BUILTIN, OUTPUT);

    //Set the pins that will be used to communicate with the ATWINC3400
    WiFi.setPins(WINC_SS, WINC_IRQ, WINC_RESET, WINC_EN);

    //Check to see if the wifi module was found
    if (WiFi.status() == WL_NO_SHIELD)
    {
        Serial.println("ERROR: WiFi module not found!");
        
        //don't continue:
        while (true);
    }
    else
    {
        Serial.println("SUCCESS: Wifi module found.");

        //Initialize the wifi module
        WiFi.begin();

        //Initialize the BLE module
        status = VulintusArduinoBLE::BLE.Begin();
        if (status == M2M_SUCCESS)
        {
            Serial.println("SUCCESS: BLE module initialized.");

            //Set the name of the BLE device
            VulintusArduinoBLE::BLE.SetDeviceName("ATWINC3400_TEST");
        }
        else
        {
            Serial.println("ERROR: Failed to initialize BLE module.");
            Serial.print("Error code: ");
            Serial.println(status);
            while(1);
        }
    }    
}

void loop()
{
    //empty
}