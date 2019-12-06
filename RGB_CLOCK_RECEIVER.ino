//LIBRARIES
#include <FastLED.h> // WS2812b
#include "RTClib.h" // DS3231
#include <Wire.h> // LCD DISPLAY
#include <LCD.h> // LCD DISPLAY
#include <LiquidCrystal_I2C.h> // LCD DISPLAY
#include <LiquidCrystal.h> // LCD DISPLAY
#include <SPI.h> //nRF24L01
#include <nRF24L01.h> //nRF24L01
#include <RF24.h> //nRF24L01

//PIN/CONST DEFINITIONS
#define buttonPin     2
#define backlightPin  3
#define ledPin        4
#define ledNum        60
#define hueLow        10
#define hueMed        25
#define hueHigh       50

//VARIABLES/ARRAY
int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;
float temp;
CRGB leds[ledNum];
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const byte address[6] = "00001";

//COMPONENT SETUPS
RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
RF24 radio(9, 10);

//MAIN SETUP
void setup()
{
  //SERIAL MONITOR (BEGIN @ 9600 BAUD)
  Serial.begin(9600);

  //PINMODE SETUPS (BUTTON/LED)
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  //LCD DISPLAY SETUP (20x4 @ HIGH)
  lcd.begin(20, 4);
  lcd.setBacklightPin(backlightPin, POSITIVE);
  lcd.setBacklight(HIGH);

  //WS2812b RGB STRIP SETUP
  FastLED.addLeds<WS2812, ledPin, GRB> (leds, ledNum);

  //DS3231 RTC (CLOCK) SETUP (BEGIN)
  if (! rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  //DS3231 RTC (CLOCK) SETUP (IF POWER LOST)
  if (rtc.lostPower())
  {
    Serial.println("RTC lost power, lets set the time!");
    //MANUAL TIME SETUP
    rtc.adjust(DateTime(2019, 12, 4, 14, 37, 10));

  }

  //nRF24L01 SETUP (LISTEN FOR TRANSMITTER)
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

//MAIN LOOP
void loop()
{
  //BUTTON READ
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonPin);

  //TEMP/DATE/TIME READ FROM RTC CLOCK
  temp = rtc.getTemperature();
  DateTime now = rtc.now();

  //IF RADIO AVAILABLE
  if (radio.available())
  {
    //FOR READING THE BUTTON STATES FROM TRANSMITTER
    char text[32] = "";
    radio.read(&text, sizeof(text));
    radio.read(&buttonState, sizeof(buttonState));

    //COMPARE buttonState TO lastButtonState
    if (buttonState != lastButtonState)
    {
      if (buttonState == HIGH)
      {
        buttonPushCounter++;
      }
      else
      {
        Serial.println("off");
      }
      // Delay a little bit to avoid bouncing
      delay(50);
    }
    // save the current state as the last state, for next time through the loop
    lastButtonState = buttonState;

    //TURNS ON EVERYTHING BY CHECKING FOR MODULO OF buttonPushCounter
    if (buttonPushCounter % 2 == 0)
    {
      //TURN ON LCD
      lcd.setBacklight(HIGH);

      //IF TEMP LESS/EQUAL 23, RGB -> BLUE
      if (temp <= 25)
      {
        for (int i = 0; i < 60; i++)
        {
          temp = rtc.getTemperature();
          leds[i] = CRGB(0, 0, hueHigh);
          FastLED.show();
        }
        lcd.setCursor(2, 4);
        lcd.print("Status: FREEZING" );
      }

      //IF TEMP LESS/EQUAL 23, RGB -> CYAN
      if ((temp > 25) && (temp <= 26.5))
      {
        for (int i = 0; i < 60; i++)
        {
          temp = rtc.getTemperature();
          leds[i] = CRGB(0, hueLow, hueLow);
          FastLED.show();
        }
        lcd.setCursor(0, 4);
        lcd.print("Status: COLD!!!!" );
      }

      //IF TEMP BETWEEN 23 AND 25, RGB -> GREEN
      if ((temp > 26.5) && (temp <= 27.5))
      {
        for (int i = 0; i < 60; i++)
        {
          temp = rtc.getTemperature();
          leds[i] = CRGB(0, hueHigh, 0);
          FastLED.show();
        }
        lcd.setCursor(0, 4);
        lcd.print("Status: PERFECT!");
      }

      //IF TEMP HIGHER/EQUAL 25, RGB -> ORANGE
      if ((temp > 27.5) && (temp <= 28.5))
      {
        for (int i = 0; i < 60; i++)
        {
          temp = rtc.getTemperature();
          leds[i] = CRGB(hueHigh, hueLow, 0);
          FastLED.show();
        }
        lcd.setCursor(0, 4);
        lcd.print("Status: WARM!!!!");
      }

      //IF TEMP HIGHER/EQUAL 25, RGB -> RED
      if (temp > 28.5)
      {
        for (int i = 0; i < 60; i++)
        {
          temp = rtc.getTemperature();
          leds[i] = CRGB(hueHigh, 0, 0);
          FastLED.show();
        }
        lcd.setCursor(0, 4);
        lcd.print("Status: HOT!!!!!");
      }

      //DATE(MONTH, DAY, YEAR) LCD DISPLAY
      lcd.setCursor(0, 0);
      lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
      lcd.print(" ");
      lcd.print(now.month(), DEC);
      lcd.print("/");
      lcd.print(now.day(), DEC);
      lcd.print("/");
      lcd.print(now.year(), DEC);

      //TIME(HOUR, MIN, SEC) LCD DISPLAY
      lcd.setCursor(0, 1); //column & row
      lcd.print("Time: ");
      lcd.print(now.hour(), DEC);
      lcd.print(':');
      lcd.print(now.minute(), DEC);
      lcd.print(':');
      lcd.print(now.second(), DEC);

      //TEMP(TEMP) LCD DISPLAY
      lcd.setCursor(0, 2);
      lcd.print("Temp: ");
      lcd.print(rtc.getTemperature());
      lcd.print((char)223);
      lcd.print("C");
    }
    else
    {
      //ELSE, TURON OFF RGB AND LCD DISPLAY
      for (int i = 0; i < 60; i++)
      {
        temp = rtc.getTemperature();
        leds[i] = CRGB(0, 0, 0);
        FastLED.show();
      }
      lcd.setBacklight(LOW);
      lcd.clear();
    }
  }
  delay(50);
}
