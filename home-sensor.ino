// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_IO_Client.h"

// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_IO_Arduino.h"

// This #include statement was automatically added by the Particle IDE.
#include "DHT.h"

// AdaFruit.io
#include "Adafruit_IO_Client.h"
#include "Adafruit_IO_Arduino.h"

//
// Includes
//
#include "DHT.h"
#include "application.h"

//
// Configuration
//

// device name
#define DEVICE_NAME "home-sensor"

// sensor type: [DHT11, DHT22, DHT21, AM2301]
#define DHTTYPE DHT22

// which digital pin for the DHT
#define DHTPIN D3

// which digital pin for the Photon/Spark Core/Electron LED
#define LEDPIN D7

// whether to use Farenheit instead of Celsius
#define USE_FARENHEIT 0

// min/max values (sanity checks)
#define MIN_TEMPERATURE -30
#define MAX_TEMPERATURE 120

#define MIN_HUMIDITY 0
#define MAX_HUMIDITY 100

// sensor sending interval (seconds)
#define SEND_INTERVAL 60

// AdaFruit integration
#define ADAFRUIT_API_KEY ""
#define ADAFRUIT_FEED_TEMPERATURE "temp"
#define ADAFRUIT_FEED_HUMIDITY "humidity"
#define ADAFRUIT_FEED_HEAT_INDEX "heat-index"

// Particle event
#define PARTICLE_EVENT 0
#define PARTICLE_EVENT_NAME "dht-logger-log"

//
// Integration Includes
//

//
// Locals
//
TCPClient tcpClient;

DHT dht(DHTPIN, DHTTYPE);

float humidity;
float temperature;
float heatIndex;

char humidityString[10];
char temperatureString[10];
char heatIndexString[10];

int failed = 0;

// last time since we sent sensor readings
int lastUpdate = 0;

Adafruit_IO_Client aio = Adafruit_IO_Client(tcpClient, ADAFRUIT_API_KEY);
Adafruit_IO_Feed aioFeedTemperature = aio.getFeed(ADAFRUIT_FEED_TEMPERATURE);
Adafruit_IO_Feed aioFeedHumidity = aio.getFeed(ADAFRUIT_FEED_HUMIDITY);
Adafruit_IO_Feed aioFeedHeatIndex = aio.getFeed(ADAFRUIT_FEED_HEAT_INDEX);

// for HTTP POST and Particle.publish payloads
char payload[1024];

/**
 * Setup
 */
void setup() {
    pinMode(LEDPIN, OUTPUT);
    digitalWrite(LEDPIN, HIGH);

    // configure Particle variables - float isn't accepted, so we have to use string versions
    Particle.variable("temperature", &temperatureString[0], STRING);
    Particle.variable("humidity", &humidityString[0], STRING);
    Particle.variable("heatIndex", &heatIndexString[0], STRING);

    Particle.variable("status", &failed, INT);

    // start the DHT sensor
    dht.begin();

    aio.begin();

#if PARTICLE_EVENT
    // startup event
    sprintf(payload,
            "{\"device\":\"%s\",\"state\":\"starting\"}",
            DEVICE_NAME);

    Spark.publish(PARTICLE_EVENT_NAME, payload, 60, PRIVATE);
#endif

    // run the first measurement
    loop();
}

/**
 * Event loop
 */
void loop() {
    int now = Time.now();

    // only run every SEND_INTERVAL seconds
    if (now - lastUpdate < SEND_INTERVAL) {
        return;
    }

    // turn on LED when updating
    digitalWrite(LEDPIN, HIGH);

    lastUpdate = now;

    failed = 0;

    // read humidity and temperature values
    humidity = dht.readHumidity();
    temperature = dht.readTemperature(USE_FARENHEIT);

    if (temperature == NAN
        || humidity == NAN
        || temperature > MAX_TEMPERATURE
        || temperature < MIN_TEMPERATURE
        || humidity > MAX_HUMIDITY
        || humidity < MIN_HUMIDITY) {
        // if any sensor failed, bail on updates
        failed = 1;
    } else {
        failed = 0;

        // calculate the heat index
        heatIndex = dht.computeHeatIndex(temperature, humidity, USE_FARENHEIT);

        // convert floats to strings for Particle variables
        sprintf(temperatureString, "%.2f", temperature);
        sprintf(humidityString, "%.2f", humidity);
        sprintf(heatIndexString, "%.2f", heatIndex);

        aioFeedTemperature.send(temperature);
        aioFeedHumidity.send(humidity);
        aioFeedHeatIndex.send(heatIndex);

        sprintf(payload,
            "{\"device\":\"%s\",\"temperature\":%.2f,\"humidity\":%.2f,\"heatIndex\":%.2f}",
            DEVICE_NAME,
            temperature,
            humidity,
            heatIndex);

#if PARTICLE_EVENT
        Spark.publish(PARTICLE_EVENT_NAME, payload, 60, PRIVATE);
#endif
    }

    // done updating
    digitalWrite(LEDPIN, LOW);
}
