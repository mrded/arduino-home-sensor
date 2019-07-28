#include "src/CO2Sensor/src/CO2Sensor.h"
CO2Sensor co2Sensor(A0, 0.99, 100);

#include "src/LiquidCrystal_I2C/LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27,20,4);

#include "src/TinyDHT/TinyDHT.h"
// DHT temperature sensor
#define DHTPIN 7      // what pin we're connected to
#define DHTTYPE DHT22  // sensor type: [DHT11, DHT22, DHT21, AM2301]

DHT dht(DHTPIN, DHTTYPE);

int uptime = 0;

void setup() {
  lcd.init();
  lcd.backlight();

  co2Sensor.calibrate();
  lcd.setCursor(0,0);
  lcd.print("CO2 sensor: OK!");

  dht.begin();
  lcd.setCursor(0,1);
  lcd.print("DHT sensor: OK!");
}

void loop() {
  String co2 = String(co2Sensor.read());
  String temperature = String(dht.readTemperature());
  String humidity = String(dht.readHumidity());

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Temperature: " + temperature + " C");

  lcd.setCursor(3,1);
  lcd.print("Humidity: " + humidity + " %");

  lcd.setCursor(8,2);
  lcd.print("CO2: " + co2 + " ppm");

  lcd.setCursor(5,3);
  lcd.print("Uptime: " + String(uptime++) + " min");
  
  delay(60000);
}
