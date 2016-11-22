/*****************************************************************************/
/*
  Example for Atmel Sigfox shield ATA8520-EK2-E.

  This Arduino sketch sends temperature measurement every 15 minutes
  (or when shield button is pressed), using Sigfox network.
  
  This sketch uses the Atmel Sigfox shield library included.
*/
/*****************************************************************************/

#include "AtmSIGFOXshd.h"    // Atmel SIGFOX shield library

SIGFOXshield sigfox;          // load class SIGFOXshield

#define TIMEINTERVALL 900000 // 900 sec -> 15 min sleep time

unsigned long timer;          // Timer for sleeping
unsigned int count=0;         // Message counter

boolean ishere;

void setup() {
  Serial.begin(9600);
  ishere = sigfox.begin();             // Initialize library (True is present otherwise False)
  if (!ishere) {
	  Serial.println("Shield error or not present!");
	  return;
  }
                                  // Display information
  Serial.print("\r\n\r\n---------------- Sigfox ATA8520-EK2-E Demo V1.0.0 ------------------------\r\n");
  Serial.print("                       Sensor Sigfox Transmitter\r\n");
  Serial.print("--------------------------------------------------------------------------\r\n");
  Serial.print("\r\nWaiting for Timer... or button press\r\n");

  sigfox.SIGFOXoff();               // Switch off Sigfox module
  sigfox.TempOff();                 // Switch off temperature sensor

  timer = millis()+TIMEINTERVALL;    // Initialize timer for wake-up
}


void loop()
{
  if (!ishere) return;
  if (sigfox.getButton()){          // If it is sleeping but button pressed
    sensorActivity();               // Act
    delay(300);
  }
  if (millis()>timer){               // If timer expired
	   sensorActivity();
	   timer = millis()+TIMEINTERVALL;			// Act and reset timer
  }
  delay(300);
}

void sensorActivity()
{
	float t;
    count++;                         // Increment message counter
    Serial.print("Sigfox message number ");
	  Serial.println(count);
    sigfox.SIGFOXon();                // Switch on SIGFOX module and temp. module
    sigfox.TempOn();
    t = sigfox.readTemp();        // Read temperature (Celsius degrees)
    sigfox.TempOff();                 // Switch off modules
    Serial.print("  Temperature : ");
	  Serial.print(t);
	  Serial.println(" C");
    sendvalues(t);                 // Send values
    sigfox.SIGFOXoff();
}

void sendvalues(float t)
{
    int i;
    unsigned char sigfoxBuff[20];         // Sending buffer
    for(i = 0; i < 11; i++){
		    sigfoxBuff[i] = 0x00;   // Initialize first 9 bytes as 0
	  }
    int it = int(t);                   // Float temp to int
    sigfoxBuff[11] = lowByte(it);            // Temp to buffer
    Serial.print("  Sending(hex): ");
    for(i = 0; i < 12; i++){
        Serial.print(sigfoxBuff[i], HEX);
	  }
	  Serial.println();
    int ret = sigfox.sendMessage(sigfoxBuff,12);     // Send buffer to SIGFOX network
    Serial.println(sigfox.getStatusSig());
    if (ret > 0){
      Serial.println("No transmission!");
    }
}
