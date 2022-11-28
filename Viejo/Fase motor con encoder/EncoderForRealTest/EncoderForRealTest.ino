const int pinEncoder = 8, pinMotor = 9, pinButton = 10;
const int encoderStepsPerRevolution = 20;

bool prevEncoderValue = true;
int encoderStepCount = 0;
int objectiveCompartiment = 0;

bool pressedButton = false;

void setup() {
  Serial.begin(9600);

  
  pinMode(pinEncoder, INPUT_PULLUP);
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(pinMotor, OUTPUT);
}

void loop() {
  objectiveCompartiment += int(ButtonDown());
  if(objectiveCompartiment == 4) objectiveCompartiment = 0;
  
  analogWrite(pinMotor, 140);
  //MotorMovement();
  //delay(15);
}

bool ButtonDown()
{
  if(!digitalRead(pinButton) && !pressedButton)
  {
    pressedButton = true;
    return true;
  }
  else if(digitalRead(pinButton) && pressedButton)
    pressedButton = false;

  return false;
}

int CurrentCompartiment()
{
  bool encoderValue = !digitalRead(pinEncoder);
  if(!encoderValue && prevEncoderValue)
  {
    encoderStepCount++;
    if(encoderStepCount == encoderStepsPerRevolution) 
      encoderStepCount = 0;
  }
  prevEncoderValue = encoderValue;
  return encoderStepCount / 5; 
}

void MotorMovement()
{
  bool isInObjectiveCompartiment = CurrentCompartiment() == objectiveCompartiment;

  Serial.println(encoderStepCount);
  PrintState(!isInObjectiveCompartiment, int(encoderStepCount / 5));

  digitalWrite(pinMotor, !isInObjectiveCompartiment);
  
}

void PrintState(bool motorShouldBeMoving, int currentCompartiment)
{
  Serial.print("Objective compartiment:\t");
  Serial.print(objectiveCompartiment);
  Serial.print(", current compartiment:\t");
  Serial.print(currentCompartiment);  
  Serial.print(", motor should be moving:\t");
  if(motorShouldBeMoving) Serial.println("YES");
  else Serial.println("NO");
}
