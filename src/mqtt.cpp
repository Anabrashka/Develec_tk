#include <Arduino.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "mqtt.hpp"
#include "CONFIG.hpp"
#include "control.hpp"
#include <ArduinoJson.h>


WiFiClient espClient;
PubSubClient mqttClient(espClient);

const char* mqtt_server = "192.168.100.28";
const int mqtt_port = 1883;

void callback(char* topic, byte* payload, unsigned int length) {
    String msg;
    for (unsigned int i = 0; i < length; i++) {
        msg += (char)payload[i];
    }
    Serial.printf("Mensaje recibido [%s]: %s\n", topic, msg.c_str());

    for (int i = 1; i <= 5; i++) {
        String relayTopic = String(DEVICE_ID) + "/relay/" + String(i);
        if (String(topic) == relayTopic) {
            // Decodificar mensaje JSON
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, msg);
        
            const char* state = doc["state"];
            if (String(state) == "ON") {
                setRelayState(i - 1, true);
            } else if (String(state) == "OFF") {
                setRelayState(i - 1, false);
            }
        }
    }

    String rgbTopic = String(DEVICE_ID) + "/rgb";
    if (String(topic) == rgbTopic) {
        // Decodificar mensaje JSON
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, msg);
    
        int r = doc["r"];
        int g = doc["g"];
        int b = doc["b"];
    
        setRGBColor(r, g, b);
        publishRGBState(r, g, b);
    }
    
}

void connectMQTT() {
    mqttClient.setServer(mqtt_server, mqtt_port);
    mqttClient.setCallback(callback);

    Serial.println("Conectando a EMQX...");
    if (mqttClient.connect(DEVICE_ID, MQTT_USER, MQTT_PASSWORD)) {
        Serial.println("Conectado a EMQX");
        mqttClient.subscribe((String(DEVICE_ID) + "/#").c_str());
    } else {
        Serial.print("Error MQTT: ");
        Serial.println(mqttClient.state());
    }
}

void handleMQTT() {
    if (!mqttClient.connected()) {
        connectMQTT();
    }
    mqttClient.loop();
}

void publishRelayState(int index, bool state) {
    String topic = String(DEVICE_ID) + "/relay/" + String(index + 1) + "/state";
    
    // Crear el mensaje en formato JSON
    String payload = "{\"state\": \"" + String(state ? "ON" : "OFF") + "\"}";
    
    mqttClient.publish(topic.c_str(), payload.c_str());
}

void publishButtonState(int buttonIndex) {
    String topic = String(DEVICE_ID) + "/button/" + String(buttonIndex);
    String payload = "pressed";
    mqttClient.publish(topic.c_str(), payload.c_str());
}

void publishRGBState(int r, int g, int b) {
    String topic = String(DEVICE_ID) + "/rgb/state";
    
    // Crear el mensaje en formato JSON
    String payload = "{\"r\": " + String(r) + ", \"g\": " + String(g) + ", \"b\": " + String(b) + "}";
    
    mqttClient.publish(topic.c_str(), payload.c_str());
}

