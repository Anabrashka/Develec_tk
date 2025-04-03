#include <Arduino.h>
#include "control.hpp"
#include "mqtt.hpp"
#include "CONFIG.hpp"

const int RELAY_PINS[5] = {32, 33, 25, 26, 27};
const int BUTTON_PINS[5] = {36, 39, 34, 35, 4};

bool relayStates[5] = {false, false, false, false, false};
bool lastButtonStates[5] = {false, false, false, false, false};

void setRelayState(int index, bool state) {
    relayStates[index] = state;
    digitalWrite(RELAY_PINS[index], state ? HIGH : LOW);
    publishRelayState(index, state);
}

void setRGBColor(int red, int green, int blue) {
    ledcWrite(0, red);
    ledcWrite(1, green);
    ledcWrite(2, blue);
}

void setupRGB() {
    ledcSetup(0, 5000, 8);
    ledcAttachPin(14, 0); // Rojo
    ledcSetup(1, 5000, 8);
    ledcAttachPin(16, 1); // Verde
    ledcSetup(2, 5000, 8);
    ledcAttachPin(5, 2);  // Azul
}

void handleButtons() {
    for (int i = 0; i < 5; i++) {
        bool currentState = digitalRead(BUTTON_PINS[i]) == LOW;
        if (currentState && !lastButtonStates[i]) {
            bool newState = !relayStates[i];
            setRelayState(i, newState);
            publishButtonState(i + 1);
        }
        lastButtonStates[i] = currentState;
    }
}

void handleSerial() {
}
