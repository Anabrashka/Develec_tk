#include <Arduino.h>
#include <ArduinoJson.h>
#include "wifi.hpp"
#include "mqtt.hpp"
#include "control.hpp"
#include "CONFIG.hpp"
#include "pins.hpp"


void setup() {
    Serial.begin(115200);
    connectWiFi();
    connectMQTT();

    for (int i = 0; i < 5; i++) {
        pinMode(RELAY_PINS[i], OUTPUT);
        pinMode(BUTTON_PINS[i], INPUT_PULLUP);
    }

    pinMode(14, OUTPUT); // Rojo
    pinMode(16, OUTPUT); // Verde
    pinMode(5, OUTPUT);  // Azul

    setupRGB(); // PWM configuración
}

void loop() {
    handleMQTT();
    handleButtons();
}
