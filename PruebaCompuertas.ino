boolean DEBUG = false;

// pin de debug
int PIN_NO_DEBUG = A5;

// salida de las compuertas
int PIN_NO_Y = A0;

// entradas de las compuertas
int PIN_NO_A0 = 2;
int PIN_NO_A1 = 3;
int PIN_NO_A2 = 4;
int PIN_NO_A3 = 5;

int PIN_NO_B0 = 6;
int PIN_NO_B1 = 7;
int PIN_NO_B2 = 8;
int PIN_NO_B3 = 9;

int PIN_NO_COMP_MENOR = A1;
int PIN_NO_COMP_IGUAL = A2;
int PIN_NO_COMP_MAYOR = A3;

// selección de salidas de las compuertas
int PIN_NO_O0 = 10;
int PIN_NO_O1 = 11;
int PIN_NO_O2 = 12;
int PIN_NO_O3 = 13;

// selección de salida de las compuertas
int O_XOR0[] = { 0, 0, 0, 0 };
int O_XOR1[] = { 0, 0, 0, 1 };
int O_XOR2[] = { 0, 0, 1, 0 };
int O_XOR3[] = { 0, 0, 1, 1 };

int O_COMP_MAYOR[] = { 0, 1, 0, 0 };
int O_COMP_IGUAL[] = { 0, 1, 0, 1 };
int O_COMP_MENOR[] = { 0, 1, 1, 0 };

int O_FFD0_Q[] = { 1, 0, 0, 0 };
int O_FFD0_QN[] = { 1, 0, 0, 1 };
int O_FFD1_Q[] = { 1, 0, 1, 0 };
int O_FFD1_QN[] = { 1, 0, 1, 1 };

// variables
int salidaSeleccionada;

void setup() {
  // configurar pines
  pinMode(PIN_NO_A0, OUTPUT);
  pinMode(PIN_NO_A1, OUTPUT);
  pinMode(PIN_NO_A2, OUTPUT);
  pinMode(PIN_NO_A3, OUTPUT);

  pinMode(PIN_NO_B0, OUTPUT);
  pinMode(PIN_NO_B1, OUTPUT);
  pinMode(PIN_NO_B2, OUTPUT);
  pinMode(PIN_NO_B3, OUTPUT);

  pinMode(PIN_NO_O0, OUTPUT);
  pinMode(PIN_NO_O1, OUTPUT);
  pinMode(PIN_NO_O2, OUTPUT);
  pinMode(PIN_NO_O3, OUTPUT);

  pinMode(PIN_NO_DEBUG, INPUT);

  pinMode(PIN_NO_Y, INPUT);
  pinMode(PIN_NO_COMP_MENOR, OUTPUT);
  pinMode(PIN_NO_COMP_IGUAL, OUTPUT);
  pinMode(PIN_NO_COMP_MAYOR, OUTPUT);

  Serial.begin(9600);
//  establishContact();
}

void loop() {
  char opcion;
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    opcion = input.charAt(0);
    if (opcion == '0') {
      probarXORs();
    } else if (opcion == '1') {
      probarCOMPs();
    } else if (opcion == '2') {
      probarFFDs();
    }
  }
}

void probarXORs() {
  printlnHandShake("*** Probando XORs ***");
  boolean pruebasExitosas = true;
  pruebasExitosas &= probarXOR(O_XOR0);
  pruebasExitosas &= probarXOR(O_XOR1);
  pruebasExitosas &= probarXOR(O_XOR2);
  pruebasExitosas &= probarXOR(O_XOR3);

  if (pruebasExitosas) {
    printlnHandShake("$XORSOK");
  } else {
    printlnHandShake("$XORSNOK");
  }
}

