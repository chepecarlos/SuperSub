

int numero = 0;

void MultiCore( void * pvParameters ) {

  Serial.println("Procesos en Procesador 0 Iniciados");
  InicializarPantallas();
  mostarNumeros(99999);
  delay(500);

  while (true) {

    mostarNumeros(numero);
    numero++;
    numero %= 100000;

    TelnetStream.println(numero);
    delay(500);
  }
}
