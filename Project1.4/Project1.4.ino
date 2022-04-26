//===HEADER FILES===//
#include "LedControl.h"
#include "Levels.h"

//===VARIABLES===//

//General global variables
//initial position
int initCol = 0; 
int initRow = 3;
//current position
int currCol = initCol;
int currRow = initRow;
//final position 
int finalCol = 7;
int finalRow = 4;
//check if specific led is lit up
int litUp = 0;
//determine if level has been won
bool levelWon = 0;
//Keep track of current level
int currLevel = 1;
//Number of total levels
int maxLevel = 5;

//Distinct frequencies to be played by buzzer
const double D5_freq = 587.33;
const double G5_freq = 783.99;
const double A5_freq = 880.00;
const double F5_freq = 698.46;

//   Buttons
const int up = 9;
const int right = 8;
const int down = 7;

//Buzzer
const int buzzer = 6;

//Moves possible 
const int moveUp = 1;
const int moveRight = 1;
const int moveDown = 1;

//flags for seeing which move to do 
bool goUp = 0;
bool goRight = 0;
bool goDown = 0;
//


//===HELPING FUNCTIONS===//

//  Function to display player in specified row and column
void player(int row, int col){
    lc.setLed(0, row, col, 1);
    delay(100);
    lc.setLed(0, row,col, 0);
    delay(100);
}

//===STATE MACHINE FUNCTIONS===//

//This BM_state machine will wait for and capture user input on the buttons
//and then move the LED on the maze accordingly, restarting if wall was hit
enum ButtonMove_BM_states { Button_waitPress, Button_waitRelease, Button_check} BM_state;
void TickFct_ButtonMove(){
  switch(BM_state) { // Transitions
        
     case Button_waitPress: // Initial transition
        if ((digitalRead(right) == LOW) && (digitalRead(up) == LOW) && (digitalRead(down) == LOW) ){
          BM_state = Button_waitPress;  
        }
        else if ((digitalRead(right) == HIGH)){
          goRight = 1;
          BM_state = Button_waitRelease; 
        }
        else if ((digitalRead(up) == HIGH)){
          goUp = 1;
          BM_state = Button_waitRelease;  
        }
        else if ((digitalRead(down) == HIGH)){
          goDown = 1;
          BM_state = Button_waitRelease;  
        }
        else{
          BM_state = Button_waitPress;
        }
        break;
        
     case Button_waitRelease:
        if (goUp){
          if (digitalRead(up) == HIGH){
            BM_state = Button_waitRelease;  
          }
          else{
            BM_state = Button_check;
          }
        }
        else if (goRight){
          if (digitalRead(right) == HIGH){
            BM_state = Button_waitRelease;  
          }
          else{
            BM_state = Button_check; 
          }
        }
        else if (goDown){
          if (digitalRead(down) == HIGH){
            BM_state = Button_waitRelease;  
          }
          else{
            BM_state = Button_check;
          }
        }
        else{
            BM_state = Button_waitPress;
        }
        break;

     case Button_check:
        BM_state = Button_waitPress;
        
     default:
        BM_state = Button_waitPress;
   } // Transitions

  switch(BM_state) { // BM_state actions
     case Button_check:
        if (goUp){
          litUp = lc.getLed(currRow - moveUp, currCol);
          if (litUp || ((currRow - moveUp) < 0)){
            currCol = initCol;
            currRow = initRow;
          }
          else{
            currCol = currCol;
            currRow = currRow - moveUp;  
          }
          goUp = 0;
        }
        else if (goRight){
          litUp = lc.getLed(currRow, currCol + moveRight);
          if (litUp || ((currCol + moveRight) > 7)){
            currCol = initCol;
            currRow = initRow;
          }
          else{
            currCol += moveRight;
            currRow = currRow;  
          } 
          goRight = 0;
        } 
        else if (goDown){
          litUp = lc.getLed(currRow + moveDown, currCol);
          if (litUp || ((currRow + moveDown) > 7)){
            currCol = initCol;
            currRow = initRow;
          }
          else{
            currCol = currCol;
            currRow += moveDown;  
          }
          goDown = 0;
        }        

        if ((currRow == finalRow) && (currCol == finalCol)){
          levelWon = 1; 
          player(currRow, currCol); 
        }
        break;
     default:
        break;
  } // BM_state actions
 // return BM_state;
}

enum LevelWon_States { LW_celebration } LW_state;
void TickFct_LevelWon(){
  switch(LW_state) { // Transitions
     case LW_celebration: // Initial transition
        LW_state = LW_celebration;
        break;
        
     default:
        LW_state = LW_celebration;
   } // Transitions

  switch(LW_state) { // BM_state actions
     case LW_celebration:
        lc.clearDisplay(0);
        tone(buzzer, G5_freq);
        lc.setRow(0,0,c1[0]);
    lc.setRow(0,1,c1[1]);
    lc.setRow(0,2,c1[2]);
    lc.setRow(0,3,c1[3]);
    lc.setRow(0,4,c1[4]);
    lc.setRow(0,5,c1[5]);
    lc.setRow(0,6,c1[6]);
    lc.setRow(0,7,c1[7]);

    delay(300);
    
    tone(buzzer, F5_freq);
    lc.setRow(0,0,c2[0]);
    lc.setRow(0,1,c2[1]);
    lc.setRow(0,2,c2[2]);
    lc.setRow(0,3,c2[3]);
    lc.setRow(0,4,c2[4]);
    lc.setRow(0,5,c2[5]);
    lc.setRow(0,6,c2[6]);
    lc.setRow(0,7,c2[7]);

    delay(300);

    tone(buzzer, D5_freq);
    lc.setRow(0,0,c3[0]);
    lc.setRow(0,1,c3[1]);
    lc.setRow(0,2,c3[2]);
    lc.setRow(0,3,c3[3]);
    lc.setRow(0,4,c3[4]);
    lc.setRow(0,5,c3[5]);
    lc.setRow(0,6,c3[6]);
    lc.setRow(0,7,c3[7]);

    delay(300);

    tone(buzzer, A5_freq);
    lc.setRow(0,0,c4[0]);
    lc.setRow(0,1,c4[1]);
    lc.setRow(0,2,c4[2]);
    lc.setRow(0,3,c4[3]);
    lc.setRow(0,4,c4[4]);
    lc.setRow(0,5,c4[5]);
    lc.setRow(0,6,c4[6]);
    lc.setRow(0,7,c4[7]);

    delay(800);
    noTone(buzzer);       
        break;
     default:
        break;
  } // BM_state actions
 // return BM_state;
}


//===SETUP===//
void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  // Make sure display is not in shutdown mode
  lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,5);
  // Clear the display
  lc.clearDisplay(0); 

  // Set Buttons as INPUT
  pinMode(up, INPUT);
  pinMode(right, INPUT);
  pinMode(down, INPUT);

  // Set buzzer as output
  pinMode(buzzer, OUTPUT);

  //set initial states for SMs
  BM_state = Button_waitPress;
  LW_state = LW_celebration;

}

//===LOOP===//
void loop() {
  // put your main code here, to run repeatedly:]
  if (!levelWon){
    levels(currLevel);
    player(currRow, currCol);
    TickFct_ButtonMove();
  }
  else{
    TickFct_LevelWon();
    delay(500);
    levelWon = 0;
    currRow = initRow;
    currCol = initCol;
    if (currLevel < maxLevel){
      currLevel++;    
    }
    else{
      currLevel = 1; 
    } 
 
  }
}
