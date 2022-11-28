#include <Servo.h>

const int pinServo = 9, pinIR = 10, pinIR1 = 11, pinIR2 = 12;
const int deltaTime = 15, timeBetweenReadings = 500, deployTime = 5000;

Servo servo;
const int posicionInicial = 0;
int numeroDeCompartimento = 0;

unsigned long detectedTime = 0;
bool chargeBuffer = false;

void setup()
{
  Serial.begin(9600);

  pinMode(pinIR, INPUT);
  pinMode(pinIR1, INPUT);
  pinMode(pinIR2, INPUT);
  
  pinMode(pinServo, OUTPUT);
  
  servo.attach(pinServo, 500, 2500);  
  setearObjetivo();
}

void loop()
{
  if (PrimerFranjaBlanca()) ReadBits();
  if (chargeBuffer && !Deploying())
  {    
    chargeBuffer = false;
    setearObjetivo();
  }
  
  delay(deltaTime);
}

bool Deploying()
{
  bool someDetectionMade = detectedTime != 0;
  bool deployed = millis() - detectedTime >= deployTime;
  return !deployed && someDetectionMade;
}

bool PrimerFranjaBlanca()
{
  return !digitalRead(pinIR);
}

void ReadBits()
{
  bool firstBit = !digitalRead(pinIR1);
  bool secondBit = !digitalRead(pinIR2);
  numeroDeCompartimento = firstBit * 2 + secondBit;

  if(!Deploying())
    setearObjetivo();
  else
  {    
    chargeBuffer = true;
    Serial.print("Objetivo BUFFEREADO: ");
    Serial.println(numeroDeCompartimento); 
  }
  
  detectedTime = millis();
  // Para que no tome otra línea blanca del mismo QR como inicio de otro QR 
  delay(timeBetweenReadings);
}

void setearObjetivo()
{
  Serial.print("Objetivo seteado: ");
  Serial.println(numeroDeCompartimento); 
  int objetivoEnGrados = posicionInicial + numeroDeCompartimento * 45;
  servo.write(objetivoEnGrados);
}
