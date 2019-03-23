#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include "src/Adafruit_SSD1306/Adafruit_SSD1306.h"

// OLED display TWI address
Adafruit_SSD1306 display(-1);

// DHT temperature sensor
#define DHTPIN 7      // what pin we're connected to
#define DHTTYPE DHT22  // sensor type: [DHT11, DHT22, DHT21, AM2301]
DHT_Unified dht(DHTPIN, DHTTYPE);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(27,30);
  
  display.println("Hello, world!");
  display.display();

  dht.begin();
}

void loop() {
  delay(5000);
  
  display.clearDisplay();
  
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  sensors_event_t event;

  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    display.setTextSize(4);
    display.println("Error reading temperature!");
  }
  else {
    display.setTextSize(4);
    display.print((int) event.temperature);
    display.print((char)248);
    display.println("C");
  }

  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    display.println("Error reading humidity!");
  }
  else {
    display.setTextSize(1);
    display.print("humidity:");
    display.print(event.relative_humidity);
    display.println("%");
  }
  
  display.display();
}