boolean probarXOR(int seleccionSalida[]) {
  printlnHandShake("Probando XOR: " + parseEntrada(seleccionSalida));

  seleccionarSalida(seleccionSalida);

  boolean pruebasExitosas = true;

  pruebasExitosas &= probarEscenarioXOR(LOW, LOW);
  pruebasExitosas &= probarEscenarioXOR(LOW, HIGH);
  pruebasExitosas &= probarEscenarioXOR(HIGH, LOW);
  pruebasExitosas &= probarEscenarioXOR(HIGH, HIGH);

  if (pruebasExitosas) {
    printlnHandShake("XOR=" + parseEntrada(seleccionSalida) + "=OK");
  } else {
    printlnHandShake(
      "XOR:" + parseEntrada(seleccionSalida)
      + "= NOK !!!!!!!!!!!!!!!!!!");
  }
}

boolean probarEscenarioXOR(int a, int b) {
  boolean esperado;
  if (a != b) {
    esperado = HIGH;
  } else {
    esperado = LOW;
  }

  ejecutarPrueba(a, b);
  return verificarSalida(esperado);
}

void probarCOMPs() {
  printlnHandShake("*** Probando COMPs ***");

  boolean pruebasExitosas = true;

  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      printlnHandShake("Probando A=" + String(i) + ", B=" + String(j));

      digitalWrite(PIN_NO_A0, bitRead(i, 0));
      digitalWrite(PIN_NO_A1, bitRead(i, 1));
      digitalWrite(PIN_NO_A2, bitRead(i, 2));
      digitalWrite(PIN_NO_A3, bitRead(i, 3));

      digitalWrite(PIN_NO_B0, bitRead(j, 0));
      digitalWrite(PIN_NO_B1, bitRead(j, 1));
      digitalWrite(PIN_NO_B2, bitRead(j, 2));
      digitalWrite(PIN_NO_B3, bitRead(j, 3));

      digitalWrite(PIN_NO_COMP_MENOR, LOW);
      digitalWrite(PIN_NO_COMP_IGUAL, HIGH);
      digitalWrite(PIN_NO_COMP_MAYOR, LOW);

      seleccionarSalida(O_COMP_MAYOR);
      int esperado;
      int salida = negar(digitalRead(PIN_NO_Y));
      if (i > j) {
        esperado = HIGH;
      } else {
        esperado = LOW;
      }

      Serial.print(String(i) + ">" + String(j) + ": ");
      if (salida != esperado) {
        printlnHandShake(
          "NOK: esperado=" + String(esperado) + ", salida="
          + String(salida));
        pruebasExitosas &= false;
        esperar();
      } else {
        printlnHandShake("OK");
      }

      seleccionarSalida(O_COMP_IGUAL);
      salida = negar(digitalRead(PIN_NO_Y));
      if (i == j) {
        esperado = HIGH;
      } else {
        esperado = LOW;
      }

      Serial.print(String(i) + "=" + String(j) + ": ");
      if (salida != esperado) {
        printlnHandShake(
          "NOK: esperado=" + String(esperado) + ", salida="
          + String(salida));
        pruebasExitosas &= false;
        esperar();
      } else {
        printlnHandShake("OK");
      }

      seleccionarSalida(O_COMP_MENOR);
      salida = negar(digitalRead(PIN_NO_Y));
      if (i < j) {
        esperado = HIGH;
      } else {
        esperado = LOW;
      }

      Serial.print(String(i) + "<" + String(j) + ": ");
      if (salida != esperado) {
        printlnHandShake(
          "NOK: esperado=" + String(esperado) + ", salida="
          + String(salida));
        pruebasExitosas &= false;
        esperar();
      } else {
        printlnHandShake("OK");
      }
    }
  }
  if (pruebasExitosas) {
    printlnHandShake("Pruebas de COMP exitosas");
    printlnHandShake("$COMPOK");
  } else {
    printlnHandShake("$COMPNOK");
  }
}

void probarFFDs() {
  printlnHandShake("*** Probando FFDs ***");

  boolean resultado0 = probarFFD(O_FFD0_Q, O_FFD0_QN);
  boolean resultado1 =  probarFFD(O_FFD1_Q, O_FFD1_QN);

  if (resultado0 && resultado1) {
    printlnHandShake("$FFSOK");
  } else {
    printlnHandShake("$FFSNOK");
  }
}

