WiFiClient net;
MQTTClient client;

void ConfigurarMQTT() {
  client.begin(BrokerMQTT, net);
  client.onMessage(mensajeMQTT);
}

void mensajeMQTT(String &topic, String &payload) {
  Serial.println("Mensaje: " + topic + " - " + payload);
}
