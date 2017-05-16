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

// selección de salidas de las compuertas
int PIN_NO_O0 = 10;
int PIN_NO_O1 = 11;
int PIN_NO_O2 = 12;
int PIN_NO_O3 = 13;

// selección de salida de las compuertas
int O_XOR0[] = {0, 0, 0, 0};
int O_XOR1[] = {0, 0, 0, 1};
int O_XOR2[] = {0, 0, 1, 0};
int O_XOR3[] = {0, 0, 1, 1};

int O_COMP_MAYOR[] = {0, 1, 0, 0};
int O_COMP_IGUAL[] = {0, 1, 0, 1};
int O_COMP_MENOR[] = {0, 1, 1, 0};

int O_FFD0_Q[] = {1, 0, 0, 0};
int O_FFD0_QN[] = {1, 0, 0, 1};
int O_FFD1_Q[] = {1, 0, 1, 0};
int O_FFD1_QN[] = {1, 0, 1, 1};

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

  Serial.begin(9600);
  Serial.println("--- Iniciando pruebas ---");

  probarXORs();
  probarCOMPs();
  probarFFDs();
}


void loop() {

}

void probarXORs() {
  Serial.println("*** Probando XORs ***");

  probarXOR(O_XOR0);
  probarXOR(O_XOR1);
  probarXOR(O_XOR2);
  probarXOR(O_XOR3);
}

boolean probarXOR(int seleccionSalida[]) {
  Serial.println("Probando XOR: " + parseEntrada(seleccionSalida));

  seleccionarSalida(seleccionSalida);

  boolean resultado0 = probarEscenarioXOR(LOW, LOW);
  boolean resultado1 = probarEscenarioXOR(LOW, HIGH);
  boolean resultado2 = probarEscenarioXOR(HIGH, LOW);
  boolean resultado3 =  probarEscenarioXOR(HIGH, HIGH);

  if (resultado0 && resultado1 && resultado2 && resultado3) {
    Serial.println("XOR:" + parseEntrada(seleccionSalida) + "= OK");
  } else {
    Serial.println("XOR:" + parseEntrada(seleccionSalida) + "= NOK !!!!!!!!!!!!!!!!!!");
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
  Serial.println("*** Probando COMPs ***");

  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      Serial.println("Probando A=" + String(i) + ", B=" + String(j));

      digitalWrite(PIN_NO_A0, bitRead(i, 0));
      digitalWrite(PIN_NO_A1, bitRead(i, 1));
      digitalWrite(PIN_NO_A2, bitRead(i, 2));
      digitalWrite(PIN_NO_A3, bitRead(i, 3));

      digitalWrite(PIN_NO_B0, bitRead(j, 0));
      digitalWrite(PIN_NO_B1, bitRead(j, 1));
      digitalWrite(PIN_NO_B2, bitRead(j, 2));
      digitalWrite(PIN_NO_B3, bitRead(j, 3));



      boolean pruebasExitosas = true;

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
        Serial.println("NOK: esperado=" + String(esperado) + ", salida=" + String(salida));
        pruebasExitosas &= false;
        esperar();
      } else {
        Serial.println("OK");
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
        Serial.println("NOK: esperado=" + String(esperado) + ", salida=" + String(salida));
        pruebasExitosas &= false;
        esperar();
      } else {
        Serial.println("OK");
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
        Serial.println("NOK: esperado=" + String(esperado) + ", salida=" + String(salida));
        pruebasExitosas &= false;
        esperar();
      } else {
        Serial.println("OK");
      }
    }
  }
}

void probarFFDs() {
  Serial.println("*** Probando FFDs ***");

  probarFFD(O_FFD0_Q, O_FFD0_QN);
  probarFFD(O_FFD1_Q, O_FFD1_QN);
}

boolean probarFFD(int seleccionSalidaQ[], int seleccionSalidaQN[]) {
  Serial.println("Probando FFD: " + parseEntrada(seleccionSalidaQ));

  boolean resultado0 = probarEscenarioFFD(LOW, LOW, HIGH, seleccionSalidaQ, seleccionSalidaQN);
  boolean resultado1 = probarEscenarioFFD(HIGH, HIGH, LOW, seleccionSalidaQ, seleccionSalidaQN);

  if (resultado0 && resultado1) {
    Serial.println("FFD:" + parseEntrada(seleccionSalidaQ) + "= OK");
  } else {
    Serial.println("FFD:" + parseEntrada(seleccionSalidaQ) + "= NOK !!!!!!!!!!!!!!!!!!");

  }

}

boolean probarEscenarioFFD(int d, int qInicial, int qnInicial, int seleccionSalidaQ[], int seleccionSalidaQN[]) {
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
  Serial.println("A=" + i_a + ", B=" + i_b);

  digitalWrite(PIN_NO_A0, a);
  digitalWrite(PIN_NO_B0, b);

  esperar();
}

void ejecutarPrueba(int d) {
  String i_d = parseNivel(d);
  Serial.println("D=" + i_d);

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
  Serial.println("esperado=" + parseNivel(esperado));
  int y = digitalRead(PIN_NO_Y);
  y = negar(y);

  Serial.println("salida=" + parseNivel(y));
  if (y == esperado) {
    Serial.println("OK");
    return true;
  } else {
    Serial.println("NOK");
    return false;
  }
}

String parseEntrada(int entrada[]) {
  return String(entrada[0]) + String(entrada[1]) + String(entrada[2]) + String(entrada[3]);
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
    Serial.println("espero");
    delay(5000);
    int signal = digitalRead(PIN_NO_DEBUG);
    while (signal == LOW) {
      delay(1000);
      signal = digitalRead(PIN_NO_DEBUG);
    }
    Serial.println("sigo");
  }
}

