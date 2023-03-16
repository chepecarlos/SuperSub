template<class T> inline Print &operator <<(Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#include <Ticker.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <TelnetStream.h>


#include "data.h"

WiFiMulti wifiMulti;
Ticker cambiarLed;

#define noWifi 0
#define noMQTT 1
#define conectado 2

int ledEstado = 2;
boolean EstadoLed = false;
int estado = noWifi;
int estadoAnterior = -1;

void funcionLed() {
  EstadoLed = !EstadoLed;
  digitalWrite(ledEstado, EstadoLed ? HIGH : LOW);
}

void setup() {
  Serial.begin(9600);
  Serial.println("iniciando sistema de SuperSub");
  pinMode(ledEstado, OUTPUT);
  digitalWrite(ledEstado, LOW);
  actualizarEstado();

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
}

void loop() {
  actualizarEstado();
  WifiActiva();
}

void actualizarEstado() {
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
