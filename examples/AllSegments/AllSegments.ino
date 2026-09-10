#include <CH462x.h>
CH462x lcd(21,20,18,19);
void setup(){lcd.begin();}
void loop(){lcd.allOn();delay(3000);lcd.clear();delay(1000);} 
