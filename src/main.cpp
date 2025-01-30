#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#ifdef WIFI_SSID
#include secrets.h 
#else
#error "Misssing secrets.h file ! Create it and define WIFI_SSID and WIFI_PASSWORD"
#endif 

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* mqtt_server = "broker.hivemq.com";
const char* unique_identifier = "sunfounder-client-sdgvsda";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;

const int ledPin = 32;
const int buttonPin = 14;
#define DHTPIN 26
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); // DHT11 sensor connected to GPIO 26

void setup() {
    Serial.begin(9600);

    dht.begin();

    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    pinMode(buttonPin, INPUT);
    pinMode(ledPin, OUTPUT);
}

void setup_wifi() {
    Serial.println("\nConnecting to WiFi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++) {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();

    if (String(topic) == "LED") {
        Serial.print("Changing LED state to ");
        if (messageTemp == "on") {
            Serial.println("on");
            digitalWrite(ledPin, HIGH);
        } else if (messageTemp == "off") {
            Serial.println("off");
            digitalWrite(ledPin, LOW);
        }
    }
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect(unique_identifier)) {
            Serial.println("connected");
            client.subscribe("LED");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" retrying in 5 seconds");
            delay(5000);
        }
    }
}

float dht11_sensor() {
    float temperature = dht.readTemperature();
    if (!isnan(temperature)) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" °C");
        return temperature;
    } else {
        Serial.println("Error reading from DHT11 sensor.");
        return -999; // Error code for invalid temperature
    }
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    if (digitalRead(buttonPin)) {
        long now = millis();
        if (now - lastMsg > 5000) {
            lastMsg = now;
            float temperature = dht11_sensor();
            if (temperature != -999) {
                char tempString[8];
                dtostrf(temperature, 1, 2, tempString);
                client.publish("TEMPO", tempString);
            }
        }
    }
}