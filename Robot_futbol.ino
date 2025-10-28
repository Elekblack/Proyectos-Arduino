// ------
// Proyecto: Robot futbol a control remoto por bluetooth.
// ------
// Autor: ElekBlack
// Licencia: MIT
// ------

  int MA1 = 2;
  int MA2 = 4;
  int MB1 = 7;
  int MB2 = 8;
  char caja;

  void setup() {
    Serial.begin(9600);
    pinMode(MA1, OUTPUT);
    pinMode(MA2, OUTPUT);
    pinMode(MB1, OUTPUT);
    pinMode(MB2, OUTPUT);
  }
  void loop() {
    // habilitar adelante solo para calibrar
    // despues de calibrar deben comentarlo
    
    //adelante();

    if (Serial.available() > 0) {
      caja = Serial.read();
    }
    if(caja == 'F'){
      adelante();
    }
    if(caja=='B'){
      atras();
    }
    if(caja=='L'){
      izquierda();
    }
    if(caja== 'R'){
      derecha();
    }
    if(caja == 'S'){
      detener();
    }
  }

  void adelante() {
    digitalWrite(MA1, HIGH);
    digitalWrite(MA2, LOW);
    digitalWrite(MB1, HIGH);
    digitalWrite(MB2, LOW);
  }
  void atras() {
    digitalWrite(MA1, LOW);
    digitalWrite(MA2, HIGH);
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, HIGH);
  }
  void izquierda() {
    digitalWrite(MA1, LOW);
    digitalWrite(MA2, HIGH);
    digitalWrite(MB1, HIGH);
    digitalWrite(MB2, LOW);
  }
  void derecha() {
    digitalWrite(MA1, HIGH);
    digitalWrite(MA2, LOW);
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, HIGH);
  }
  void detener() {
    digitalWrite(MA1, LOW);
    digitalWrite(MA2, LOW);
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, LOW);
  }
