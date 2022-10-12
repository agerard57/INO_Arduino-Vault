/* Memory Library https://docs.arduino.cc/learn/built-in-libraries/eeprom */
#include <EEPROM.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <Keypad.h>
Adafruit_7segment matrix = Adafruit_7segment();

char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[4] = {13, 12, 11, 10}; // connect to the row pinouts of the keypad
byte colPins[4] = {9, 8, 7, 6};     // connect to the column pinouts of the keypad

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

int numberAddress = 0; // Address that will store the number
int resetButton = 0;   // 0 == LOW
int code = 1234;
int displayedNumber = 0;

int buzzerPin = 3;
int resetButtonPin = 4;

/* https://www.youtube.com/watch?v=NA5MwhuHWLo :) */
void input()
{
  tone(buzzerPin, 1760);
  delay(150);
 noTone(buzzerPin);
}

void correct()
{
  tone(buzzerPin, 2300);
  delay(150);
  noTone(buzzerPin);
  tone(buzzerPin, 2300);
  delay(150);
  noTone(buzzerPin);
}

void error()
{
  tone(buzzerPin, 700);
  delay(200);
  noTone(buzzerPin);
  delay(100);

  tone(buzzerPin, 700);
  delay(200);
  noTone(buzzerPin);

  delay(100);
  tone(buzzerPin, 700);
  delay(200);
  noTone(buzzerPin);
}

void setup()
{
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
#endif

  matrix.begin(0x70);

  while (!Serial)
  {
    ;
  }

  pinMode(buzzerPin, OUTPUT);
  pinMode(resetButtonPin, INPUT_PULLUP);

  /* GET number from memory */
  //EEPROM.get(numberAddress, code);
}

void loop()
{
  char keyPressed = myKeypad.getKey();
  if (displayedNumber >= 1000)
  {


    if (displayedNumber == code)
    {
      correct();
    }
    else
    {
      error();
    }
   displayedNumber = 0;
        matrix.print("");
    matrix.writeDisplay();
  }
  if (keyPressed >= '0' && keyPressed <= '9')
    {

      displayedNumber = displayedNumber * 10 + (keyPressed - '0');
      Serial.println(displayedNumber);
    matrix.print(displayedNumber);
    matrix.writeDisplay();
    Serial.println(keyPressed);
    input();
  }

  if (displayedNumber != 0 && keyPressed == 'C')
  {
       displayedNumber = 0;
    matrix.print("");
    matrix.writeDisplay();
    error();
  }

  resetButton = digitalRead(resetButtonPin);

// If resetButton is hold down for 3 seconds, reset the code
  if (resetButton == 0)
  {
    delay(3000);
    resetButton = digitalRead(resetButtonPin);
    if (resetButton == 0)
    {
      displayedNumber = 0;
      matrix.print("");
      matrix.writeDisplay();
      code = 2345;
      EEPROM.put(numberAddress, code);
      Serial.println("Code reset to 1234");
    }
  }
}
