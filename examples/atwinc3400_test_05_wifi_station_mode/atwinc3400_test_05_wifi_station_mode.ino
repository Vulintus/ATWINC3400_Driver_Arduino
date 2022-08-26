#include <Vulintus_WiFi3400.h>

#include "board_pin_definitions.h"

String ssid = "yourNetworkName";
String password = "yourNetworkPassword";

int status = 0;
int ping_spacing = 3000;
int last_ping = -1;

void printMacAddress(byte mac[]) 
{
    for (int i = 5; i >= 0; i--) 
    {
        if (mac[i] < 16) 
        {
            Serial.print("0");
        }
        
        Serial.print(mac[i], HEX);
        
        if (i > 0) 
        {
            Serial.print(":");
        }
    }
    
    Serial.println();
}

void printWiFiStatus() 
{
    //Print the MAC address of the wifi module
    Serial.print("MAC: ");
    byte remote_device_mac_address[6];
    WiFi.macAddress(remote_device_mac_address);
    printMacAddress(remote_device_mac_address);

    //Print the SSID of the access point
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    //Print the IP address of the wifi module
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    //Print the signal strength
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}

// the setup function runs once when you press reset or power the board
void setup(void)
{
    //Initialize the serial port
    Serial.begin(115200);

    //Countdown to initialization
    Serial.print("Setup will begin in... ");
    for (int i = 10; i > 0; i--)
    {
        Serial.print(" ");
        Serial.print(i);
        Serial.print(" ");
        delay(1000);
    }

    Serial.println("Setup begins now...");

    //Inititalize the built-in LED on the board.
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

        //Scan for wifi networks
        Serial.println("Scanning for networks");
        int num_networks = WiFi.scanNetworks();
        Serial.print("Networks found: ");
        Serial.println(num_networks);
        Serial.println("Listing networks that were found:");
        for (int i = 0; i < num_networks; i++)
        {
            Serial.print("(");
            Serial.print(i+1);
            Serial.print(") ");
            Serial.println(WiFi.SSID(i));
        }
        Serial.println("DONE listing networks");        

        //Create a wifi access point
        status = WiFi.begin(ssid, password);
        if (status != WL_CONNECTED)
        {
            Serial.println("ERROR: Failed to connect to access point!");
            
            //don't continue
            while(true);
        }
        else
        {
            Serial.println("SUCCESS: Connected to access point.");
        }
        
        //Print the WiFI status
        printWiFiStatus();  
    }
}

// the loop function runs over and over again forever
void loop(void)
{
    //Let the WiFi process messages
    WiFi.status();

    //Try to ping google servers at a regular interval of every N seconds
    int current_millis = millis();
    if ((last_ping == -1) || (current_millis >= (last_ping - ping_spacing)))
    {
        last_ping = current_millis;

        int result = WiFi.ping("www.google.com");
        if (result > 0)
        {
            Serial.println("SUCCESS: ping to Google servers was successful.");
            Serial.print("Ping time: ");
            Serial.println(result);
        }
        else
        {
            Serial.println("ERROR: was unable to ping Google servers.");
        }        
    }
}
