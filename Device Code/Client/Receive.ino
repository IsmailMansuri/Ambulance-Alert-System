//Receiver program
#include <SPI.h>
#include "nRF24L01.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

int led_pin=2;

Nrf24l Mirf = Nrf24l(10, 9);                             //Set CE, CSN pins
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);  //Setup 16x2 LCD
byte value;

void setup()
{
  pinMode(led_pin,OUTPUT);

  lcd.init();
  
  
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();                                          //Initialize radio
  Mirf.setRADDR((byte *)"FGHIJ");                       //Set receiver address
  Mirf.payload = sizeof(value);
  Mirf.channel = 90;                                    //Set the used channel
  Mirf.config();
  Serial.println("Listening...");                       //Start listening to received data
}

void loop()
{
  receive();
}

void receive()
{
  if (Mirf.dataReady()){                                //If received value is 255 display to LCD, else clear the LCD
    Mirf.getData(&value);
    Serial.print("Got data: ");
    Serial.println(value);
    if (value == 255){
      display(); 
    }
  }
  else{
    clearLCD();
  }

}

void display()                                         //Display message on LCD display
{
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

void clearLCD()
{
  lcd.clear();
  lcd.noBacklight();
  value=0;
}