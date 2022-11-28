const int pinIR = 9, pinIR1 = 10, pinIR2 = 11;

void setup() {
  pinMode(pinIR, INPUT);
  pinMode(pinIR1, INPUT);
  pinMode(pinIR2, INPUT);

  Serial.begin(9600);
}

void loop() {
  Serial.print(analogRead(pinIR));
  Serial.print(analogRead(pinIR1));
  Serial.print(analogRead(pinIR2));
  Serial.println();
  delay(15);
}
