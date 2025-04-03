# Develec_ESP32_MQTT_JSON

Este proyecto controla un sistema de relays y un LED RGB utilizando MQTT y JSON para la comunicación. Es ideal para controlar dispositivos de forma remota desde plataformas como Unity o Node-RED.

## Funcionalidades
- Control de **relays** (encendido y apagado).
- Control de **LED RGB** con PWM (intensidad y color).
- Publicación de estados en formato **JSON** para estandarizar la comunicación.

## Instalación
1. Clona este repositorio:
   ```bash
   git clone https://github.com/tu_usuario/Develec_ESP32_MQTT_JSON.git
    Abre el proyecto en PlatformIO (VSCode).

    Configura tus credenciales de WiFi y MQTT en CONFIG.hpp.

    Conecta el ESP32 y sube el código.

Uso

Envía comandos MQTT con el siguiente formato:
Para encender un relay:

      { "state": "ON" }


Para cambiar el color del LED RGB:

    { "r": 255, "g": 0, "b": 0 }


---
