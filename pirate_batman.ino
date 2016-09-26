// Determines which sensors should be read
const bool lightSensorEnabled = true;
const bool soilMoistureSensorEnabled = true;
const bool temperatureSensorEnabled = true;

// Defines analog pins
const int lightSensorPin = A0;
const int soilMoistureSensorPin = A1;
const int temperatureSensorPin = A2;

// Defines the name of the sensor event
const String lightSensorEventName = "iris.light";
const String soilMoistureSensorEventName = "iris.soilMoisture";
const String temperatureSensorEventName = "iris.temperature";

// If the sensor type is enabled, output voltage to the pin
void setup() {
    if (lightSensorEnabled) {
        pinMode(lightSensorPin, INPUT);
    }
    if (soilMoistureSensorEnabled) {
        pinMode(soilMoistureSensorPin, INPUT);
    }
    if (temperatureSensorEnabled) {
        pinMode(temperatureSensorPin, INPUT);
    }
}

// Sensor readings only occur once daily
void loop() {
    // Temp sensor only runs if it's enabled and it's 6pm UTC time (1pm Central Time)
    if (temperatureSensorEnabled && Time.hour() == 18) {
        // The raw value read from the temp pin
        int temperatureSensorValue = analogRead(temperatureSensorPin);
        // Convert temperature from raw data to Celcius
        double temperatureC = (((temperatureSensorValue * 3.3)/4095) - 0.5) * 100;
        // Convert temperature from Celcius to Farenheit
        int temperatureF = ((temperatureC * 9.0) / 5.0) + 32.0;
        // If the temp is less than 40 degrees, publish temp warning event to trigger
        // IFTTT.com (If This Then That) recipe and send a text to user with message
        if (temperatureF < 40) {
            // IFTTT event trigger
            Particle.publish("TemperatureWarning", "cold");
            // Web Hook trigger to send info into Iris Database
            Particle.publish("Temperature", String(temperatureF), PRIVATE);
        } else {
            // Web Hook trigger to send info into Iris Database
            Particle.publish("Temperature", String(temperatureF), PRIVATE);
        }
        // Send event data to Particle Logs
        Particle.publish(temperatureSensorEventName, String(temperatureF));
    }
    // Wait 1 minute before doing anything else (helps prevent hitting API limits)
    delay(60000);
    // Light sensor only runs if it's enabled and it's 6pm UTC time (1pm Central Time)
    if (lightSensorEnabled && Time.hour() == 18) {
        // The raw value read from the light pin
        int lightSensorValue = analogRead(lightSensorPin);
        // Send event data to Particle Logs
        Particle.publish(lightSensorEventName, String(lightSensorValue));
        // Web Hook trigger to send info into Iris Database
        Particle.publish("Light", String(lightSensorValue), PRIVATE);
    }
    // Wait 1 minute before doing anything else (helps prevent hitting API limits)
    delay(60000);
    // Moisture sensor only runs if it's enabled and it's 2pm UTC time (9am Central Time)
    if (soilMoistureSensorEnabled && Time.hour() == 14) {
        // The raw value read from the moisture pin
        int soilMoistureSensorValue = analogRead(soilMoistureSensorPin);
        // If moisture value is too low, trigger IFTTT to send a text message alert to user
        if (soilMoistureSensorValue < 2200) {
            // Triggers the IFTTT.com recipe alert
            Particle.publish("MoistureLevel", "dry");
            // Triggers web hook for Iris database
            Particle.publish("Moisture", String(soilMoistureSensorValue), PRIVATE);
        } else {
            // Triggers web hook for Iris database
            Particle.publish("Moisture", String(soilMoistureSensorValue), PRIVATE);
        }
        // Send event data to Particle Logs
        Particle.publish(soilMoistureSensorEventName, String(soilMoistureSensorValue));

    }
    // Wait 1 hour and 1 minute before doing anything else. Ensures sensor data is only read
    // once daily
    delay(3600001);
}
