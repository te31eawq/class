
int led = 9;
char keyStr[10];
int keyStrlen = 0;
int pwm= 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    keyStrlen = Serial.readBytes(keyStr, sizeof(keyStr));
    keyStr[keyStrlen - 1] = '\0';
    atoi(keyStr);
    Serial.println(keyStrlen);
    Serial.println(keyStr);
    pwm = atoi(keyStr);
    analogWrite(led, pwm);
    Serial.println(5/256.0 * pwm);
  }

}

