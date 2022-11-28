#include <Servo.h>

const int pinEncoder = 8, pinIR = 9, pinIR1 = 10, pinIR2 = 11, pinMotorTambor = 12, pinMotorCinta = 13;
const int deltaTime = 15, deployTime = 5000;

const int encoderStepsPerRevolution = 20;
bool prevEncoderValue = true;
int encoderStepCount = 0;

int readCompartiment = 0, objectiveCompartiment = 0;

unsigned long detectedTime = 0;
bool chargeBuffer = false;

void setup()
{
  Serial.begin(9600);

  pinMode(pinEncoder, INPUT);
  pinMode(pinIR, INPUT);
  pinMode(pinIR1, INPUT);
  pinMode(pinIR2, INPUT);
  pinMode(pinMotorTambor, OUTPUT);
  pinMode(pinMotorCinta, OUTPUT);
}

void loop()
{  
  ReadingEventsHandler();  
  LoadBufferWhenStoppedDeploying();
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

void LoadBufferWhenStoppedDeploying()
{
  if (chargeBuffer && !Deploying())
  {    
    chargeBuffer = false;
    objectiveCompartiment = readCompartiment;
  }
}

// Si todos los infrarrojos detectan blanco
bool FranjaBlanca()
{
  return !digitalRead(pinIR) && !digitalRead(pinIR1) && !digitalRead(pinIR2);
}

bool Deploying()
{
  return !TimeHasPassedSinceDetectionMade(deployTime);
}

bool TimeHasPassedSinceDetectionMade(unsigned long timeAmount)
{
  bool detectionTimeHasNotBeenSet = detectedTime == 0;
  if(detectionTimeHasNotBeenSet) return true;
  
  bool timeHasPassed = millis() - detectedTime >= timeAmount;
  return timeHasPassed;
}

void ReadBits()
{   
  bool firstBit = !digitalRead(pinIR1);
  bool secondBit = !digitalRead(pinIR2);
  readCompartiment = firstBit * 2 + secondBit;

  if(!Deploying())
    objectiveCompartiment = readCompartiment;
  else
  {    
    chargeBuffer = true;
    Serial.print("Objetivo BUFFEREADO: ");
    Serial.println(readCompartiment); 
  }
  
  detectedTime = millis(); 
}

void MotorMovement()
{
  bool isInObjectiveCompartiment = CurrentCompartiment() == objectiveCompartiment;
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
