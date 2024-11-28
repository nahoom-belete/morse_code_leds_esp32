  #include <Arduino.h>
  #include "FileReader.h"

  const int pins[3] = {25, 32, 33};
  const int blueLED = 2;

  int currentPin;
  int pinPos = 0;
  const int wordSeparation = 500;
  const int letterSeparation = 400;
  const int dot = 100;
  const int dash = 300;
  String message = "";
  char delimeter = '/';

void setup() {
  delay(1000);
  Serial.begin(115200);
  currentPin = 25;
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
        if(pinPos == 2) 
        {
            pinPos = 0;
        }
        else {
          pinPos = pinPos + 1;
        }
        currentPin = pins[pinPos];
        pinMode(currentPin, OUTPUT);
        delay(wordSeparation);
      } 
      else 
      {
        if(message[i] == '.')
        {
           digitalWrite(currentPin, HIGH);
           delay(dot);
           digitalWrite(currentPin, LOW);
           delay(dot);  
        }
        else if(message[i] == '-')
        {
           digitalWrite(currentPin, HIGH);
           delay(dash);
           digitalWrite(currentPin, LOW);
           delay(dash);  
        }
        else
        {
          digitalWrite(currentPin, HIGH);
          delay(letterSeparation);
          digitalWrite(currentPin, LOW);
          delay(letterSeparation);
        }  
      }
  }
  digitalWrite(blueLED, HIGH);
  delay(4500);
  digitalWrite(blueLED, LOW);
  pinPos = 0;
  currentPin = pins[pinPos];
  pinMode(currentPin, OUTPUT);
}
