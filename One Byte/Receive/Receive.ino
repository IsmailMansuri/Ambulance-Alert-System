//Receiver program
#include <SPI.h>
#include "nRF24L01.h"

int led_pin=2;

Nrf24l Mirf = Nrf24l(10, 9);

byte value;

void setup()
{
  pinMode(led_pin,OUTPUT);
  
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"FGHIJ"); //Set your own address (receiver address) using 5 characters
  Mirf.payload = sizeof(value);
  Mirf.channel = 90;             //Set the used channel
  Mirf.config();
  Serial.println("Listening...");  //Start listening to received data
}

void loop()
{

  digitalWrite(led_pin,HIGH);
  delay(250);
  digitalWrite(led_pin,LOW);
  delay(250);
  
  if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData(&value);
    Serial.print("Got data: ");
    Serial.println(value);
  }
}
