/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/
unsigned long x= 0;
int y = 0;
int sensorValuePre = 0;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(13,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A1);
  Serial.println(sensorValue);
  // print out the value you read:
  delay(1);  // delay in between reads for stability
  x = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(13,x);
  // if(abs((x-y) > 5) && x != y)
  // {
  //   Serial.println(5/255.0*x);
  //   y = x;
  // }
  
}
