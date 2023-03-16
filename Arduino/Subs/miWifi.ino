
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
  } else {
    estado = noMQTT;
  }

  ArduinoOTA.handle();
  client.loop();
  delay(10);

  if (!client.connected()) {
    Serial.println("MQTT - No Conectada!");
    if (!client.connect(nombre)) {
      delay(500);
      return;
    }
    client.subscribe("/sub");
    Serial.println("MQTT - Conectada!");
  }


}
