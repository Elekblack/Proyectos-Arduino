// ------
// Función que recibe tres cadenas de texto como parámetros y las muestra centradas horizontalmente en la pantalla OLED SSD1306 de 128x64.
// ------
// Autor: ElekBlack
// Licencia: MIT
// ------

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- Función para imprimir 3 líneas centradas ---
void mostrarTextoCentrado(const char* linea1, const char* linea2, const char* linea3) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  int16_t x1, y1;
  uint16_t w, h;

  // Línea 1
  display.getTextBounds(linea1, 0, 0, &x1, &y1, &w, &h);
  int xLinea1 = (SCREEN_WIDTH - w) / 2;
  display.setCursor(xLinea1, 10);
  display.println(linea1);

  // Línea 2
  display.getTextBounds(linea2, 0, 0, &x1, &y1, &w, &h);
  int xLinea2 = (SCREEN_WIDTH - w) / 2;
  display.setCursor(xLinea2, 30);
  display.println(linea2);

  // Línea 3
  display.getTextBounds(linea3, 0, 0, &x1, &y1, &w, &h);
  int xLinea3 = (SCREEN_WIDTH - w) / 2;
  display.setCursor(xLinea3, 50);
  display.println(linea3);

  display.display();
}

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("No se encontró la pantalla OLED");
    for (;;);
  }

  // Ejemplo de uso
  mostrarTextoCentrado("Hola", "esta es", "mi pantalla");
}

void loop() {
  // Aquí puedes volver a llamar a la función con otros textos cuantas veces quieras
}
