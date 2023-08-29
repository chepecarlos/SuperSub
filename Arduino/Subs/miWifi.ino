
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
    estadoLocal = noMQTT;
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
    estadoLocal = noWifi;
    return;
  }

  ArduinoOTA.handle();

  actualizarMQTT();

}

void LeerTelnet() {
  while (TelnetStream.available()) {
    estadoSerial(TelnetStream);
  }
}
