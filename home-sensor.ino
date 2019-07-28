#include "src/CO2Sensor/src/CO2Sensor.h"
CO2Sensor co2Sensor(A0, 0.99, 100);

#include "src/LiquidCrystal_I2C/LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27,20,4);

#include "src/TinyDHT/TinyDHT.h"
// DHT temperature sensor
#define DHTPIN 7      // what pin we're connected to
#define DHTTYPE DHT22  // sensor type: [DHT11, DHT22, DHT21, AM2301]

DHT dht(DHTPIN, DHTTYPE);

int uptime;

void setup() {
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Temperature:");

  lcd.setCursor(3,1);
  lcd.print("Humidity:");

  lcd.setCursor(8,2);
  lcd.print("CO2:");

  lcd.setCursor(5,3);
  lcd.print("Uptime:");

  dht.begin();
  co2Sensor.calibrate();

  uptime = 0;
}

void loop() {
  String co2 = String(co2Sensor.read());
  String temperature = String(dht.readTemperature());
  String humidity = String(dht.readHumidity());

  lcd.setCursor(13,0);
  lcd.print(temperature + " C");

  lcd.setCursor(13,1);
  lcd.print(humidity + " %");

  lcd.setCursor(13,2);
  lcd.print(co2 + " ppm");

  lcd.setCursor(13,3);
  lcd.print(String(uptime++) + " min");
  
  delay(60000);
}
