// entradas de las compuertas
int PIN_A = 2;
int PIN_B = 3;

// salida de las compuertas
int PIN_Y = 12;

// selección de entradas de las compuertas
int PIN_I0 = 4;
int PIN_I1 = 5;
int PIN_I2 = 6;
int PIN_I3 = 7;

// selección de salidas de las compuertas
int PIN_O0 = 8;
int PIN_O1 = 9;
int PIN_O2 = 10;
int PIN_O3 = 11;

// pin de debug
int PIN_DEBUG = 13;

// selección de compuerta a probar
int I_XOR0[] = {0, 0, 0, 0};
int I_XOR1[] = {0, 0, 0, 1};
int I_XOR2[] = {0, 0, 1, 0};
int I_XOR3[] = {0, 0, 1, 1};

int I_COMP0[] = {0, 1, 0, 0};
int I_COMP1[] = {0, 1, 0, 1};
int I_COMP2[] = {0, 1, 1, 0};
int I_COMP3[] = {0, 1, 1, 1};

int I_FFD0[] = {1, 0, 0, 0};
int I_FFD1[] = {1, 0, 0, 1};

// selección de salida de las compuertas
int O_XOR0[] = {0, 0, 0, 0};
int O_XOR1[] = {0, 0, 0, 1};
int O_XOR2[] = {0, 0, 1, 0};
int O_XOR3[] = {0, 0, 1, 1};

int O_COMP0[] = {0, 1, 0, 0};
int O_COMP1[] = {0, 1, 0, 1};
int O_COMP2[] = {0, 1, 1, 0};
int O_COMP3[] = {0, 1, 1, 1};

int O_FFD0_Q[] = {1, 0, 0, 0};
int O_FFD0_QN[] = {1, 0, 0, 1};
int O_FFD1_Q[] = {1, 0, 1, 0};
int O_FFD1_QN[] = {1, 0, 1, 1};

// variables
int entradaSeleccionada;
int salidaSeleccionada;

boolean DEBUG = false;

void setup() {
  // configurar pines
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_Y, INPUT);

  pinMode(PIN_I0, OUTPUT);
  pinMode(PIN_I1, OUTPUT);
  pinMode(PIN_I2, OUTPUT);
  pinMode(PIN_I3, OUTPUT);

  pinMode(PIN_O0, OUTPUT);
  pinMode(PIN_O1, OUTPUT);
  pinMode(PIN_O2, OUTPUT);
  pinMode(PIN_O3, OUTPUT);

  pinMode(PIN_DEBUG, INPUT);

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

  probarXOR(I_XOR0, O_XOR0);
  probarXOR(I_XOR1, O_XOR1);
  probarXOR(I_XOR2, O_XOR2);
  probarXOR(I_XOR3, O_XOR3);
}

