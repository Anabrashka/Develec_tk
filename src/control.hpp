#ifndef CONTROL_HPP
#define CONTROL_HPP

void setRelayState(int index, bool state);
void setRGBColor(int red, int green, int blue);
void setupRGB();
void handleButtons();
void handleSerial();

#endif
