#include <Servo.h>

const int pinIR = 10, pinServo = 9;
const int deltaTime = 15, timeBetweenReadings = 500;

Servo servo;

int objetivo;
const int posicionInicial = 0;

int currentBit = 0;
bool firstBit = false;
bool secondBit = false;

void setup()
{
  Serial.begin(9600);

  pinMode(pinIR, INPUT);
  pinMode(pinServo, OUTPUT);
  
  servo.attach(pinServo, 500, 2500);    
  setearObjetivo(0);
}

void loop()
{
  IRStuff();

  irAObjetivo();
}

bool reading = false;
int waitingTime = 0;
void IRStuff()
{
  if (!digitalRead(pinIR) && !reading)
  {
    reading = true;
  }

  if(reading)
  {
    if(currentBit < 2)
    {
      WaitToReadBit(); 

      return;
    }
    
    setearObjetivo(firstBit * 2 + secondBit);

    WaitToReset();
  }  
}

// Para que no empiece a leer ni bien termine
void WaitToReset()
{
  Serial.print("Tiempo de espera: ");
  Serial.println(waitingTime);
  waitingTime += deltaTime;
  if(waitingTime > timeBetweenReadings)
  {
    Serial.print("Objetivo seteado: ");
    Serial.println(objetivo); 
    waitingTime = 0;
    reading = false;
    currentBit = 0;
  }
}

void WaitToReadBit()
{
  Serial.print("Tiempo de espera: ");
  Serial.println(waitingTime);
  waitingTime += deltaTime;
  if(waitingTime > timeBetweenReadings)
  {
    waitingTime = 0;
    ReadingBit(!digitalRead(pinIR));      
  }  
}

void ReadingBit(bool readState)
{
  currentBit++;

  if (currentBit == 1) firstBit = readState;
  if (currentBit == 2) secondBit = readState;

  Serial.println((String)"Reading bit " + currentBit);
}

void irAObjetivo()
{
  servo.write(objetivo);
  delay(deltaTime);
}

void setearObjetivo(int compartimento)
{
  objetivo = posicionInicial + compartimento * 45;
}
