// ------
// Proyecto: Tacho de basura automático con sensor ultrasonico
// ------
// Autor: ElekBlack
// Licencia: MIT
// ------

#include <Servo.h>  // Incluye la librería Servo

// Pines del sensor de ultrasonido
const int trigPin = 7;
const int echoPin = 6;

// Pines para led
const int ledVerdePin = 8;
const int ledRojoPin = 9;

// Umbral de distancia en cm
const int distanciaUmbral = 20;

Servo servoMotor;    // Crea un objeto de tipo Servo

void setup() {
  // Configura los pines del sensor de ultrasonido
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configura los pines de los led
  pinMode(ledVerdePin, OUTPUT);
  pinMode(ledRojoPin, OUTPUT);

  // Configura el servomotor en el pin 5
  servoMotor.attach(5);
  
  // Inicia el servomotor en 0 grados
  servoMotor.write(90);

  //Inica los led
  digitalWrite(ledVerdePin, LOW);
   digitalWrite(ledRojoPin, HIGH);
}

void loop() {
  // Mide la distancia con el sensor de ultrasonido
  long distancia = medirDistancia();

  // Si la distancia es menor que el umbral, mover a 90°
  if (distancia > 0 && distancia < distanciaUmbral) {
    servoMotor.write(0);  // Mueve el servomotor a 90 grados
    digitalWrite(ledVerdePin, HIGH);
    digitalWrite(ledRojoPin, LOW);
    delay(5000);           // Espera 5 segundos
    servoMotor.write(90);   // Vuelve a 0 grados
    digitalWrite(ledVerdePin, LOW);
    digitalWrite(ledRojoPin, HIGH);
  }

  delay(500);  // Pequeña pausa antes de medir de nuevo
}

// Función para medir la distancia con el sensor de ultrasonido
long medirDistancia() {
  // Enviar un pulso ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Medir el tiempo del eco
  long duracion = pulseIn(echoPin, HIGH);

  // Convertir el tiempo en distancia (en cm)
  long distancia = duracion * 0.034 / 2;

  return distancia;
}
