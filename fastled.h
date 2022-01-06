void setupFastLED(){
  // three-wire LEDs (WS2811, WS2812, NeoPixel)
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS);
  // set master brightness control
  FastLED.setBrightness(brightness);
}

void rainbow() {
  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = CHSV(hue + (i * 10), 255, 255);
  }
  //You can change the pattern speed here
  EVERY_N_MILLISECONDS(20){ hue++; }
  FastLED.show();
}
void flash(){
  fill_solid(leds,NUM_LEDS,CRGB::White);
  FastLED.setBrightness(255);
  FastLED.show();
  delay(50);
  FastLED.clear();
  FastLED.show();
  delay(50);
}

void initTest(){
  for (int i=0; i< NUM_LEDS; i++){
    leds[i]=CRGB::Blue;
    FastLED.show();
    leds[i]=CRGB::Black;
    delay(50);
  }
  for (int i=0; i< NUM_LEDS; i++){
    leds[i]=CRGB::Green;
    FastLED.show();
    leds[i]=CRGB::Black;
    delay(50);
  }
  for (int i=0; i< NUM_LEDS; i++){
    leds[i]=CRGB::Red;
    FastLED.show();
    leds[i]=CRGB::Black;
    delay(50);
  }
  for (int j=0; j<3; j++){
    flash();
  }
  for (int l=0; l<4000; l++){
    rainbow();
  }
  FastLED.setBrightness(128);
  FastLED.clear ();
  FastLED.show();
}
