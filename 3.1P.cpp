#include "Adafruit_DHT.h"
#define DHTPIN 2    
#define DHTTYPE DHT11

int temperature, humidity, previousTemperature, previousHumidity;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
	Serial.begin(9600); 
    
    temperature = dht.getTempCelcius();
	humidity = dht.getHumidity();
	
	previousTemperature = temperature;
	previousHumidity = humidity;
    
	dht.begin();
}

void loop() {
    // Transmit every 10 seconds
	delay(10000);
	

	temperature = dht.getTempCelcius();
	humidity = dht.getHumidity();
	
	
	// Remove anomalies
	if(temperature > (1.5 * previousTemperature) || temperature < (0.5 * previousTemperature)) {
	    temperature = previousTemperature;
	}
	
	if(humidity > (1.5 * previousHumidity) || humidity < (0.5 * previousHumidity)) {
	    humidity = previousHumidity;
	}
	
    // Publish to Webhook
	Particle.publish("Temperature Reading (C)", String(temperature)); 
	Particle.publish("Humidity (%)", String(humidity));
	
	// Publish alert to events
	if(temperature != previousTemperature) {
	    Particle.publish("--- ALERT ---", "Temperature Changed!!");
	}
	if(humidity != previousHumidity) {
	    Particle.publish("--- ALERT ---", "Humidity Changed!!");
	}
}