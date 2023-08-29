template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include <Ticker.h>
#include <ESPmDNS.h>
//#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFi.h>
#include <MQTT.h>
#include <WiFiMulti.h>
#include <TelnetStream.h>
#include "RTClib.h"

#include "data.h"

WiFiMulti wifiMulti;
Ticker cambiarLed;

#define noWifi 0
#define noMQTT 1
#define conectado 2

int pinLedEstado = 4;
boolean EstadoLed = false;

int estado = noWifi;
int estadoAnterior = -1;

int estadoLocal = noWifi;
int estadoAnteriorLocal = -1;

float SubReal = -1;
float SubRealAnterior = 0;

boolean pantallaActiva = true;
boolean pantallaActivaAnterior = false;

void setup() {
  Serial.begin(115200);
  Serial.println("iniciando sistema de SuperSub");

  pinMode(pinLedEstado, OUTPUT);
  digitalWrite(pinLedEstado, LOW);
  actualizarLed();

  //Activando codigo a cargarse en procesador 0
  //Procesador 1 Exclusico para Wifi
  //Procesador 0 Actualizar pantalla
  xTaskCreatePinnedToCore(
    MultiCore,   /* Nombre de la funcion */
    "MultiCore", /* Nombre del proceso  */
    10000,      /* Tamano de palabra */
    NULL,       /* parametros de entrada */
    0,          /* Prioridas del proceso */
    NULL,       /* Manejo del proceso  */
    0);  /* Procesador a poner la operacion */
  delay(100);

  conectarWifi();
  iniciarReloc();
}

void loop() {
  actualizarLed();
  actualizarWifi();
  LeerTelnet();
  actualizarSerial();
}

void actualizarSerial() {
  while (Serial.available()) {
    estadoSerial(Serial);
  }
}

void estadoSerial(Stream & miSerial) {
  char Letra = miSerial.read();
  switch (Letra) {
    case 'e':
    case 'E':
      miSerial.print("Estado del sistema: ");
      switch (estado) {
        case noWifi:
          miSerial.print("No Wifi, como viste este mensaje??");
          break;
        case noMQTT:
          miSerial.print("Si Wifi, falta MQTT");
          break;
        case conectado:
          miSerial.print("Todo conectado");
          break;
        default:
          miSerial.print("Que paso aqui??");
          break;
      }
      miSerial.println();
      miSerial << "SubReal: " << SubReal << "\n";
      miSerial << "SubGuardado" << leerSub() << "\n";
      break;
    case 'r':
    case 'R':
      formatiarMemoria(miSerial);
      break;
  }
}
