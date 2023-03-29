
void conectarWifi() {

  wifiMulti.addAP(ssid_1, password_1);
  wifiMulti.addAP(ssid_2, password_2);

  Serial.println("Conectando con Wifi...");
  if (wifiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi Conectado");
    Serial.println("Mi IP es: ");
    Serial.println(WiFi.localIP());
    estado = noMQTT;
  }

  MDNS.begin(nombre);
  configurarOTA();
  ConfigurarMQTT();

  TelnetStream.begin();
}


void actualizarWifi() {

  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("Wifi No Conectada!");
    delay(500);
    estado = noWifi;
    return;
  }

  ArduinoOTA.handle();

  actualizarMQTT();

}

void LeerTelnet() {
  if (TelnetStream.available()) {
    char Letra = TelnetStream.read();
    switch (Letra) {
      case 'e':
      case 'E':
        TelnetStream.print("Estado del sistema: ");
        switch (estado) {
          case noWifi:
            TelnetStream.print("No Wifi, como viste este mensaje??");
            break;
          case noMQTT:
            TelnetStream.print("Si Wifi, falta MQTT");
            break;
          case conectado:
            TelnetStream.print("Todo conectado");
            break;
          default:
            TelnetStream.print("Que paso aqui??");
            break;
        }
        TelnetStream.println();
        TelnetStream.print("SubReal: ");
        TelnetStream.println(SubReal);
        break;
    }
  }
}
