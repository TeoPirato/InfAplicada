// Pines de motor de tambor
const int motorPin1 = 8, motorPin2 = 9, motorPin3 = 10, motorPin4 = 11;

// Variable para fijar la velocidad del motor (el retraso entre cada secuencia)
const int motorSpeed = 1200;  
// Número de pasos por vuelta completa
const int stepsPerRevolution = 512;
// Tabla de prendido de bobinas
const int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

// Pines de infrarrojos y motor de la cinta
const int pinIR = 4, pinIR1 = 5, pinIR2 = 6, pinMotorCinta = 7;

// Tiempo de delay entre iteraciones en milisegundos
const int deltaTime = 15;

void setup()
{
  // Si se necesita depurar algo con Serial.print, se descomenta esto
  // Serial.begin(9600);

  // Preparaciones usando pinmode
  pinMode(pinIR, INPUT);
  pinMode(pinIR1, INPUT);
  pinMode(pinIR2, INPUT);  
  pinMode(pinMotorCinta, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop()
{
  if(ExitedFranjaBlanca())
    MotorMovement(GetReadObjectiveCompartiment()); 
  
  // La cinta siempre está prendida
  digitalWrite(pinMotorCinta, HIGH);
  
  delay(deltaTime);
}

// Es verdadero cuando en la anterior iteración hubo una franja blanca 
bool inFranjaBlanca = false;

// Devuelve verdaderlo cuando sale una franja blanca del codigo de barras
bool ExitedFranjaBlanca()
{
  // Detecta si entra una franja blanca al lector
  if (FranjaBlanca() && !inFranjaBlanca)
    inFranjaBlanca = true;

  // Detecta si sale una franja blanca del lector
  if (!FranjaBlanca() && inFranjaBlanca)  
  {    
    inFranjaBlanca = false;
    return true;
  }

  return false;
}

// Devuelve verdadero si todos los infrarrojos leen blanco
bool FranjaBlanca()
{
  return !digitalRead(pinIR) && !digitalRead(pinIR1) && !digitalRead(pinIR2);
}

// Devuelve el compartimento objetivo según el lector de barras
int GetReadObjectiveCompartiment()
{   
  bool firstBit = !digitalRead(pinIR1);
  bool secondBit = !digitalRead(pinIR2);  

  // Convierte de binario a un número del 0 al 3
  return firstBit * 2 + secondBit;  
}

int currentCompartiment = 0;

// Se mueve el tambor al compartimento objetivo
void MotorMovement(int objectiveCompartiment)
{
  // Compartimentos y dirección del movimiento del tambor
  int compartimentDelta = objectiveCompartiment - currentCompartiment;
  
  // Para minimizar movimiento, mover 3 es equivalente a mover 1 en la dirección contraria
  if(abs(compartimentDelta) == 3) compartimentDelta /= -3;

  // Mover el tambor
  if(compartimentDelta >= 0)
    for(int i = 0; i < stepsPerRevolution * compartimentDelta / 4; i++)
      clockwise();
  else
    for(int i = 0; i < stepsPerRevolution * -compartimentDelta / 4; i++)
      anticlockwise();

  // Actualizar el compartimento actual
  currentCompartiment = objectiveCompartiment;
}

// Un paso contra las agujas del reloj
void anticlockwise() 
{
  for(int i = 0; i < 8; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

// Un paso en las agujas del reloj
void clockwise()
{
  for(int i = 7; i >= 0; i--)
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
