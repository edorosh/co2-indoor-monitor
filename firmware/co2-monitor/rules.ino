void handleLedIndicator() {
  if (CO2 < 700) {
    setLED(LED_YELLOW);
    Serial.println("Led set Green");
    return;
  } 

  if (CO2 < 1200) {
    Serial.println("Led set Blue");
    setLED(LED_BLUE);
    return;
  }
  
  setLED(LED_RED);
  Serial.println("Led set RED");
}

void handleMusic() {
   requestPlayMelody = (CO2 >= 1200);
}
