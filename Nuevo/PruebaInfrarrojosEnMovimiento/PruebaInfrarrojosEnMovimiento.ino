const int pinIR = 4, pinIR1 = 5, pinIR2 = 6, pinMotorCinta = 7;
const int deltaTime = 15;

void setup() {
  pinMode(pinIR, INPUT);
  pinMode(pinIR1, INPUT);
  pinMode(pinIR2, INPUT); 
  pinMode(pinMotorCinta, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print(GetReadObjectiveCompartiment());
  digitalWrite(pinMotorCinta, HIGH);  
  delay(deltaTime);
}

// Devuelve el compartimento objetivo según el lector de barras
int GetReadObjectiveCompartiment()
{   
  bool firstBit = !digitalRead(pinIR1);
  bool secondBit = !digitalRead(pinIR2);  

  // Convierte de binario a un número del 0 al 3
  return firstBit * 2 + secondBit;  
}
