//@see: https://build.particle.io/libs/Adafruit_DHT/0.0.2
#include <Adafruit_DHT.h>

//@see: https://build.particle.io/libs/Adafruit_SSD1306/0.0.2
#include <Adafruit_SSD1306.h>

// Display
#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);

// DHT temperature sensor
#define DHTPIN D3      // what pin we're connected to
#define DHTTYPE DHT22  // sensor type: [DHT11, DHT22, DHT21, AM2301]
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  display.println("Hello, world!");
  display.display();

  dht.begin();
}

void loop() {
  delay(5000); // Seconds.

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  float humidity = dht.getHumidity();
  float temperature = dht.getTempCelcius();
  float heatIndex = dht.getHeatIndex();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature) || isnan(heatIndex)) {
    display.println("Failed to read from DHT sensor!");
    display.display();
    return;
  }

  display.println(Time.timeStr());

  display.print("temperature: ");
  display.println(temperature);

  display.print("humidity: ");
  display.println(humidity);

  display.print("heatIndex: ");
  display.println(heatIndex);

  display.display();
}