boolean probarFFD(int seleccionSalidaQ[], int seleccionSalidaQN[]) {
  printlnHandShake("Probando FFD: " + parseEntrada(seleccionSalidaQ));

  boolean resultado0 = probarEscenarioFFD(LOW, LOW, HIGH, seleccionSalidaQ,
                                          seleccionSalidaQN);
  boolean resultado1 = probarEscenarioFFD(HIGH, HIGH, LOW, seleccionSalidaQ,
                                          seleccionSalidaQN);

  if (resultado0 && resultado1) {
    printlnHandShake("FFD:" + parseEntrada(seleccionSalidaQ) + "= OK");
  } else {
    printlnHandShake(
      "FFD:" + parseEntrada(seleccionSalidaQ)
      + "= NOK !!!!!!!!!!!!!!!!!!");

  }

}

boolean probarEscenarioFFD(int d, int qInicial, int qnInicial,
                           int seleccionSalidaQ[], int seleccionSalidaQN[]) {
  boolean qEsperado;
  boolean qnEsperado;
  boolean exito = true;

  qEsperado = d;
  qnEsperado = negar(d);

  seleccionarSalida(seleccionSalidaQ);
  ejecutarPrueba(d);
  exito &= verificarSalida(qEsperado);

  esperar();

  seleccionarSalida(seleccionSalidaQN);
  exito &= verificarSalida(qnEsperado);

  return exito;
}

void seleccionarSalida(int salida[]) {
  digitalWrite(PIN_NO_O0, salida[3]);
  digitalWrite(PIN_NO_O1, salida[2]);
  digitalWrite(PIN_NO_O2, salida[1]);
  digitalWrite(PIN_NO_O3, salida[0]);
}

void ejecutarPrueba(int a, int b) {
  String i_a = parseNivel(a);
  String i_b = parseNivel(b);
  printlnHandShake("A=" + i_a + ", B=" + i_b);

  digitalWrite(PIN_NO_A0, a);
  digitalWrite(PIN_NO_B0, b);

  esperar();
}

void ejecutarPrueba(int d) {
  String i_d = parseNivel(d);
  printlnHandShake("D=" + i_d);

  digitalWrite(PIN_NO_A0, d);
  reloj();

  esperar();
}

void reloj() {
  digitalWrite(PIN_NO_B0, LOW);
  delay(100);
  digitalWrite(PIN_NO_B0, HIGH);
}

boolean verificarSalida(int esperado) {
  printlnHandShake("esperado=" + parseNivel(esperado));
  int y = digitalRead(PIN_NO_Y);
  y = negar(y);

  printlnHandShake("salida=" + parseNivel(y));
  if (y == esperado) {
    printlnHandShake("OK");
    return true;
  } else {
    printlnHandShake("NOK");
    return false;
  }
}

String parseEntrada(int entrada[]) {
  return String(entrada[0]) + String(entrada[1]) + String(entrada[2])
         + String(entrada[3]);
}

String parseNivel(int nivel) {
  if (nivel == LOW) {
    return "LOW";
  }
  if (nivel == HIGH) {
    return "HIGH";
  }
}

int negar(int nivel) {
  if (nivel == HIGH) {
    return LOW;
  } else {
    return HIGH;
  }
}

int esperar() {
  if (DEBUG) {
    printlnHandShake("espero");
    delay(5000);
    int signal = digitalRead(PIN_NO_DEBUG);
    while (signal == LOW) {
      delay(1000);
      signal = digitalRead(PIN_NO_DEBUG);
    }
    printlnHandShake("sigo");
  }
}

//void establishContact() {
//  while (Serial.available() <= 0) {
//    Serial.println("%");
//    delay(300);
//  }
//}

void printlnHandShake(String mensaje) {
  char input = '0';
  if (Serial.available() > 0) {
    input = Serial.read();
  }

  while (input != '&') {
    if (Serial.available() > 0) {
      input = Serial.read();
    }
  }

  Serial.println(mensaje);
}

