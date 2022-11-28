const int pinEncoder = 8;

bool prevEncoderValue = true;
int encoderCount = 0;

const int contadasPorVuelta = 20;

void setup() {
  Serial.begin(9600);
  pinMode(pinEncoder, INPUT_PULLUP);
}

void loop() {
  bool encoderValue = digitalRead(pinEncoder);
  if(!encoderValue && prevEncoderValue)
  {
    encoderCount++;
    if(encoderCount == contadasPorVuelta) encoderCount = 0;
  }
  Serial.println(encoderCount);
  prevEncoderValue = encoderValue;  
  delay(15);
}
