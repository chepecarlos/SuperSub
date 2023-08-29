WiFiClient net;
WiFiClient netLocal;
MQTTClient clientMQTT;
MQTTClient clientMQTTLocal;


void ConfigurarMQTT() {
  clientMQTT.begin(BrokerMQTT, net);
  clientMQTT.onMessage(mensajeMQTT);
  clientMQTTLocal.begin(BrokerMQTTLocal, netLocal);
  clientMQTTLocal.onMessage(mensajeMQTTLocal);
}

void mensajeMQTT(String &topic, String &payload) {
  Serial.println("Mensaje: " + topic + " - " + payload);
  TelnetStream.println("Mensaje: " + topic + " - " + payload);
  SubReal = payload.toFloat();
}

void mensajeMQTTLocal(String &topic, String &payload) {
  Serial.println("Mensaje Local: " + topic + " - " + payload);
  TelnetStream.println("Mensaje Local: " + topic + " - " + payload);

  if (topic.equals("alsw/subreal")) {
    Serial.println("Cambiando sub");
    TelnetStream.println("Cambiando sub");
    SubReal = payload.toFloat();
  }
  else if (topic.endsWith("activo")) {
    pantallaActiva = !pantallaActiva;
    Serial << "Cambiando estado: " << (pantallaActiva ? "Activo" : "Desactivo") << "\n";
    TelnetStream << "Cambiando estado: " << (pantallaActiva ? "Activo" : "Desactivo") << "\n";
  }
}

void actualizarMQTT() {
  clientMQTT.loop();
  delay(10);
  clientMQTTLocal.loop();
  delay(10);

  if (!clientMQTT.connected()) {
    if (!clientMQTT.connect(nombre)) {
      delay(500);
      Serial.println("MQTT - No Conectada!");
      return;
    }
    estado = noMQTT;
  } else if (estado == noMQTT) {
    estado = conectado;
    clientMQTT.subscribe(TopicMQTT);
    Serial.println("MQTT - Conectada!");
    TelnetStream.println("MQTT - Conectada!");
  }

  if (!clientMQTTLocal.connected()) {
    if (!clientMQTTLocal.connect(nombre)) {
      delay(500);
      Serial.println("MQTT Local - No Conectada!");
      return;
    }
    estadoLocal = noMQTT;
  } else if (estadoLocal == noMQTT) {
    estadoLocal = conectado;
    clientMQTTLocal.subscribe(TopicMQTTLocal);
    Serial.println("MQTT Local - Conectada!");
    TelnetStream.println("MQTT Local - Conectada!");
  }
}
