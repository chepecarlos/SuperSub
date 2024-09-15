
#define suscriptor 0
#define tiempo 1
#define temperatura 2

int mostarPantalla = temperatura;

int numero = 0;
int cambioPantalla = 4;

int temperaturaAnterior = 0;
int minutoAnterior = -1;
estructuraEstado estadoDibujado = { true, true };

void MultiCore(void* pvParameters) {

  Serial.println("Procesos en Procesador 0 Iniciados");
  InicializarPantallas();
  iniciarSistema();
  configurarCambioPantalla();
  while (true) {
    if (estadoPantalla.actual) {
      switch (mostarPantalla) {
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

void funcionCambioPantalla() {
  mostarPantalla++;
  estadoDibujado.actual = false;
  if (mostarPantalla > temperatura) {
    mostarPantalla = suscriptor;
  }
}

void configurarCambioPantalla() {
  cambiarPantalla.attach(cambioPantalla, funcionCambioPantalla);
}

void dibujarSub() {
  if (SubReal >= 0) {
    if (SubReal != SubRealAnterior) {
      SubRealAnterior = SubReal;
      mostarNumeros(SubReal);
      Serial << "Actualizando pantalla " << SubReal << "\n";
      TelnetStream << "Actualizando pantalla " << SubReal << "\n";
      escrivirSub(SubReal);
    } else  // if (pantallaActiva != pantallaActivaAnterior ) {
    {
      pantallaActivaAnterior = pantallaActiva;
      // Serial << "Redibujar\n";
      // TelnetStream << "Redibujar\n";
      mostarNumeros(SubReal);
    }
  }
}

void dibujarTiempo() {
  if (relocActivo()) {
    actualizarFecha();
    int hora = horaActual();
    int minuto = minutoActual();
    boolean pm = esPM();
    if (minuto != minutoAnterior || !estadoDibujado.actual) {
      estadoDibujado.actual = true;
      minutoAnterior = minuto;
      mostarHora(hora, minuto, pm);
      Serial << "Hora: " << hora << ":" << minuto << " " << (pm ? "PM" : "AM") << "\n";
    }
  } else {
    Serial << "Error con la hora\n";
  }
}

void dibujarTemperatura() {
  if (relocActivo()) {
    int temperaturaInterna = abs(temperaturaActual());
    if (temperaturaAnterior != temperaturaInterna || !estadoDibujado.actual) {
      temperaturaAnterior = temperaturaInterna;
      estadoDibujado.actual = true;
      Serial << "Temeratura Actual: " << temperaturaInterna << "\n";
      mostarTemperatura(temperaturaInterna);
    }
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
  estadoPantalla.actual = leerPantalla();
  Serial << "Cargando pantalla Activa: " << (estadoPantalla.actual ? "Activa" : "Desactiva") << "\n";
}
