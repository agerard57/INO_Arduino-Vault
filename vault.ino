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
byte rowPins[4] = {13, 12, 11, 10};
byte colPins[4] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

int numberAddress = 0;
int resetButton = 0;
int code = 1234;
int displayedNumber = 0;

int buzzerPin = 3;
int resetButtonPin = 4;

void input()
{
  tone(buzzerPin, 1760);
  delay(150);
  noTone(buzzerPin);
}

void error()
{
  for (int i = 0; i < 3; i++)
  {
    screenStatus("off");
    tone(buzzerPin, 700);
    delay(200);
    noTone(buzzerPin);
    screenStatus("on");
    delay(100);
  }
  clearScreen();
}

void correct()
{
  for (int i = 0; i < 2; i++)
  {
    screenStatus("off");
    tone(buzzerPin, 2300);
    delay(150);
    noTone(buzzerPin);
    screenStatus("on");
    delay(50);
  }
  clearScreen();
}

void clearScreen()
{
  displayedNumber = 0;
  screenStatus("off");
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
  // EEPROM.get(numberAddress, code);
}

void screenStatus(String status)
{
  if (status == "off")
  {
    matrix.clear();
    matrix.writeDisplay();
  }
  else if (status == "on")
  {
    matrix.print(displayedNumber);
    matrix.writeDisplay();
  }
}

void loop()
{
  char keyPressed = keypad.getKey();
  if (displayedNumber >= 1000)
  {
    if (displayedNumber == code)
      correct();
    else
      error();
  }
  if (keyPressed >= '0' && keyPressed <= '9')
  {

    displayedNumber = displayedNumber * 10 + (keyPressed - '0');
    screenStatus("on");
    input();
  }

  if (displayedNumber != 0 && keyPressed == 'C')
    error();

  resetButton = digitalRead(resetButtonPin);

  // If resetButton is hold down for 3 seconds, reset the code
  if (resetButton == 0)
  {
    delay(3000);
    resetButton = digitalRead(resetButtonPin);
    if (resetButton == 0)
    {
      clearScreen();
      code = 2345;
      EEPROM.put(numberAddress, code);
      Serial.println("Code reset to 1234");
    }
  }
}
