

int numero = 0;

void MultiCore( void * pvParameters ) {

  Serial.println("Procesos en Procesador 0 Iniciados");
  InicializarPantallas();
  mostarNumeros(99999);
  delay(500);

  while (true) {

    if (SubReal >= 0) {
      mostarNumeros(SubReal);
      Serial.println(SubReal);
      TelnetStream.println(SubReal);
    } else {
      mostarNumeros(numero);
      numero++;
      numero %= 100000;
      TelnetStream.println(numero);
      Serial.println(numero);
    }
    delay(500);
  }
}
