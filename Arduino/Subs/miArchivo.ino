#include "LittleFS.h"

void escrivirArchivo(float sub) {
  //  char numero[8]; // Buffer big enough for 7-character float
  //  dtostrf(sub, 6, 2, numero); // Leave room for too large numbers!
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


String leerArchivo() {
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
