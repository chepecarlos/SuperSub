
RTC_DS3231 rtc;


void iniciarReloc() {
  if (!rtc.begin()) {
    Serial.println("No encontrado RTC");
    Serial.flush();
//    while (1) delay(10);
  }
}

float temperaturaActual() {
  return rtc.getTemperature();
}

//
//DateTime fechaActual() {
//  return rtc.now();
//}
