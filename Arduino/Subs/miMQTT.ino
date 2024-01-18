WiFiClient net;
WiFiClient netLocal;
MQTTClient clientMQTT;
MQTTClient clientMQTTLocal;

boolean MqttConectado = false;


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
  } else if (topic.endsWith("activo")) {
    pantallaActiva = !pantallaActiva;
    escrivirPantalla(pantallaActiva);
    Serial << "Cambiando estado: " << (pantallaActiva ? "Activo" : "Desactivo") << "\n";
    TelnetStream << "Cambiando estado: " << (pantallaActiva ? "Activo" : "Desactivo") << "\n";
  } else if (topic.indexOf("control") > 0) {
    payload.toLowerCase();
    if (payload.equals("conectado")) {
      ConectadoPC = true;
    } else {
      ConectadoPC = false;
    }
    Serial << "Cambiando PC: " << (ConectadoPC ? "Activo" : "Desactivo") << "\n";
    TelnetStream << "Cambiando PC: " << (ConectadoPC ? "Activo" : "Desactivo") << "\n";
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
  }

  if (estado == conectado and !MqttConectado) {
    // Serial.println("MQTT - Conectada!");
    // TelnetStream.println("MQTT - Conectada!");
    MqttConectado = true;
  } else {
    MqttConectado = false;
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
    for (int i = 0; i < CantidadTopic; i++) {
      clientMQTTLocal.subscribe(TopicMQTTLocal[i]);
    }
    Serial.println("MQTT Local - Conectada!");
    TelnetStream.println("MQTT Local - Conectada!");
  }
}
