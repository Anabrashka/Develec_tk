#include <WiFi.h>
#include "CONFIG.hpp"

void connectWiFi() {
    Serial.println("Conectando a WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Conectado! IP: ");
    Serial.println(WiFi.localIP());
}
