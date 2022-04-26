
//#include "LEDMatrix.h"
int buzzer = 6;
/*
void EvenCols(){
  digitalWrite(COL1, HIGH);
  digitalWrite(COL2, HIGH);
  digitalWrite(COL3, LOW);
  digitalWrite(COL4, HIGH);
  digitalWrite(COL5, HIGH);
  digitalWrite(COL6, LOW);
  digitalWrite(COL7, HIGH);
  digitalWrite(COL8, HIGH);
}
*/


void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
  //Set LED Matrix to output
  //LEDSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  //LightShow();
  tone(buzzer, 880);
}
