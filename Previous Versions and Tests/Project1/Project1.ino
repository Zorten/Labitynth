#include "Timer.h"
#include "Levels.h"

typedef struct task {
  int state; // Current state of the task
  unsigned long period; // Rate at which the task should tick
  unsigned long elapsedTime; // Time since task's previous tick
  int (*TickFct)(int); // Function to call for task's tick
} task;

task tasks[1];

const unsigned char tasksNum = 1;
const unsigned long tasksPeriodGCD = 50;
const unsigned long periodPlayer = 500;
const unsigned long periodLevel = 100;

enum Player_States { Player_SMStart, Player_On, Player_Off };
int TickFct_Player(int state){
  switch(state) { // Transitions
     case Player_SMStart: // Initial transition
        state = Player_On;
        break;
     case Player_On:
        state = Player_Off;
        break;
     case Player_Off:
        state = Player_On;
        break;
     default:
        state = Player_SMStart;
   } // Transitions

  switch(state) { // State actions
     case Player_On:
        LED31;
        break;
     case Player_Off:
        LEDoff();
     default:
        break;
  } // State actions
  return state;
}

enum Level_States { Level_SMStart, Level_On};
int TickFct_Level(int state){
  switch(state) { // Transitions
     case Level_SMStart: // Initial transition
        state = Level_On;
        break;
     case Level_On:
        state = Level_On;
        break;
     default:
        state = Level_SMStart;
   } // Transitions

  switch(state) { // State actions
     case Level_SMStart:
        break;
     case Level_On:
        level1();
     default:
        break;
  } // State actions
  return state;
}

void setup() {
  // put your setup code here, to run once:
  LEDSetup();

  unsigned char i=0;
  /*
  tasks[i].state = Player_SMStart;
  tasks[i].period = periodPlayer;
  tasks[i].elapsedTime = tasks[i].period;
  tasks[i].TickFct = &TickFct_Player;
  
  ++i;
  */
  tasks[i].state = Level_SMStart;
  tasks[i].period = periodLevel;
  tasks[i].elapsedTime = tasks[i].period;
  tasks[i].TickFct = &TickFct_Level;
  

  TimerSet(tasksPeriodGCD);
  TimerOn();

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) { // Heart of the scheduler code
     if ( tasks[i].elapsedTime >= tasks[i].period ) { // Ready
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = 0;
     }
     while (!TimerFlag){}   // Wait for timer period
     TimerFlag = 0;         // Lower flag raised by timer
     tasks[i].elapsedTime += tasksPeriodGCD;
  }
}
