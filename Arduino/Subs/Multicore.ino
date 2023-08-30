
#define suscriptor 0
#define tiempo 1
#define temperatura 2

int estadoPantalla = temperatura;

int numero = 0;

void MultiCore( void * pvParameters ) {

  Serial.println("Procesos en Procesador 0 Iniciados");
  InicializarPantallas();
  iniciarSistema();
  while (true) {
    if (pantallaActiva) {
      switch (estadoPantalla) {
        case suscriptor:
          dibujarSub();
          break;
        case tiempo:
          dibujarTiempo();
          break;
        case temperatura:
          dibujarTemperatura();
          break;
        default:
          numero = suscriptor;
          break;
      }

    } else {
      mostarNumeros(0);
      pantallaActivaAnterior = pantallaActiva;
    }
    delay(500);
  }
}


void dibujarSub() {
  if (SubReal >= 0) {
    if (SubReal != SubRealAnterior) {
      SubRealAnterior = SubReal;
      mostarNumeros(SubReal);
      Serial << "Actualizando pantalla " << SubReal << "\n";
      TelnetStream << "Actualizando pantalla " << SubReal << "\n";
      escrivirSub(SubReal);
    } else if (pantallaActiva != pantallaActivaAnterior ) {
      pantallaActivaAnterior = pantallaActiva;
      Serial << "Redibujar\n";
      TelnetStream << "Redibujar\n";
      mostarNumeros(SubReal);
    }
  }
}

void dibujarTiempo() {
  if (relocActivo()) {
    actualizarFecha();
    int hora = horaActual() ;
    int minuto = minutoActual();
    boolean pm = esPM();
    Serial << "Hora: " << hora << ":" << minuto << " " << (pm ? "PM" : "AM") << "\n";
    mostarHora(hora, minuto, pm);
  } else {
    Serial << "Error con la hora\n";
  }
}

void dibujarTemperatura() {
  if (relocActivo()) {
    float temperaturaInterna = temperaturaActual();
    Serial << "Temeratura Actual: " << temperaturaInterna << "\n";
    mostarTemperatura(temperaturaInterna);
  } else {
    Serial << "Error con la Tempetura\n";
  }
}

void dibujarDefault() {
  numero++;
  numero %= 100000;
  TelnetStream.println(numero);
  Serial.println(numero);
  mostarNumeros(numero);
}

void iniciarSistema() {
  mostarNumeros(99999);
  delay(500);
  mostarNumeros(12345);
  delay(500);
  SubReal = leerSub().toInt();
  Serial << "Cargando Sub: " << SubReal << "\n";
  pantallaActiva = leerPantalla();
  Serial << "Cargando pantalla Activa: " << (pantallaActiva ? "Activa" : "Desactiva") << "\n";
}
