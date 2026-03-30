#include <LiquidCrystal.h>

// LCD pins: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

#define sensor A0

// custom degree symbol
byte degree[8] = {
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup()
{
  lcd.begin(16,2);

  lcd.createChar(0, degree);

  lcd.setCursor(0,0);
  lcd.print("Digital");

  lcd.setCursor(0,1);
  lcd.print("Thermometer");

  delay(2000);
  lcd.clear();
}

void loop()
{
  // read analog value
  float reading = analogRead(sensor);

  // convert to voltage
  float voltage = reading * (5.0 / 1023.0);

  // LM35 temperature formula
  float temperature = voltage * 100;

  // display on LCD
  lcd.setCursor(0,0);
  lcd.print("Temperature:");

  lcd.setCursor(4,1);
  lcd.print(temperature);

  lcd.write(byte(0)); // degree symbol
  lcd.print("C   ");

  delay(1000);
}