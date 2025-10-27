// I2C Scanner - Escanea direcciones I2C y las muestra por Serial
// Funciona con la librería Wire (incluida en Arduino IDE)

#include <Wire.h>

void setup() {
  Wire.begin();               // Para Arduino Uno/Nano: usa A4 (SDA) y A5 (SCL)
  Serial.begin(115200);      // Monitor serial a 115200 bps
  while (!Serial) {}         // Espera a que Serial esté listo (útil en Leonardo/Zero)
  Serial.println("\nI2C Scanner iniciado");
}

void loop() {
  Serial.println("Escaneando bus I2C...");
  int devicesFound = 0;

  for (uint8_t address = 1; address < 127; ++address) { // 0x01 .. 0x7E
    Wire.beginTransmission(address);
    uint8_t error = Wire.endTransmission();

    if (error == 0) {
      // Dispositivo ACKed en esta dirección
      Serial.print("-> Dispositivo encontrado en dirección 0x");
      if (address < 16) Serial.print("0"); // formateo hex de 2 dígitos
      Serial.print(address, HEX);
      Serial.print("   (");
      Serial.print(address); // decimal
      Serial.println(")");
      devicesFound++;
      delay(10); // pequeño retardo para bus estable
    } else if (error == 4) {
      // Error desconocido en el bus
      Serial.print("!! Error en la comunicación con dirección 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
    // si error == 2 (NACK), no hay dispositivo en esa dirección
  }

  if (devicesFound == 0) {
    Serial.println("No se encontraron dispositivos I2C.");
  } else {
    Serial.print("Escaneo completado. Dispositivos encontrados: ");
    Serial.println(devicesFound);
  }

  Serial.println("--------------------------------\n");
  delay(3000); // espera antes del siguiente escaneo
}
