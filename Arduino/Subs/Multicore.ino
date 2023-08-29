

int numero = 0;

void MultiCore( void * pvParameters ) {

  Serial.println("Procesos en Procesador 0 Iniciados");
  InicializarPantallas();
  mostarNumeros(99999);
  delay(500);
  SubReal = leerArchivo().toInt();
  Serial << "Cargando Sub: " << SubReal << "\n";
  while (true) {
    if (pantallaActiva) {
      if (SubReal >= 0) {
        if (SubReal != SubRealAnterior) {
          SubRealAnterior = SubReal;
          mostarNumeros(SubReal);
          Serial << "Actualizando pantalla " << SubReal << "\n";
          TelnetStream << "Actualizando pantalla " << SubReal << "\n";
          escrivirArchivo(SubReal);
        } else if (pantallaActiva != pantallaActivaAnterior ) {
          pantallaActivaAnterior = pantallaActiva;
          Serial << "Redibujar\n";
          TelnetStream << "Redibujar\n";
          mostarNumeros(SubReal);
        }
      }  else {
        mostarNumeros(numero);
        numero++;
        numero %= 100000;
        TelnetStream.println(numero);
        Serial.println(numero);
      }
    } else {
      mostarNumeros(0);
      pantallaActivaAnterior = pantallaActiva;
    }

    delay(500);
  }
}
