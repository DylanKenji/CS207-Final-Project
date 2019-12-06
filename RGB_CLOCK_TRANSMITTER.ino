//LIBRARIES
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//PIN/VARIABLES
const byte address[6] = "00001";
const int  buttonPin = 2; 
int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

//nRF24L01 SETUP
RF24 radio(9, 10); // CE, CSN

//MAIN SETUP
void setup() 
{
  //PINMODE SETUP (BUTTON)
  pinMode(buttonPin, INPUT);

  //nRF24L01 SETUP (BROADCASTER FOR RECEIVER)
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

//MAIN LOOP
void loop()
{
  //SERIAL MONITOR (BEGIN @ 9600 BAUD)
  Serial.begin(9600);

  //READ buttonState FROM buttonPin
  buttonState = digitalRead(buttonPin);

  //BUTTON ON/OFF TOGGLE
  if (buttonState != lastButtonState) 
  {
    if (buttonState == HIGH) 
    {
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } 
    else 
    {
      Serial.println("off");
    }
    delay(50);
  }
  lastButtonState = buttonState;
  
  //SEND DATA TO RECEIVER
  radio.write(&buttonState, sizeof(buttonState));
  delay(50);
}
