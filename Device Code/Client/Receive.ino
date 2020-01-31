//Receiver program
#include <SPI.h>
#include "nRF24L01.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

int led_pin=2;

Nrf24l Mirf = Nrf24l(10, 9);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
byte value;

void setup()
{
  pinMode(led_pin,OUTPUT);

  lcd.init();
  
  
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

    if (value == 255){
       lcd.backlight();
       lcd.setCursor(3, 0); 
       lcd.print("Ambulance  "); 
       lcd.setCursor(4, 1); 
       lcd.print("Inbound");
       delay(1500);
       lcd.clear();
       lcd.setCursor(3, 0); 
       lcd.print("Pull Over"); 
       delay(1500);
    }
  }
  else{
      lcd.clear();
      lcd.noBacklight();
      value=0;
  }
  
}
