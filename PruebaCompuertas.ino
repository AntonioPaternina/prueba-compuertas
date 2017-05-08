// entradas de las compuertas
int PIN_A = 2;
int PIN_B = 3;

// salida de las compuertas
int PIN_Y = 4;

// selección de entradas de las compuertas
int PIN_I0 = 5;
int PIN_I1 = 6;
int PIN_I2 = 7;
int PIN_I3 = 8;

// selección de salidas de las compuertas
int PIN_O0 = 9;
int PIN_O1 = 10;
int PIN_O2 = 11;
int PIN_O3 = 12;

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

  Serial.begin(9600);
  Serial.println("--- Iniciando pruebas ---");

  probarXORs();
  probarCOMPs();
  probarFFDs();
}


void loop() {

}

void probarXORs() {
  Serial.println("Probando XORs");

  probarXOR(I_XOR0, O_XOR0);
  probarXOR(I_XOR1, O_XOR1);
  probarXOR(I_XOR2, O_XOR2);
  probarXOR(I_XOR3, O_XOR3);
}

boolean probarXOR(int seleccionEntrada[], int seleccionSalida[]) {
  Serial.println("Probando XOR: " + parseEntrada(seleccionEntrada));
  boolean resultado0 = probarEscenarioXOR(LOW, LOW, seleccionEntrada, seleccionSalida);
  boolean resultado1 = probarEscenarioXOR(LOW, HIGH, seleccionEntrada, seleccionSalida);
  boolean resultado2 = probarEscenarioXOR(HIGH, LOW, seleccionEntrada, seleccionSalida);
  boolean resultado3 =  probarEscenarioXOR(HIGH, HIGH, seleccionEntrada, seleccionSalida);

  boolean pruebasExitosas = (resultado0 == resultado1 == resultado2 == resultado3 == true);

  if (pruebasExitosas) {
    Serial.println("XOR:" + parseEntrada(seleccionEntrada) + "= OK");
  }

}

boolean probarEscenarioXOR(int a, int b, int seleccionEntrada[], int seleccionSalida[]) {
  boolean esperado;
  if (a != b) {
    esperado = HIGH;
  } else {
    esperado = LOW;
  }

  ejecutarPrueba(a, b, seleccionEntrada, seleccionSalida);
  verificarSalida(esperado);
}

void probarCOMPs() {
  Serial.println("Probando XORs");

  probarXOR(I_COMP0, O_COMP0);
  probarXOR(I_COMP1, O_COMP1);
  probarXOR(I_COMP2, O_COMP2);
  probarXOR(I_COMP3, O_COMP3);
}

boolean probarCOMP(int seleccionEntrada[], int seleccionSalida[]) {
  Serial.println("Probando COMP: " + parseEntrada(seleccionEntrada));
  boolean resultado0 = probarEscenarioCOMP(LOW, LOW, seleccionEntrada, seleccionSalida);
  boolean resultado1 = probarEscenarioCOMP(LOW, HIGH, seleccionEntrada, seleccionSalida);
  boolean resultado2 = probarEscenarioCOMP(HIGH, LOW, seleccionEntrada, seleccionSalida);
  boolean resultado3 =  probarEscenarioCOMP(HIGH, HIGH, seleccionEntrada, seleccionSalida);

  boolean pruebasExitosas = (resultado0 == resultado1 == resultado2 == resultado3 == true);

  if (pruebasExitosas) {
    Serial.println("XOR:" + parseEntrada(seleccionEntrada) + "= OK");
  }

}

boolean probarEscenarioCOMP(int a, int b, int seleccionEntrada[], int seleccionSalida[]) {
  boolean esperado;
  if (a != b) {
    esperado = HIGH;
  } else {
    esperado = LOW;
  }

  ejecutarPrueba(a, b, seleccionEntrada, seleccionSalida);
  verificarSalida(esperado);
}

void probarFFDs() {
  Serial.println("Probando XORs");

  probarFFD(I_COMP0, O_FFD0_Q, O_FFD0_QN);
  probarFFD(I_COMP1, O_FFD1_Q, O_FFD1_QN);
}

boolean probarFFD(int seleccionEntrada[], int seleccionSalidaQ[], int seleccionSalidaQN[]) {
  Serial.println("Probando COMP: " + parseEntrada(seleccionEntrada));

  boolean resultado0 = probarEscenarioFFD(LOW, HIGH, LOW, HIGH, seleccionEntrada, seleccionSalidaQ, seleccionSalidaQN);
  boolean resultado1 = probarEscenarioFFD(HIGH, HIGH, LOW, HIGH, seleccionEntrada, seleccionSalidaQ, seleccionSalidaQN);
  boolean resultado2 = probarEscenarioFFD(LOW, LOW, HIGH, LOW, seleccionEntrada, seleccionSalidaQ, seleccionSalidaQN);
  boolean resultado3 =  probarEscenarioFFD(HIGH, LOW, HIGH, HIGH, seleccionEntrada, seleccionSalidaQ, seleccionSalidaQN);
  boolean resultado4 =  probarEscenarioFFD(LOW, HIGH, HIGH, LOW, seleccionEntrada, seleccionSalidaQ, seleccionSalidaQN);

  boolean pruebasExitosas = (resultado0 == resultado1 == resultado2 == resultado3 == true);

  if (pruebasExitosas) {
    Serial.println("XOR:" + parseEntrada(seleccionEntrada) + "= OK");
  }

}

boolean probarEscenarioFFD(int d, int reloj, int qInicial, int qnInicial, int seleccionEntrada[], int seleccionSalidaQ[], int seleccionSalidaQN[]) {
  boolean qEsperado;
  boolean qnEsperado;
  if (reloj == LOW) {
    qEsperado = qInicial;
    qnEsperado = qnInicial;
  } else if (reloj == HIGH) {
    qEsperado = d;
    qnEsperado = negar(qEsperado);
  }

  ejecutarPrueba(d, reloj, seleccionEntrada, seleccionSalidaQ);
  verificarSalida(qEsperado);

  seleccionarSalida(seleccionSalidaQN);
  verificarSalida(qnEsperado);
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

void ejecutarPrueba(int a, int b, int seleccionEntrada[], int seleccionSalida[]) {
  String i_a = parseNivel(a);
  String i_b = parseNivel(b);
  Serial.println("A=" + i_a + ", B=" + i_b);
  seleccionarEntrada(seleccionEntrada);
  seleccionarSalida(seleccionSalida);

  digitalWrite(PIN_A, a);
  digitalWrite(PIN_B, b);
}

boolean verificarSalida(int esperado) {
  Serial.println("esperado=" + parseNivel(esperado));
  int y = digitalRead(PIN_Y);

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
  return "" + entrada[3] + entrada[2] + entrada[1] + entrada[0];
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

