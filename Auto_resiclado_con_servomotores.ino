#include <Servo.h>

// Definición de servomotores
Servo servoIzquierdo; // Servo para tracción izquierda
Servo servoDerecho;   // Servo para tracción derecha
Servo servoDireccion; // Servo para dirección

// Pines de conexión
const int pinServoIzquierdo = 8;
const int pinServoDerecho = 9;
const int pinServoDireccion = 10;
const int pinLucesDelanteras = 13;
const int pinLucesTraseras = 12;

// Variables para la lectura de comandos
char comando;

// Configuración inicial
void setup() {
  // Configurar comunicación serie para el módulo Bluetooth
  Serial.begin(9600);

  // Configuración de pines de luces
  pinMode(pinLucesDelanteras, OUTPUT);
  pinMode(pinLucesTraseras, OUTPUT);

  // Asociar los pines a los servos
  servoIzquierdo.attach(pinServoIzquierdo);
  servoDerecho.attach(pinServoDerecho);
  servoDireccion.attach(pinServoDireccion);

  // Posicionar el servo de dirección al centro
  servoDireccion.write(90); 

  // Detener los servos de tracción
  detenerMotores();
}

// Bucle principal
void loop() {
  // Leer comando desde el módulo Bluetooth
  if (Serial.available()>0) {
    comando = Serial.read();
    Serial.println(comando);
    switch (comando) {
    case 'F': // Avanzar
      servoDireccion.write(90);
      moverAdelante();
      break;
    case 'B': // Retroceder
      servoDireccion.write(90);
      moverAtras();
      break;
    case 'L': // Girar izquierda
      servoDireccion.write(115);
      moverAdelante();
      break;
    case 'R': // Girar derecha
      servoDireccion.write(65);
      moverAdelante();
      break;
    case 'S': // Detener
      detenerMotores();
      servoDireccion.write(90);
      break;
    case '1': // Luces Delanteras encendidas
      digitalWrite(pinLucesDelanteras, HIGH);
      break;
    case '2': // Luces Delanteras apagadas
      digitalWrite(pinLucesDelanteras, LOW);
      break;
    case '3': //
      break;
    case '4': //
      break;
    default:
      // Comando no reconocido
      detenerMotores();
      servoDireccion.write(90);
      break;
    }
  }
}

// Función para mover el robot hacia adelante
void moverAdelante() {
  servoIzquierdo.write(180); // Giro hacia adelante
  servoDerecho.write(0);     // Giro hacia adelante
  digitalWrite(pinLucesTraseras, LOW);
}

// Función para mover el robot hacia atrás
void moverAtras() {
  servoIzquierdo.write(0);   // Giro hacia atrás
  servoDerecho.write(180);   // Giro hacia atrás
  digitalWrite(pinLucesTraseras, HIGH);
}

// Función para detener los motores
void detenerMotores() {
  servoIzquierdo.write(90); // Parar servo izquierdo
  servoDerecho.write(90);   // Parar servo derecho
  digitalWrite(pinLucesTraseras, LOW);
}
