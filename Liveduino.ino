int pin;
int value;

void setup() {

  for (pin = 0; pin <= 13; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, 0);
  }

  Serial.begin(57600);

}

void loop() {

  while (Serial.available() >= 3 && Serial.read() == 0xff) {

    value = Serial.read();
    pin = Serial.read();

    isPWM(pin) ? analogWrite(pin, value) : digitalWrite(pin, value);

  }

  delay(2);

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
