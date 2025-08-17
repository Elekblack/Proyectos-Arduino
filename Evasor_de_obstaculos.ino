// ------
// Proyecto: Robot evador de obstáculos con servomotor y sensor ultrasónico
// ------
// Autor: ElekBlack
// Licencia: MIT
// ------

#include <Servo.h>
#include <NewPing.h>

// Definición de pines
const int pinTrig = 9;         // Pin de disparo (trigger) del sensor ultrasónico
const int pinEcho = 10;        // Pin de eco del sensor ultrasónico
const int pinServo = 5;        // Pin del servomotor
const int motorA1 = 4;         // Pin de dirección del motor A
const int motorA2 = 2;         // Pin de dirección del motor A
const int motorB1 = 8;         // Pin de dirección del motor B
const int motorB2 = 7;         // Pin de dirección del motor B
const int pinVelocidadA = 3;  // Pin PWM para velocidad del motor A
const int pinVelocidadB = 6;  // Pin PWM para velocidad del motor B

// Definición de constantes
const int distanciaSeguridad = 30; // Distancia mínima de seguridad en cm
const int anguloIzquierda = 180;     // Ángulo del servo hacia la izquierda
const int anguloDerecha = 0;     // Ángulo del servo hacia la derecha
const int anguloCentro = 90;       // Ángulo del servo al frente
const int velocidad = 150;         // Velocidad del motor (0-255)

// Configuración del sensor ultrasónico
NewPing sensorUltrasonico(pinTrig, pinEcho, 200); // Rango máximo de 200 cm
Servo servoMotor;

void setup() {
  Serial.begin(9600);

  // Configuración de pines de motores
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(pinVelocidadA, OUTPUT);
  pinMode(pinVelocidadB, OUTPUT);

  // Inicializar el servomotor
  servoMotor.attach(pinServo);
  servoMotor.write(anguloCentro); // Colocar el servo al frente

  // Iniciar movimiento
  avanzar();
}

void loop() {
  int distanciaFrontal = medirDistancia(); // Medir la distancia al frente

  if (distanciaFrontal < distanciaSeguridad) {
    detener(); // Detener si hay un obstáculo cerca

    // Medir distancias a izquierda y derecha
    int distanciaIzquierda = medirDistanciaLado(anguloIzquierda);
    int distanciaDerecha = medirDistanciaLado(anguloDerecha);

    // Decidir hacia qué lado girar
    if (distanciaIzquierda > distanciaDerecha) {
      girarIzquierda();
    } else {
      girarDerecha();
    }

    avanzar(); // Continuar después de girar
  }
}

// Función para avanzar
void avanzar() {
  analogWrite(pinVelocidadA, velocidad);
  analogWrite(pinVelocidadB, velocidad);
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

// Función para detener
void detener() {
  analogWrite(pinVelocidadA, 0);
  analogWrite(pinVelocidadB, 0);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}

// Función para girar a la izquierda
void girarIzquierda() {
  analogWrite(pinVelocidadA, velocidad);
  analogWrite(pinVelocidadB, velocidad);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  delay(500); // Ajusta este valor para un giro adecuado
}

// Función para girar a la derecha
void girarDerecha() {
  analogWrite(pinVelocidadA, velocidad);
  analogWrite(pinVelocidadB, velocidad);
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  delay(500); // Ajusta este valor para un giro adecuado
}

// Función para medir la distancia al frente
int medirDistancia() {
  delay(50); // Espera para asegurar estabilidad en la lectura
  return sensorUltrasonico.ping_cm();
}

// Función para medir la distancia en una dirección específica
int medirDistanciaLado(int angulo) {
  servoMotor.write(angulo);     // Mover el servomotor hacia el ángulo deseado
  delay(500);                   // Espera para estabilizar el sensor
  int distancia = medirDistancia(); // Medir la distancia
  servoMotor.write(anguloCentro);   // Retornar el servomotor al centro
  delay(500);                   // Espera para asegurar estabilidad en el centro
  return distancia;
}
