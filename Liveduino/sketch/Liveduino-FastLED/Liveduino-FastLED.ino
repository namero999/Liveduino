#include <FastLED.h>

#define LED_PIN     10
#define NUM_LEDS    14
#define BRIGHTNESS  16
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

int pin;
int value;

void setup() {

  delay(2000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  for (pin = 0; pin <= 13; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, 0);
  }

  Serial.begin(57600);

}
int note, velocity, brightness;
void loop() {

  while (Serial.available() >= 3 && Serial.read() == 0xff) {

    value = Serial.read();
    pin = Serial.read();
    if (pin == 10) {
      randomSeed(value);
      note = random(256);
      for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = CHSV(note, brightness, velocity);
    }
    else if (pin == 4) {
      brightness = value;
      for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = CHSV(note, brightness, velocity);
    }
    else if (pin == 11) {
      velocity = value;
      for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = CHSV(note, brightness, velocity);
    }
//      isPWM(pin) ? analogWrite(pin, value) : digitalWrite(pin, value);
    leds[random(NUM_LEDS)] = CRGB::Black;

  }

  FastLED.show();

}

boolean isPWM(int pin) {
  return pin == 3 || pin == 5 || pin == 6 || pin == 9 || pin == 10 || pin == 11;
}

// DEBUG

//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 20, 4);
//lcd.init();
//lcd.backlight();
//lcd.clear();
//char buf[3];
//lcd.setCursor(0, 0);
//sprintf(buf, "%3d", value);
//lcd.print(buf);
