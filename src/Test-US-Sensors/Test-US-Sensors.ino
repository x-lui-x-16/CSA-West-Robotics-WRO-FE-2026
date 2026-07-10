// Definición de Pines de Sensores US (HC-SR04)
#define TRIG1 8 // Sensor delantero
#define ECHO1 9
#define TRIG2 10 // Sensor Izquierdo
#define ECHO2 11
#define TRIG3 12 // Sensor Derecho
#define ECHO3 13

const unsigned long printInterval = 1000; // Intervalo de 5 segundos
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600); // Iniciar la comunicación Serial

  // Configuración de pines de HC-SR04
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(TRIG3, OUTPUT);
  pinMode(ECHO3, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Verificar si han pasado 5 segundos
  if (currentMillis - previousMillis >= printInterval) {
    previousMillis = currentMillis;
    
    // Obtener los valores de los sensores ultrasónicos y de color
    int distanceFront = measureDistance(TRIG1, ECHO1);
    int distanceLeft = measureDistance(TRIG2, ECHO2);
    int distanceRight = measureDistance(TRIG3, ECHO3);
    
    // Mostrar los valores en el Serial
    Serial.print("Distancia delantera: "); Serial.print(distanceFront); Serial.println(" cm");
    Serial.print("Distancia izquierda: "); Serial.print(distanceLeft); Serial.println(" cm");
    Serial.print("Distancia derecha: "); Serial.print(distanceRight); Serial.println(" cm");
    Serial.println("----------------------------");
  }
}

// Función para medir la distancia con los sensores ultrasónicos
int measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}
