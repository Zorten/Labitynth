#include "LedControl.h"
#include "Levels.h"
const int button = 4;
int buttonState = 0;

void player(int row, int col){
    lc.setLed(0, row, col, 1);
    delay(200);
    lc.setLed(0, row,col, 0);
    delay(200);
}

// sad face
byte sf[8]= {B00111100,B01000010,B10100101,B10000001,B10011001,B10100101,B01000010,B00111100};

//happy
byte hf[8]= {B00111100,B01000010,B10100101,B10000001,B10100101,B10011001,B01000010,B00111100};


void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,5);
  // Clear the display
  lc.clearDisplay(0); 

  pinMode(button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:]
  buttonState = digitalRead(button);

  if (buttonState == LOW){
    // Display happy face
    level1();
    player(3, 0);
  }else{
    lc.clearDisplay(0);
    
  }
}
