// Biomed Device Client Side Code 
// by: Ismail Mansuri
// Made for Arduino Micro


#include <Arduino.h>
#include <SPI.h>
#include <RH_NRF24.h>
#include <LiquidCrystal.h>

// initialize the LCD library with the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Radio driver
RH_NRF24 nrf24;

void setup() 
{
// Initialize LCD and the LCD's number of columns and rows:
  lcd.begin(16, 2);

  Serial.begin(9600);
  
  if (!nrf24.init())
    Serial.println("init failed");
  // Default after init is 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    
}


void loop()
{
  Serial.println("Sending to nrf24_server");
  // Send a message to nrf24_server
  uint8_t data[] = "Test message to server";
  nrf24.send(data, sizeof(data));
  
  nrf24.waitPacketSent();
  // Wait for a reply
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (nrf24.waitAvailableTimeout(500))
  { 
    // Should be a reply message for us now   
    if (nrf24.recv(buf, &len))
    {
      Serial.print("got reply: ");
      Serial.println((char*)buf);
      lcd.print((char*)buf);
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is nrf24_server running?");
  }
  delay(400);
}