#include <DHT.h>

#include "src/CO2Sensor/src/CO2Sensor.h"
CO2Sensor co2Sensor(A0, 0.99, 100);

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

// DHT temperature sensor
#define DHTPIN 7      // what pin we're connected to
#define DHTTYPE DHT22  // sensor type: [DHT11, DHT22, DHT21, AM2301]

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  
  lcd.print("Hello, world!");

  dht.begin();
  co2Sensor.calibrate();
}

void loop() {
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("temperature:");
  lcd.setCursor(13,0);
  lcd.print((int) dht.readTemperature());

  lcd.setCursor(3,1);
  lcd.print("humidity:");
  lcd.setCursor(13,1);
  lcd.print(dht.readHumidity());

  lcd.setCursor(8,2);
  lcd.print("CO2:");
  lcd.setCursor(13,2);
  lcd.print(co2Sensor.read());

  delay(1000*60);
}
