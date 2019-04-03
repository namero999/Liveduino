#define FASTLED_ALLOW_INTERRUPTS 1
#include <FastLED.h>

#define LED_PIN     10
#define NUM_LEDS    14
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

unsigned long last[NUM_LEDS];


void setup() {

  delay(1000);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  for (int pin = 0; pin <= 13; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, 0);
  }

  Serial.begin(57600);

}

void loop() {

  if (Serial.read() == 0xff) {
    int  value = Serial.read();
    int  channel = Serial.read();
    int  analog = Serial.read();
    int  pitch = value % 127;
    bool on = value > 127;
    if (channel == 6) {
      for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = CRGB::Black;
    } else {
      if (channel  == 3) {
        int led = map(pitch, 0, 127, 0, NUM_LEDS - 1);
        leds[led] = on ? CRGB::Red : CRGB::Black; //CHSV(map(pitch, 0, 127, 0, 255), 255, on ? 200 : 0);
      }
    }
  }

  //  if (now % 5 == 0)
  //    for (int i = 0; i < NUM_LEDS; i++)
  //      leds[i].fadeToBlackBy(2);
  //
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
