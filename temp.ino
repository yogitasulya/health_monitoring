//MY 2nd project Health Monitoring System 
//by yogita Sulya

#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

const int SENSOR_PIN = 13;

OneWire oneWire(SENSOR_PIN);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27,16,2);

double alpha = 0.75;
int period = 20;
double refresh=0.0;
float tempCelsius;

void setup()
{
  pinMode(A0,INPUT);
  sensors.begin();
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop ()
{
  static double oldValue=0;
  static double oldrefresh=0;

  int beat = analogRead(A0);

  double value=alpha*oldValue+(0-alpha)*beat;

 int refresh=value-oldValue;
  sensors.requestTemperatures();
  tempCelsius = sensors.getTempCByIndex(0);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Body:  ");
  lcd.print(tempCelsius);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Heart:  ");
  lcd.print(beat/10);
  oldValue=value;
  oldrefresh=refresh;
  delay(period*10);

  delay(500);

}