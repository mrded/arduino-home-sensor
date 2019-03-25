#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

// DHT temperature sensor
#define DHTPIN 7      // what pin we're connected to
#define DHTTYPE DHT22  // sensor type: [DHT11, DHT22, DHT21, AM2301]
DHT_Unified dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  
  lcd.print("Hello, world!");

  dht.begin();
}

void loop() {
  delay(5000);

  lcd.clear();

  lcd.setCursor(0,0);

  sensors_event_t event;

  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    lcd.setCursor(0,0);
    lcd.print("Error reading temperature!");
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("temperature:");
    lcd.setCursor(13,0);
    lcd.print((int) event.temperature);
  }

  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    lcd.setCursor(0,1);
    lcd.print("Error reading humidity!");
  }
  else {
    lcd.setCursor(3,1);
    lcd.print("humidity:");
    lcd.setCursor(13,1);
    lcd.print(event.relative_humidity);
  }
}
