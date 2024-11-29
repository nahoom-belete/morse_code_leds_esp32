#include <Arduino.h>
#include "FileReader.h"

// Array of LED output pins
const int pins[3] = {25, 32, 33};
const int blueLED = 2;// Debugging LED used to indicate end of message

// Initialization
int currentPin = 0;
int pinPos = 0;
String message = "";
char delimeter = '/';

// Delays
const int wordSeparation = 500;
const int letterSeparation = 400;
const int dot = 100;
const int dash = 300;

//Custom function declarations
void setPin();
void changePins();
void displayMessage(int d);
void reset(); 


//Entry point
void setup() {
  delay(1000);
  Serial.begin(115200);
  currentPin = pins[pinPos];
  pinMode(currentPin, OUTPUT);
  pinMode(blueLED, OUTPUT);

  FileReader file("/morse_code.txt");
  message = file.readFile();
}

void loop() {
  for(int i = 0; i < message.length(); i++) 
  {
    if(message[i] == delimeter) 
    {
      setPin();
      changePins();
    } 
    else 
    {
      switch(message[i])
      {
        case('.'):
           displayMessage(dot);
           break;
        case('-'):
          displayMessage(dash);
          break;
        default:
          displayMessage(letterSeparation);
          break;
      }
    }
  }
 reset();
}

//Custom functions
void setPin() 
{
  if(pinPos == 2) 
  {
      pinPos = 0;
  }
  else 
  {
    pinPos = pinPos + 1;
  }
}

void changePins() 
{
  currentPin = pins[pinPos];
  pinMode(currentPin, OUTPUT);
  delay(wordSeparation);
}

void displayMessage(int d) 
{
  digitalWrite(currentPin, HIGH);
  delay(d);
  digitalWrite(currentPin, LOW);
  delay(d);  
}

void reset() {
  digitalWrite(blueLED, HIGH);
  delay(4500);
  digitalWrite(blueLED, LOW);
  pinPos = 0;
  currentPin = pins[pinPos];
  pinMode(currentPin, OUTPUT);
}
