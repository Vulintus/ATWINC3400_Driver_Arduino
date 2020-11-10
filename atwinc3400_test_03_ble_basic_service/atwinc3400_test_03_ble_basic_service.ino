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
    digitalWrite(LED_BUILTIN, 0);

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
            status = VulintusArduinoBLE::BLE.SetDeviceName("ATWINC3400_TEST");
            if (status == at_ble_status_t::AT_BLE_SUCCESS)
            {
                Serial.println("SUCCESS: Set BLE device name.");
            }
            else
            {
                Serial.println("ERROR: Unable to set BLE device name");
            }

            //Set the advertised service
            VulintusArduinoBLE::BLE.SetAdvertisedService(test_service);
            Serial.println("SUCCESS: Set the advertised service UUID");

            //Add a characteristic to the service
            test_service.AddCharacteristic(test_characteristic);
            Serial.println("SUCCESS: Added a characteristic to the service");

            //Add the service to the local device
            status = VulintusArduinoBLE::BLE.AddService(test_service);
            if (status == at_ble_status_t::AT_BLE_SUCCESS)
            {
                Serial.println("SUCCESS: Added service to local device. ");
                String service_uuid = test_service.GetServiceUUID();
                at_ble_handle_t service_handle = test_service.GetServiceHandle();
                Serial.print("Service UUID: ");
                Serial.print(service_uuid);
                Serial.print(", Service Handle: ");
                Serial.print((uint16_t) service_handle);
                Serial.println();
                Serial.print("Characteristic UUID: ");
                Serial.print(test_characteristic.uuid());
                Serial.print(", Characteristic Value Handle: ");
                Serial.print((uint16_t) test_characteristic.GetCharacteristicValueHandle());
                Serial.println();
            }
            else
            {
                Serial.println("ERROR: Unable to add service to local device.");
            }
            
            //Write an initial value to the characteristic
            status = test_characteristic.writeValue(0);
            if (status == at_ble_status_t::AT_BLE_SUCCESS)
            {
                Serial.println("SUCCESS: Wrote new value to characteristic");
            }
            else
            {
                Serial.println("ERROR: Unable to write value to characteristic");
            }
            
            //Advertise our service
            status = VulintusArduinoBLE::BLE.Advertise();
            if (status)
            {
                Serial.println("SUCCESS: Advertising");
            }
            else
            {
                Serial.println("ERROR: Unable to advertise successfully");
            }

            //Print the BLE device address
            String ble_device_address = VulintusArduinoBLE::BLE.GetAddress(true);
            Serial.print("BLE DEVICE ADDRESS: ");
            Serial.println(ble_device_address);
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
    //VulintusArduinoBLE::BLEDevice central = VulintusArduinoBLE::BLE.central();

    //If so...
    /*
    if (central)
    {
        Serial.print("Central device has connected: ");
        Serial.println(central.address());

        
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
    */
}