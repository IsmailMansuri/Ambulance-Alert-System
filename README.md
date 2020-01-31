# Ambulance Alert
This device allows ambulances or other emergency vehicles to communicate with traffic ahead of them, allowing the traffic more time to exit the emergency vehicle's path, awarding quicker arrival times for the emergency vehicle.

# Motivation
Our group noticed that tracking technologies used by ambulances dated back to the 1980's, and we wanted to improve upon that and somehow allow ambulances an easier journey to get to their patients.

# Build Status
Working Prototype

# Code Style
Code Style: Standard

# Code Example

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

# Built With
   - Arduino
   - Arduino C
   - Keywish RF-Nano
   - I2C Serial Display Module

# Features
Our project features two radios: one transmitting the message (for the emergency vehicle) and one receiving the message (for the other vehicles on the road). The message is a simple delcaration of the incoming emergency vehicle, flashing on and off the screen to attract the drivers' attention.
