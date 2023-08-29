#include "LittleFS.h"

void escrivirSub(float sub) {
  char direccion[30] = "/sub.txt";
  TelnetStream.print("Escribiendo en archivo: ");
  TelnetStream.println(direccion);
  LittleFS.begin();
  File archivo = LittleFS.open(direccion, "w");
  if (!archivo) {
    TelnetStream.println("Archivo no se puede abir");
    return;
  }

  if (archivo.print(sub)) {
    TelnetStream.println("Archivo Escribiendo");
  } else {
    TelnetStream.println("Error Escribiendo");
  }
  archivo.close();
  LittleFS.end();
}


String leerSub() {
  char direccion[30] = "/sub.txt";
  Serial << "Leyendo: " << direccion << "\n";
  LittleFS.begin();
  File archivo = LittleFS.open(direccion, "r");
  if (!archivo) {
    Serial.println("Archivo no se puede abir");
    return "";
  }

  String Mensaje;
  while (archivo.available()) {
    Mensaje = archivo.readString();
  }
  archivo.close();
  LittleFS.end();
  return Mensaje;
}


void escrivirPantalla(boolean estado) {
  char direccion[30] = "/pantalla.txt";
  TelnetStream.print("Escribiendo en archivo: ");
  TelnetStream.println(direccion);
  LittleFS.begin();
  File archivo = LittleFS.open(direccion, "w");
  if (!archivo) {
    TelnetStream.println("Archivo no se puede abir");
    return;
  }

  if (archivo.print(estado)) {
    TelnetStream.println("Archivo Escribiendo");
  } else {
    TelnetStream.println("Error Escribiendo");
  }
  archivo.close();
  LittleFS.end();
}


boolean leerPantalla() {
  char direccion[30] = "/pantalla.txt";
  Serial << "Leyendo: " << direccion << "\n";
  LittleFS.begin();
  File archivo = LittleFS.open(direccion, "r");
  if (!archivo) {
    Serial.println("Archivo no se puede abir");
    return false;
  }

  String Mensaje;
  while (archivo.available()) {
    Mensaje = archivo.readString();
  }
  archivo.close();
  LittleFS.end();
  return Mensaje.toInt();
}


void formatiarMemoria(Stream &miSerial) {

#if defined(ESP32)
  if (!LittleFS.begin(true)) {
    Serial.println("Error formatiando");
    return;
  }
#endif

  if (!LittleFS.format()) {
    miSerial.println("Error formatiando");
    return;
  } else {
    miSerial.println("Se boro todo, formatiado LittleFS");
  }
}
