#include <Servo.h>

const int pinEncoder = 8, pinIR = 9, pinIR1 = 10, pinIR2 = 11, pinMotorTambor = 12, pinMotorCinta = 13;
const int deltaTime = 15;

const int encoderStepsPerRevolution = 20;
bool prevEncoderValue = true;
int encoderStepCount = 0;

int objectiveCompartiment = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(pinEncoder, INPUT);
  pinMode(pinIR, INPUT);
  pinMode(pinIR1, INPUT);
  pinMode(pinIR2, INPUT);
  pinMode(pinMotorTambor, OUTPUT);
  pinMode(pinMotorCinta, OUTPUT);

  digitalWrite(pinMotorCinta, HIGH);
}

void loop()
{  
  ReadingEventsHandler();  
  MotorMovement();
  
  delay(deltaTime);
}

bool enFranjaBlanca = false, reading = false;
void ReadingEventsHandler()
{
  if (FranjaBlanca() && !enFranjaBlanca)
    enFranjaBlanca = true;
  
  if (!FranjaBlanca() && enFranjaBlanca)  
  {    
    enFranjaBlanca = false;
    if(!reading) ReadBits(); 
    reading = !reading;   
  }
}

// Si todos los infrarrojos detectan blanco
bool FranjaBlanca()
{
  return !digitalRead(pinIR) && !digitalRead(pinIR1) && !digitalRead(pinIR2);
}

void ReadBits()
{   
  bool firstBit = !digitalRead(pinIR1);
  bool secondBit = !digitalRead(pinIR2);  
  objectiveCompartiment = firstBit * 2 + secondBit;
}

void MotorMovement()
{
  bool isInObjectiveCompartiment = CurrentCompartiment() == objectiveCompartiment;
  Serial.println(objectiveCompartiment);
  digitalWrite(pinMotorTambor, !isInObjectiveCompartiment);
}

int CurrentCompartiment()
{
  bool encoderValue = digitalRead(pinEncoder);
  if(!encoderValue && prevEncoderValue)
  {
    encoderStepCount++;
    if(encoderStepCount == encoderStepsPerRevolution) 
      encoderStepCount = 0;
  }
  prevEncoderValue = encoderValue;

  return encoderStepCount / 5; 
}
