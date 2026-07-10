#include <Servo.h>

Servo miServo;

const int servoPin = 2;   // Pin donde está conectado el servo

void setup() {
  Serial.begin(115200);

  // Espera a que se abra el Monitor Serial
  while (!Serial);

  miServo.attach(servoPin);
  miServo.write(155);   // Posición Ajustable para Probar rango del Servo
}

void loop() {
}