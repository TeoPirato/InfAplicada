const int pinIR = 10, pinIR1 = 11, pinIR2 = 12;
const int deltaTime = 15, timeBetweenReadings = 500;

void setup()
{
  Serial.begin(9600);

  pinMode(pinIR, INPUT);
  pinMode(pinIR1, INPUT);
  pinMode(pinIR2, INPUT);
}

bool firstBit = false;
bool secondBit = false;

void loop()
{
  IRStuff();

  delay(deltaTime);
}

bool PrimerFranjaBlanca()
{
  return !digitalRead(pinIR);
}

void IRStuff()
{
  if (PrimerFranjaBlanca())
  {
    firstBit = !digitalRead(pinIR1);
    secondBit = !digitalRead(pinIR2);
    
    Serial.println(firstBit * 2 + secondBit);

    delay(2000);
  }
}
