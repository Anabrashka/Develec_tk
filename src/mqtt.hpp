#ifndef MQTT_HPP
#define MQTT_HPP

void connectMQTT();
void handleMQTT();
void publishRelayState(int index, bool state);
void publishButtonState(int buttonIndex);
void publishRGBState(int r, int g, int b);

#endif
