/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/DigitalReadSerial
*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;
int ledPin = 13;
char ledState = 0;
int buttonStatePre = 0; 
int buttonCount = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  if(buttonState != buttonStatePre)
  {
    if(buttonState)
    {
      buttonCount++;
      ledState = !ledState;
      Serial.print("buttonCount : ");
      Serial.println(buttonCount);
      digitalWrite(ledPin,ledState);
    }
    buttonStatePre = buttonState;
  }
  if(Serial.available())
  {
    ledState = Serial.read(); 

    if(ledState == '0' || ledState == '1')
    {
      if(ledState == '1')
      {
        digitalWrite(ledPin,HIGH);
      }
      else if(ledState == '0')
      {
        digitalWrite(ledPin,LOW);
      }
      Serial.print("ledState : ");
      Serial.println(ledState);
    }
  }
}
