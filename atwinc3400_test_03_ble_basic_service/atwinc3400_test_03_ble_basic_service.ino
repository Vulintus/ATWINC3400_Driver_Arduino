#include <WiFi101.h>
#include <ArduinoBLE.h>

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
#define WINC_WAKE			A0			//Digital output for the ATWINC3400 wake input.

sint8 status;
unsigned long prev_millis = 0;
unsigned long prev_pulse = 0;

VulintusArduinoBLE::BLEService test_service("181A");
VulintusArduinoBLE::BLEUnsignedCharCharacteristic test_characteristic("2A59", 
    VulintusArduinoBLE::BLEProperty::BLERead | VulintusArduinoBLE::BLEProperty::BLEWrite);

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
        status = VulintusArduinoBLE::BLE.begin();
        if (status == M2M_SUCCESS)
        {
            Serial.println("SUCCESS: BLE module initialized.");

            //Set the name of the BLE device
            VulintusArduinoBLE::BLE.setDeviceName("ATWINC3400_TEST");

            //Set the local name
            VulintusArduinoBLE::BLE.setLocalName("ATWINC3400_LOCAL_NAME_TEST");

            //Set the advertised service
            VulintusArduinoBLE::BLE.setAdvertisedService(test_service);

            //Add a characteristic to the service
            test_service.addCharacteristic(test_characteristic);

            //Add the service to the local device
            VulintusArduinoBLE::BLE.addService(test_service);

            //Write an initial value to the characteristic
            test_characteristic.writeValue(0);

            //Advertise our service
            VulintusArduinoBLE::BLE.advertise();
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
    unsigned long cur_pulse = millis();
    if (cur_pulse >= (prev_pulse + 10000))
    {
        prev_pulse = cur_pulse;
        Serial.print("Application debug pulse: ");
        Serial.println(cur_pulse);
    }

    //See if a "central" device has connected to this peripheral
    VulintusArduinoBLE::BLEDevice central = VulintusArduinoBLE::BLE.central();

    //If so...
    if (central)
    {
        Serial.print("Central device has connected: ");
        Serial.println(central.address());

        //Update the characteristic while the central is connected.
        while (central.connected())
        {
            unsigned long current_millis = millis();
            if (current_millis >= (prev_millis + 200))
            {
                prev_millis = current_millis;
                char rand = random(0, 100);
                test_characteristic.writeValue(rand);
            }
        }

        Serial.print("Disconnected from central device: ");
        Serial.println(central.address());
    }
}