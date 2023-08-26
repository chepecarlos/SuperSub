
void funcionLed() {
  EstadoLed = !EstadoLed;
  digitalWrite(pinLedEstado, EstadoLed ? HIGH : LOW);
}

void actualizarLed() {
  if (estado != estadoAnterior) {
    estadoAnterior = estado;

    switch (estado) {
      case noWifi:
        cambiarLed.attach(0.1, funcionLed);
        break;
      case noMQTT:
        cambiarLed.attach(1, funcionLed);
        break;
      case conectado:
        cambiarLed.attach(2, funcionLed);
        break;
    }
  }
}
