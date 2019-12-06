# CS207-Final-Project
CS 207 Final Project - RGB Temperature Clock

What the project does:  
&nbsp;&nbsp;  This project is an RGB temperature clock that uses a wireless module to turn it on and off
  
Why is the project useful:  
&nbsp;&nbsp; The clock can be used everyday if you'd like with lots more modifications that can be added. It also showcases
&nbsp;&nbsp; many simple components such as button switch, wireless transmitting, RGB led strips, LCD screen, and a
&nbsp;&nbsp;  RealTimeClock module.
  
How users can get started with the project:  
&nbsp;&nbsp;  Components:    
&nbsp;&nbsp;&nbsp;&nbsp;   1. ARDUINO UNO board (x2)    
&nbsp;&nbsp;&nbsp;&nbsp;   2. Push button  
&nbsp;&nbsp;&nbsp;&nbsp;   3. Jumper wires (F-M wires recommended)  
&nbsp;&nbsp;&nbsp;&nbsp;   4. DS3231 RTC module (requires a CR2032 lithium battery)    
&nbsp;&nbsp;&nbsp;&nbsp;   5. LCD screen (20x4)  
&nbsp;&nbsp;&nbsp;&nbsp;   6. WS2812b RGB strip (x~60 leds)  
&nbsp;&nbsp;&nbsp;&nbsp;   7. nRF24L01 module (x2)  
&nbsp;&nbsp;&nbsp;&nbsp;   8. 220 ohm resistor (x1)  
&nbsp;&nbsp;&nbsp;&nbsp;   9. Barrel Jack 7.5v battery pack  
&nbsp;&nbsp;&nbsp;&nbsp;   10. Acrylic/Glass case  
&nbsp;&nbsp;  Libraries:  
&nbsp;&nbsp;&nbsp;&nbsp; FastLED, RTClib, Wire, LCD, LiquidCrystal_I2C, LiquidCrystal, SPI, nRF24L01, RF24

Usage:  
&nbsp;&nbsp; Upload transmitter code to arduino with the button
&nbsp;&nbsp; Upload receiver code to the other arduino
&nbsp;&nbsp; Wait for the nRF24L01 modules to connect (takes a few seconds)
&nbsp;&nbsp; Now you can turn the device on/off using the transmitter arduino with the button
&nbsp;&nbsp; enjoy
    
 Where users can get help with your project:  
&nbsp;&nbsp;   dylanyamaguchikuan@gmail.com & Kwonjah@gmail.com
   
 Who maintains and contributes to the project/Credits:  
&nbsp;&nbsp;    At the moment, no plans to maintain the project  
&nbsp;&nbsp;    Dylan.Y and Jahkwon.H contributed to creating this project  

 Link for those who want a visual presentation: https://www.youtube.com/watch?v=O7sx4c2UZBA  
 Circuit schematics:  
 Transmitter   
 ![Alt text](https://github.com/ImGizmoh/CS207-Final-Project/blob/master/TRANSMITTER.png)  
 ![Alt text](https://github.com/ImGizmoh/CS207-Final-Project/blob/master/TRANSMITTER.jpg)  
 Receiver  
 ![Alt text](https://github.com/ImGizmoh/CS207-Final-Project/blob/master/RECEIVER.png)  
 ![Alt text](https://github.com/ImGizmoh/CS207-Final-Project/blob/master/RECEIVER.jpg)  
 ![Alt text](https://github.com/ImGizmoh/CS207-Final-Project/blob/master/INSIDE.png) 
 
    
