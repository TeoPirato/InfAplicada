#include <Servo.h>

Servo myservo;

int pos = 0; 

void setup()
{
  myservo.attach(6); 
  myservo.write(90);
  
}

void loop()
{
//  myservo.write(360);
//  delay(10);
//  myservo.write(90);
//  delay(80);
  myservo.write(360);
  delay(595);
  myservo.write(90);
  delay(1000);
//  for (pos = 0; pos <= 180; pos += 1) { 
//    myservo.write(pos);              
//    delay(100);                      
//  }
//  for (pos = 180; pos >= 0; pos -= 1) { 
//    myservo.write(pos);            
//    delay(100);                      
//  }
}
