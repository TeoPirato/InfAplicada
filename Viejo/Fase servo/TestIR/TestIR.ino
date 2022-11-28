const int pinIR = 10;
const int deltaTime = 15, timeBetweenReadings = 500;

void setup()
{
  Serial.begin(9600);

  pinMode(pinIR, INPUT);
}

int currentBit = 0;
bool firstBit = false;
bool secondBit = false;

void loop()
{
  IRStuff();

  delay(deltaTime);
}

void IRStuff()
{
  if (!digitalRead(pinIR))
  {
    while (currentBit < 2)
    {
      delay(timeBetweenReadings);
      ReadingBit(!digitalRead(pinIR));
    }

    currentBit = 0;
    Serial.println(firstBit * 2 + secondBit);

    delay(2000);
  }
}

void ReadingBit(bool readState)
{
  currentBit++;

  if (currentBit == 1) firstBit = readState;
  if (currentBit == 2) secondBit = readState;

  Serial.println((String)"Reading bit " + currentBit);
}
