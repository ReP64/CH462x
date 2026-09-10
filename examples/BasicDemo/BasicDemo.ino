#include <CH462x.h>
CH462x lcd(21,20,18,19);
void setup(){lcd.begin();lcd.blOn();}
void loop(){lcd.show("1234.56");delay(2000);lcd.show("PASS");delay(2000);} 
