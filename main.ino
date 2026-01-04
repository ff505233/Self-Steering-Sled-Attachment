#include "MicroBlue.h"
#include "SoftwareSerial.h"


const int rXPin = 7;
const int tXPin = 8;
SoftwareSerial SSerial(rXPin, tXPin); 
MicroBlueManager manager(SSerial);

//motor pins
const int IN1 = 4;
const int IN2 = 5;
const int ENA = 6;

void setup() {
  Serial.begin(9600);
  SSerial.begin(9600); // initialize bluetooth
  

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

}

void loop() { 
  MicroBlueMessage msg = manager.read();

  if(msg.hasId() && msg.hasValue()) {
    Serial.println(msg.toString()); 
    //turn motor right
    if (msg.id == "b0") {
      if (msg.value == "1") {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(ENA, 200);
      }
      else if (msg.value == "0") {
        stopMotor();
      }
    }
    //turn motor left
    if (msg.id == "b1") {
      if (msg.value == "1") {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        analogWrite(ENA, 200);
      }
      else if (msg.value == "0") {
        stopMotor();
      }
    }
  }
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}
