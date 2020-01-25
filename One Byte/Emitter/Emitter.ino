//Transmitter program

#include <SPI.h>
#include "nRF24L01.h"

Nrf24l Mirf = Nrf24l(10, 9);
byte value;

void setup()
{
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"ABCDE");           //Set your own address (sender address) using 5 characters
  Mirf.payload = sizeof(value);
  Mirf.channel = 90;              //Set the channel used
  Mirf.config();
}

void loop()
{
  Mirf.setTADDR((byte *)"FGHIJ");           //Set the receiver address
  value = 255;                      //Send value 255
  Mirf.send(&value);                //Send instructions, send random number value
  Serial.print("Wait for sending.....");
  while (Mirf.isSending())//Until you send successfully, exit the loop
  delay(1);        
  Serial.print("Send success:");
  Serial.println(value);
  delay(1000);
}
