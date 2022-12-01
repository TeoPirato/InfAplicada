// Pines de motor de tambor
const int motorPin1 = 8, motorPin2 = 9, motorPin3 = 10, motorPin4 = 11;

// Variable para fijar la velocidad del motor (el retraso entre cada secuencia)
//const int motorSpeed = 1200;  
const int motorSpeed = 10000;
// Número de pasos por vuelta completa
const int stepsPerRevolution = 512;
// Tabla de prendido de bobinas
//const int numSteps = 8;
//const int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

const int numSteps = 4;
const int lookup[numSteps] = { B1100, B0110, B0011, B1001 }; // dos fases

//const int numSteps = 4;
//const int lookup[4] = { B1000, B0100, B0010, B0001 }; // una fase

void setup() {  
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop() {
  for(int i = 0; i < stepsPerRevolution; i++)    
    anticlockwise();

  delay(1000);

  for(int i = 0; i < stepsPerRevolution; i++)    
    clockwise();

  delay(1000);
}

// Un paso contra las agujas del reloj
void anticlockwise() 
{
  for(int i = 0; i < numSteps; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

// Un paso en las agujas del reloj
void clockwise()
{
  for(int i = numSteps - 1; i >= 0; i--)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

// Función de secuencia de giro
void setOutput(int out) 
{
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}
