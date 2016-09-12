const bool lightSensorEnabled = false;
const bool soilMoistureSensorEnabled = false;
const bool temperatureSensorEnabled = true;

const int lightSensorPin = A0;
const int soilMoistureSensorPin = A1;
const int temperatureSensorPin = A2;

const String lightSensorEventName = "iris.light";
const String soilMoistureSensorEventName = "iris.soilMoisture";
const String temperatureSensorEventName = "iris.temperature";

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

void loop() {
    if (lightSensorEnabled) {
        int lightSensorValue = analogRead(lightSensorPin);
        Particle.publish(lightSensorEventName, String(lightSensorValue));
    }

    if (soilMoistureSensorEnabled) {
        int soilMoistureSensorValue = analogRead(soilMoistureSensorPin);
        Particle.publish(soilMoistureSensorEventName, String(soilMoistureSensorValue));
    }
    if (temperatureSensorEnabled) {
        int temperatureSensorValue = analogRead(temperatureSensorPin);
        Particle.publish(temperatureSensorEventName, String(temperatureSensorValue));
    }

    delay(1000);
}
