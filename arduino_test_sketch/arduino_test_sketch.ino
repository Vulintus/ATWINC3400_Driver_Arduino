#include <m2m_ble.h>
#include <WiFi101.h>

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

WiFiServer server(80);
uint8_t status = 0;
char ssid[] = "ATWINC3400_TEST";

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
    
    //Print where to go in the browser
    Serial.print("To see this page in action, open a browser to http://");
    Serial.println(ip);
}

// the setup function runs once when you press reset or power the board
void setup(void)
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

    //Inititalize the built-in LED on the SAMD21 Xplained Pro.
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

        //Create a wifi access point
        status = WiFi.beginAP(ssid);
        if (status != WL_AP_LISTENING)
        {
            Serial.println("ERROR: Failed to create access point!");
            
            //don't continue
            while(true);
        }
        else
        {
            Serial.println("SUCCESS: Access pointed created.");
        }

        //Initialize the web server
        server.begin();
        
        //Print the WiFI status
        printWiFiStatus();  
    }
}

// the loop function runs over and over again forever
void loop(void)
{
    //Check to see if the status has changed
    if (status != WiFi.status())
    {
        //Update the status variable to be the new status
        status = WiFi.status();
        
        //Check to see if a new client has connected to the WiFi access point
        if (status == WL_AP_CONNECTED)
        {
            byte remote_device_mac_address[6];
            WiFi.APClientMacAddress(remote_device_mac_address);
            
            Serial.print("New device connected to access point: ");
            printMacAddress(remote_device_mac_address);
        }
    }
    
    //Check to see if any clients are connected
    WiFiClient client = server.available();
    
    if (client)
    {
        //If we found a client, output a message indicating a new client was found
        Serial.println("New client found");  

        //Create an empty string to hold our received message
        String received_msg = "";
        
        //Loop while the client's connected
        bool currentLineIsBlank = true;
        while (client.connected()) 
        {
            //If there are bytes to read from the client...
            if (client.available()) 
            {
                //Read a byte
                char c = client.read();

                if (c == '\n' && currentLineIsBlank) 
                {
                    //Send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");        //The connection will be closed after completion of the response
                    client.println("Refresh: 5");               //Refresh the page automatically every 5 sec
                    client.println();
                    client.println("<!DOCTYPE HTML>");
                    client.println("<html>");
                    client.println("Hello, World!");
                    client.println("</html>");

                    break;
                }

                if (c == '\n') 
                {
                    // you're starting a new line
                    currentLineIsBlank = true;
                }
                else if (c != '\r') 
                {
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }
        }

        //Give the web browser time to receive the data
        delay(100);
        
        //Disconnect from the client
        client.stop();

        //Output a message over the serial line
        Serial.println("Client disconnected");
    }    
}
