#include <CH462x.h>
CH462x lcd(21,20,18,19);
void setup(){lcd.begin();}
void loop(){lcd.setKg();delay(1000);lcd.clearIndicators();lcd.setNet();delay(1000);lcd.clearIndicators();}
