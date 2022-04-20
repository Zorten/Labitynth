//===HEADER FILES===//
#include "LedControl.h"
#include "Levels.h"

//===VARIABLES===//
int buttonState = 0;
int initCol = 0;
int initRow = 3;
int currCol = 0;
int currRow = 3;
int litUp = 0;

//   Buttons
const int up1 = 9;
const int up2 = 8;
const int right1 = 7;
const int right2 = 6;
const int down1 = 5;
const int down2 = 4;

//Moves possible 
const int moveUp1 = 1;
const int moveUp2 = 1;
const int moveRight1 = 1;
const int moveRight2 = 1;
const int moveDown1 = 1;
const int moveDown2 = 1;

//flags for seeing which move to do 
bool goUp1 = 0;
bool goUp2 = 0;
bool goRight1 = 0;
bool goRight2 = 0;
bool goDown1 = 0;
bool goDown2 = 0;


//===HELPING FUNCTIONS===//

//  Function to display player in specified row and column
void player(int row, int col){
    lc.setLed(0, row, col, 1);
    delay(100);
    lc.setLed(0, row,col, 0);
    delay(100);
}

//===STATE MACHINE FUNCTIONS===//

//This state machine will wait for and capture user input on the buttons
//and then moves the LED on the maze accordingly, restarting if wall was hit
enum Button_States { Button_SMStart, Button_waitPress, Button_waitRelease, Button_check} state;
void TickFct_Button(){
  switch(state) { // Transitions
     case Button_SMStart: // Initial transition
        state = Button_waitPress;
        break;
        
     case Button_waitPress:
        if ((digitalRead(right1) == LOW) && (digitalRead(up1) == LOW) && (digitalRead(down1) == LOW) ){
          state = Button_waitPress;  
        }
        else if ((digitalRead(right1) == HIGH)){
          goRight1 = 1;
          state = Button_waitRelease; 
        }
        else if ((digitalRead(up1) == HIGH)){
          goUp1 = 1;
          state = Button_waitRelease;  
        }
        else if ((digitalRead(down1) == HIGH)){
          goDown1 = 1;
          state = Button_waitRelease;  
        }
        else{
          state = Button_waitPress;
        }
        break;
        
     case Button_waitRelease:
        if (goUp1){
          if (digitalRead(up1) == HIGH){
            state = Button_waitRelease;  
          }
          else{
            state = Button_check;
          }
        }
        else if (goRight1){
          if (digitalRead(right1) == HIGH){
            state = Button_waitRelease;  
          }
          else{
            state = Button_check; 
          }
        }
        else if (goDown1){
          if (digitalRead(down1) == HIGH){
            state = Button_waitRelease;  
          }
          else{
            state = Button_check;
          }
        }
        else{
            
        }
        break;

     case Button_check:
        state = Button_waitPress;
        
     default:
        state = Button_SMStart;
   } // Transitions

  switch(state) { // State actions
     case Button_check:
        if (goUp1){
          litUp = lc.getLed(currRow - moveUp1, currCol);
          if (litUp){
            currCol = initCol;
            currRow = initRow;
          }
          else{
            currCol = currCol;
            currRow = currRow - moveUp1;  
          }
          goUp1 = 0;
        }
        else if (goRight1){
         // litUp = ;
          if (lc.getLed(currRow, currCol + moveRight1)){
            currCol = initCol;
            currRow = initRow;
          }
          else{
            currCol += moveRight1;
            currRow = currRow;  
          } 
          goRight1 = 0;
        } 
        else if (goDown1){
          litUp = lc.getLed(currRow + moveDown1, currCol);
          if (litUp){
            currCol = initCol;
            currRow = initRow;
          }
          else{
            currCol = currCol;
            currRow += moveDown1;  
          }
          goDown1 = 0;
        }
        break;
     default:
        break;
  } // State actions
 // return state;
}


//===SETUP===//
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Make sure display is not in shutdown mode
  lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,5);
  // Clear the display
  lc.clearDisplay(0); 

  // Set Buttons as INPUT
  pinMode(up1, INPUT);
  pinMode(up2, INPUT);
  pinMode(right1, INPUT);
  pinMode(right2, INPUT);
  pinMode(down1, INPUT);
  pinMode(down2, INPUT);

  //set initial states for SMs
  state = Button_SMStart;

}

//===LOOP===//
void loop() {
  // put your main code here, to run repeatedly:]
  // Display level1();
  level1();
  player(currRow, currCol);
  TickFct_Button();
}
