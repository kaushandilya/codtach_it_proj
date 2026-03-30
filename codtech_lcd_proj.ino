#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SENSOR_PIN A0

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup()
{
  lcd.begin(16,2);   // FIXED
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Temp Sensor");
  delay(2000);
  lcd.clear();
}

void loop()
{
  int adcValue = analogRead(SENSOR_PIN);

  float voltage = adcValue * (5.0 / 1023.0);

  float temperature = voltage * 100;

  lcd.setCursor(0,0);
  lcd.print("Temperature:");

  lcd.setCursor(0,1);
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C   ");

  delay(1000);
}