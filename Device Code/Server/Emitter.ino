//Transmitter program

#include <SPI.h>
#include "nRF24L01.h"

Nrf24l Mirf = Nrf24l(10, 9);                //Set CE, CSN pins
byte value = 255;                           //Set send value 255

void setup()
{
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();                              //Initialize radio
  Mirf.setRADDR((byte *)"ABCDE");           //Set sender address
  Mirf.payload = sizeof(value);
  Mirf.channel = 90;                        //Set the channel used
  Mirf.config();
}

void loop()
{
  transmit();
}

void transmit()
{
  Mirf.setTADDR((byte *)"FGHIJ");           //Set the receiver address                     
  Mirf.send(&value);                        //Send value
  Serial.print("Wait for sending.....");
  while (Mirf.isSending())                  //Until send success, exit the loop
  delay(1);        
  Serial.print("Send success:");
  Serial.println(value);
  delay(1000);
}