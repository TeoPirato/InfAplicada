#include <Stepper.h>

// Motor PaP: Cantidad de pasos por revolución y por compartimento, y velocidad en RPM
const int stepsPerRevolution = 96;
const int stepsPerCompartiment = stepsPerRevolution / 4;
const int speedMotorTambor = 60;

// Prepara la librería del stepper, se asignan los pasos por revolución y pines de control
Stepper motorTambor(stepsPerRevolution, 8, 9, 10, 11);

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

  // Establecimiento de la velocidad del motor del tambor
  motorTambor.setSpeed(speedMotorTambor);  
}

void loop()
{
  ReadingEventsHandler();  
  
  // La cinta siempre está prendida
  digitalWrite(pinMotorCinta, HIGH);
  
  delay(deltaTime);
}

// Es verdadero cuando en la anterior iteración hubo una franja blanca 
bool inFranjaBlanca = false;

// Lee el valor del código de barras después de la franja blanca
void ReadingEventsHandler()
{
  // Detecta si entra una franja blanca al lector
  if (FranjaBlanca() && !inFranjaBlanca)
    inFranjaBlanca = true;

  // Detecta si sale una franja blanca del lector
  if (!FranjaBlanca() && inFranjaBlanca)  
  {    
    inFranjaBlanca = false;

    // Se usan los valores de los infrarrojos después de una franja blanca    
    MotorMovement(GetReadObjectiveCompartiment());
    
    // Se puede poner un delay acá si hay ruido en los infrarrojos,
    // para que no empieze a leer de nuevo justo después
  }
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
  motorTambor.step(stepsPerCompartiment * compartimentDelta);

  // Actualizar el compartimento actual
  currentCompartiment = objectiveCompartiment;
}
