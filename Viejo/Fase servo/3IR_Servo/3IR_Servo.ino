#include <Servo.h>

const int pinServo = 9, pinIR = 10, pinIR1 = 11, pinIR2 = 12;
const int deltaTime = 15, timeBetweenReadings = 500;

Servo servo;

const int posicionInicial = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(pinIR, INPUT);
  pinMode(pinIR1, INPUT);
  pinMode(pinIR2, INPUT);
  
  pinMode(pinServo, OUTPUT);
  
  servo.attach(pinServo, 500, 2500);  
  setearObjetivo(0);
}

void loop()
{
  if (PrimerFranjaBlanca()) ReadBits();
  delay(deltaTime);
}


bool PrimerFranjaBlanca()
{
  return !digitalRead(pinIR);
}

void ReadBits()
{  
  bool firstBit = !digitalRead(pinIR1);
  bool secondBit = !digitalRead(pinIR2);

  int numeroDeCompartimento = firstBit * 2 + secondBit;
  setearObjetivo(numeroDeCompartimento);
  Serial.print("Objetivo seteado: ");
  Serial.println(numeroDeCompartimento); 
  
  delay(timeBetweenReadings);
}

void setearObjetivo(int compartimento)
{
  int objetivoEnGrados = posicionInicial + compartimento * 45;
  servo.write(objetivoEnGrados);
}
