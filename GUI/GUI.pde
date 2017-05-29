import processing.serial.*;

Serial myPort;
String val;

int xorX;
int xorY;
int compX;
int compY;
int ffX;
int ffY;

int anchoBoton;
int altoBoton;
int espacioEntreBotones;

color colorOK;
color colorNOK;
color colorEjecutandoPruebas;

boolean xorOK;
boolean compOK;
boolean ffOK;

boolean firstContact = false;

void setup() {
  size(640, 360);

  anchoBoton = 120;
  altoBoton = 90;
  espacioEntreBotones = 20;

  colorOK = color(0, 128, 0);
  colorNOK = color(255, 0, 0);
  colorEjecutandoPruebas = color(143, 188, 143);

  compX = (width / 2) - (anchoBoton / 2);
  compY = (height / 2) - (altoBoton / 2);

  xorX = compX - (espacioEntreBotones + anchoBoton);
  xorY = compY;

  ffX = compX + espacioEntreBotones + anchoBoton;
  ffY = compY;

  ellipseMode(CENTER);

  background(255);

  String portName = Serial.list()[0]; //Verificar
  myPort = new Serial(this, portName, 9600);
  //myPort.bufferUntil('\n');
}

void draw() {
  stroke(0);

  establecerColor(xorOK);
  rect(xorX, xorY, anchoBoton, altoBoton);

  establecerColor(compOK);
  rect(compX, compY, anchoBoton, altoBoton);

  establecerColor(ffOK);
  rect(ffX, ffY, anchoBoton, altoBoton);
}

//void serialEvent(Serial myPort) {
//  val = myPort.readStringUntil('\n');

//  if (val != null) {
//    val = trim(val);
//    println(val);

//    if (firstContact == false) {
//      if (val.equals("%")) {
//        myPort.clear();
//        firstContact = true;
//        myPort.write("%");
//        println("contact");
//      }
//    } else {
//      //println(val);
//    }
//  }

//  myPort.write('&');
//}

void mousePressed() {
  if (sobreXOR()) {
    xorOK = ejecutarPrueba('0', "$XORSOK");
  } else if (sobreCOMP()) {
    compOK = ejecutarPrueba('1', "$COMPOK");
  } else if (sobreFF()) {
    ffOK = ejecutarPrueba('2', "$FFSOK");
  }
}

boolean ejecutarPrueba(char valorArduino, String mensajeOK) {
  inicioPruebas();

  myPort.write(valorArduino);
  myPort.write('\n');

  boolean pruebaEnCurso = true;
  boolean pruebasOK = false;
  while (pruebaEnCurso) {
    val = readLineWithHandshake();
    if (val == null) {
      continue;
    }
    val = val.trim();
    println(val);
    if (val.charAt(0) == '$') {
      if (val.equals(mensajeOK)) { 
        println("pruebas OK");
        pruebasOK = true;
      } else {
        println("pruebas NOK");
      }
      pruebaEnCurso = false;
    }
  }

  finPruebas();
  return pruebasOK;
}

void inicioPruebas() {
  background(colorEjecutandoPruebas);
}

void finPruebas() {
  background(color(255));
}

boolean sobreXOR() {
  return sobreRectangulo(xorX, xorY, anchoBoton, altoBoton);
}

boolean sobreCOMP() {
  return sobreRectangulo(compX, compY, anchoBoton, altoBoton);
}

boolean sobreFF() {
  return sobreRectangulo(ffX, ffY, anchoBoton, altoBoton);
}

boolean sobreRectangulo(int x, int y, int ancho, int alto) {
  if (mouseX >= x && mouseX <= x + ancho && 
    mouseY >= y && mouseY <= y + alto) {
    return true;
  } else {
    return false;
  }
}

void establecerColor(boolean ok) {
  if (ok) {
    fill(colorOK);
  } else {
    fill(colorNOK);
  }
}

String readLineWithHandshake() {
  myPort.write('&');
  myPort.write('\n');
  while (true) {
    if (myPort.available() > 0) {
      String linea = myPort.readStringUntil('\n');
      return linea;
    }
    delay(300);
  }
}