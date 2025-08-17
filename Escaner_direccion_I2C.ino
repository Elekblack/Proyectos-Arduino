// ------
// Proyecto: Escanea direcciones I2C y muestra los dispositivos encontrados en el monitor
// ------
// Autor: ElekBlack
// Licencia: MIT
// ------

#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\nEscaneando I2C...");
  byte count = 0;

  for (byte i = 1; i < 127; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Dispositivo encontrado en 0x");
      Serial.println(i, HEX);
      count++;
    }
    delay(10);
  }

  if (count == 0) Serial.println("No se encontró ningún dispositivo I2C.");
  else Serial.println("Escaneo completo.");
}

void loop() {}

