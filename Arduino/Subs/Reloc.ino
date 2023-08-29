
RTC_DS3231 rtc;
boolean estadoReloc = false;

void iniciarReloc() {
  if (!rtc.begin()) {
    Serial.println("No encontrado RTC");
    Serial.flush();
    return;
  }
  estadoReloc = true;
}

float temperaturaActual() {
  return rtc.getTemperature();
}

boolean relocActivo() {
  return true;
  return estadoReloc;
}

int horaActual() {
  return 11;
}

int minutoActual() {
  return 59 ;
}

boolean esPM() {
  return true;
}
