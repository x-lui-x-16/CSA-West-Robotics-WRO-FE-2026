// Pines del L298N para el motor A
const int ENA = 5;   // Pin PWM para velocidad
const int IN1 = 4;   // Dirección
const int IN2 = 3;   // Dirección

int vel = 50;                  // valor de 0-100 para la potencia
int frvel = (vel * 255) / 100; // conversión a 0-255

void setup() {
  // Configurar pines como salida
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Hacer que el motor avance
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Velocidad del motor
  analogWrite(ENA, frvel);
}

void loop() {
  // El motor sigue avanzando
}