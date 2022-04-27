#include "Timer.h"
#include "Levels.h"

enum Player_States { Player_SMStart, Player_On, Player_Off } Player_state;
void TickFct_Player(){
  switch(Player_state) { // Transitions
     case Player_SMStart: // Initial transition
        Player_state = Player_On;
        break;
     case Player_On:
        Player_state= Player_Off;
        break;
     case Player_Off:
        Player_state = Player_On;
        break;
     default:
        Player_state = Player_SMStart;
   } // Transitions

  switch(Player_state) { // State actions
     case Player_On:
        LED31;
        break;
     case Player_Off:
        delay(500);
     default:
        break;
  } // State actions
}

void setup() {
  // put your setup code here, to run once:
  LEDSetup();
  //Player_state = Player_SMStart;
}

void loop() {
  // put your main code here, to run repeatedly:
  level1();
  //TickFct_Player();
}
