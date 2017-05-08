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

boolean probarXOR(int entrada[], int salida[]) {
  Serial.println("Probando XOR: " + parseEntrada(entrada));
  boolean p0 = probarXOR(LOW, LOW, entrada, salida);
  boolean p1 = probarXOR(LOW, HIGH, entrada, salida);
  boolean p2 = probarXOR(HIGH, LOW, entrada, salida);
  boolean p3 =  probarXOR(HIGH, HIGH, entrada, salida);

  boolean pruebasExitosas = p0 == p1 == p2 == p3 == true;

  if (pruebasExitosas) {
    Serial.println("XOR:" + parseEntrada(entrada) + "= OK");
  }

}

boolean probarXOR(int a, int b, int entrada[], int salida[]) {
  String i_a = parseNivel(a);
  String i_b = parseNivel(b);
  Serial.println("A=" + i_a + ", B=" + b);
  seleccionarEntrada(entrada);
  seleccionarSalida(salida);

  digitalWrite(PIN_A, a);
  digitalWrite(PIN_B, b);

  int y = digitalRead(PIN_Y);
  Serial.println("salida=" + parseNivel(y));

  boolean esperado;
  if (a != b) {
    esperado = HIGH;
  } else {
    esperado = LOW;
  }
  Serial.println("esperado=" + parseNivel(esperado));

  if (y == esperado) {
    Serial.println("OK");
    return true;
  } else {
    Serial.println("NOK");
    return false;
  }
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

