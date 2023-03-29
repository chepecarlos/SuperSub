WiFiClient net;
MQTTClient clientMQTT;

void ConfigurarMQTT() {
  clientMQTT.begin(BrokerMQTT, net);
  clientMQTT.onMessage(mensajeMQTT);
}

void mensajeMQTT(String &topic, String &payload) {
  Serial.println("Mensaje: " + topic + " - " + payload);
  TelnetStream.println("Mensaje: " + topic + " - " + payload);
  SubReal = payload.toFloat();
}

void actualizarMQTT() {
  clientMQTT.loop();
  delay(10);

  if (!clientMQTT.connected()) {
    Serial.println("MQTT - No Conectada!");
    if (!clientMQTT.connect(nombre)) {
      delay(500);
      estado = noMQTT;
      return;
    }
  } else if (estado == noMQTT) {
    estado = conectado;
    clientMQTT.subscribe("alsw/subreal");
    Serial.println("MQTT - Conectada!");
    TelnetStream.println("MQTT - Conectada!");
  } 
}
