void setLED(LED_COLOR color) {
  // Turn all the colors
  analogWrite(LED_RED_PIN, 0);
  analogWrite(LED_GREEN_PIN, 0);
  analogWrite(LED_BLUE_PIN, 0);

  // Turn on the color
  switch (color) {
    case LED_RED:
      analogWrite(LED_RED_PIN, LED_BRIGHTNESS);
      break;
    case LED_GREEN: 
      analogWrite(LED_GREEN_PIN, LED_BRIGHTNESS);
      break;
    case LED_BLUE: 
      analogWrite(LED_BLUE_PIN, LED_BRIGHTNESS);
      break;
    case LED_YELLOW: 
      analogWrite(LED_RED_PIN, LED_BRIGHTNESS - 50); //todo: refactor by 100%
      analogWrite(LED_GREEN_PIN, LED_BRIGHTNESS);
      break;
  }
}
