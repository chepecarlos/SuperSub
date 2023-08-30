
RTC_DS3231 rtc;
boolean estadoReloc = false;
DateTime fechaActual;

void iniciarReloc() {
  if (!rtc.begin()) {
    Serial.println("No encontrado RTC");
    Serial.flush();
    estadoReloc = false;
    return;
  }
  Serial.println("RTC encontrado");
  estadoReloc = true;
}

float temperaturaActual() {
  return rtc.getTemperature();
}

boolean relocActivo() {
  return estadoReloc;
}

void actualizarFecha() {
  fechaActual =  rtc.now();
}

int horaActual() {
  return fechaActual.twelveHour();
}

int minutoActual() {
  return fechaActual.minute();
}

boolean esPM() {
  return fechaActual.isPM();
}