boolean probarXOR(int seleccionEntrada[], int seleccionSalida[]) {
  Serial.println("Probando XOR: " + parseEntrada(seleccionEntrada));

  seleccionarEntrada(seleccionEntrada);
  seleccionarSalida(seleccionSalida);

  boolean resultado0 = probarEscenarioXOR(LOW, LOW);
  esperar();
  boolean resultado1 = probarEscenarioXOR(LOW, HIGH);
  esperar();
  boolean resultado2 = probarEscenarioXOR(HIGH, LOW);
  esperar();
  boolean resultado3 =  probarEscenarioXOR(HIGH, HIGH);
  esperar();

  if (resultado0 && resultado1 && resultado2 && resultado3) {
    Serial.println("XOR:" + parseEntrada(seleccionEntrada) + "= OK");
  } else {
    Serial.println("XOR:" + parseEntrada(seleccionEntrada) + "= NOK !!!!!!!!!!!!!!!!!!");
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

  probarCOMP(I_COMP0, O_COMP0);
  probarCOMP(I_COMP1, O_COMP1);
  probarCOMP(I_COMP2, O_COMP2);
  probarCOMP(I_COMP3, O_COMP3);
}

boolean probarCOMP(int seleccionEntrada[], int seleccionSalida[]) {
  Serial.println("Probando COMP: " + parseEntrada(seleccionEntrada));
  seleccionarEntrada(seleccionEntrada);
  seleccionarSalida(seleccionSalida);

  boolean resultado0 = probarEscenarioCOMP(LOW, LOW);
  boolean resultado1 = probarEscenarioCOMP(LOW, HIGH);
  boolean resultado2 = probarEscenarioCOMP(HIGH, LOW);
  boolean resultado3 =  probarEscenarioCOMP(HIGH, HIGH);

  if (resultado0 && resultado1 && resultado2 && resultado3) {
    Serial.println("COMP:" + parseEntrada(seleccionEntrada) + "= OK");
  } else {
    Serial.println("COMP:" + parseEntrada(seleccionEntrada) + "= NOK !!!!!!!!!!!!!!!!!!");
  }
}

boolean probarEscenarioCOMP(int a, int b) {
  boolean esperado;
  if (a != b) {
    esperado = HIGH;
  } else {
    esperado = LOW;
  }

  ejecutarPrueba(a, b);
  return verificarSalida(esperado);
}

void probarFFDs() {
  Serial.println("*** Probando FFDs ***");

  probarFFD(I_FFD0, O_FFD0_Q, O_FFD0_QN);
  probarFFD(I_FFD1, O_FFD1_Q, O_FFD1_QN);
}

boolean probarFFD(int seleccionEntrada[], int seleccionSalidaQ[], int seleccionSalidaQN[]) {
  Serial.println("Probando FFD: " + parseEntrada(seleccionEntrada));
  seleccionarEntrada(seleccionEntrada);

  boolean resultado0 = probarEscenarioFFD(LOW, LOW, HIGH, seleccionSalidaQ, seleccionSalidaQN);
  boolean resultado1 = probarEscenarioFFD(HIGH, HIGH, LOW, seleccionSalidaQ, seleccionSalidaQN);

  if (resultado0 && resultado1) {
    Serial.println("FFD:" + parseEntrada(seleccionEntrada) + "= OK");
  } else {
    Serial.println("FFD:" + parseEntrada(seleccionEntrada) + "= NOK !!!!!!!!!!!!!!!!!!");

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

  seleccionarSalida(seleccionSalidaQN);
  exito &= verificarSalida(qnEsperado);

  return exito;
}

void seleccionarEntrada(int entrada[]) {
  digitalWrite(PIN_I0, entrada[3]);
  digitalWrite(PIN_I1, entrada[2]);
  digitalWrite(PIN_I2, entrada[1]);
  digitalWrite(PIN_I3, entrada[0]);
}

void seleccionarSalida(int salida[]) {
  digitalWrite(PIN_O0, salida[3]);
  digitalWrite(PIN_O1, salida[2]);
  digitalWrite(PIN_O2, salida[1]);
  digitalWrite(PIN_O3, salida[0]);
}

void ejecutarPrueba(int a, int b) {
  String i_a = parseNivel(a);
  String i_b = parseNivel(b);
  Serial.println("A=" + i_a + ", B=" + i_b);

  digitalWrite(PIN_A, a);
  digitalWrite(PIN_B, b);

  esperar();
}

void ejecutarPrueba(int d) {
  String i_d = parseNivel(d);
  Serial.println("D=" + i_d);

  digitalWrite(PIN_A, d);
  reloj();

  esperar();
}

void reloj() {
  digitalWrite(PIN_B, LOW);
  delay(500);
  digitalWrite(PIN_B, HIGH);
}

boolean verificarSalida(int esperado) {
  Serial.println("esperado=" + parseNivel(esperado));
  int y = digitalRead(PIN_Y);
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
    int signal = digitalRead(PIN_DEBUG);
    while (signal == LOW) {
      delay(1000);
      signal = digitalRead(PIN_DEBUG);
    }
    Serial.println("sigo");
  }
}

