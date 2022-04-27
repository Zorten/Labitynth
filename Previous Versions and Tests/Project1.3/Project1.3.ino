//===HEADER FILES===//
#include "LedControl.h"
#include "Levels.h"

//===VARIABLES===//

//General global variables
//initial position
int initCol = 0; 
int initRow = 3;
//current position
int currCol = 0;
int currRow = 3;
//final position 
int finalCol = 7;
int finalRow = 4;
//check if specific led is lit up
int litUp = 0;
//determine if level has been won
bool levelWon = 0;

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
        if ((digitalRead(right1) == LOW) && (digitalRead(up1) == LOW) && (digitalRead(down1) == LOW) && (digitalRead(right2) == LOW) && (digitalRead(up2) == LOW) && (digitalRead(down2) == LOW) ){
          BM_state = Button_waitPress;  
        }
        else if ((digitalRead(right1) == HIGH)){
          goRight1 = 1;
          BM_state = Button_waitRelease; 
        }
        else if ((digitalRead(up1) == HIGH)){
          goUp1 = 1;
          BM_state = Button_waitRelease;  
        }
        else if ((digitalRead(down1) == HIGH)){
          goDown1 = 1;
          BM_state = Button_waitRelease;  
        }
        else if ((digitalRead(right2) == HIGH)){
          goRight2 = 1;
          BM_state = Button_waitRelease; 
        }
        else if ((digitalRead(up2) == HIGH)){
          goUp2 = 1;
          BM_state = Button_waitRelease;  
        }
        else if ((digitalRead(down2) == HIGH)){
          goDown2 = 1;
          BM_state = Button_waitRelease;  
        }
        else{
          BM_state = Button_waitPress;
        }
        break;
        
     case Button_waitRelease:
        if (goUp1){
          if (digitalRead(up1) == HIGH){
            BM_state = Button_waitRelease;  
          }
          else{
            BM_state = Button_check;
          }
        }
        else if (goRight1){
          if (digitalRead(right1) == HIGH){
            BM_state = Button_waitRelease;  
          }
          else{
            BM_state = Button_check; 
          }
        }
        else if (goDown1){
          if (digitalRead(down1) == HIGH){
            BM_state = Button_waitRelease;  
          }
          else{
            BM_state = Button_check;
          }
        }
        if (goUp2){
          if (digitalRead(up2) == HIGH){
            BM_state = Button_waitRelease;  
          }
          else{
            BM_state = Button_check;
          }
        }
        else if (goRight2){
          if (digitalRead(right2) == HIGH){
            BM_state = Button_waitRelease;  
          }
          else{
            BM_state = Button_check; 
          }
        }
        else if (goDown2){
          if (digitalRead(down2) == HIGH){
            BM_state = Button_waitRelease;  
          }
          else{
            BM_state = Button_check;
          }
        }
        break;

     case Button_check:
        BM_state = Button_waitPress;
        
     default:
        BM_state = Button_waitPress;
   } // Transitions

  switch(BM_state) { // BM_state actions
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
          litUp = lc.getLed(currRow, currCol + moveRight1);
          Serial.print(litUp);
          if (litUp){
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
        if (goUp2){
          litUp = lc.getLed(currRow - moveUp2, currCol);
          if (litUp){
            currCol = initCol;
            currRow = initRow;
          }
          else{
            currCol = currCol;
            currRow = currRow - moveUp2;  
          }
          goUp2 = 0;
        }
        else if (goRight2){
          litUp = lc.getLed(currRow, currCol + moveRight2);
          if (litUp){
            currCol = initCol;
            currRow = initRow;
          }
          else{
            currCol += moveRight2;
            currRow = currRow;  
          } 
          goRight2 = 0;
        } 
        else if (goDown2){
          litUp = lc.getLed(currRow + moveDown2, currCol);
          if (litUp){
            currCol = initCol;
            currRow = initRow;
          }
          else{
            currCol = currCol;
            currRow += moveDown2;  
          }
          goDown1 = 0;
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
        celebration();        
        break;
     default:
        break;
  } // BM_state actions
 // return BM_state;
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
  BM_state = Button_waitPress;
  LW_state = LW_celebration;

}

//===LOOP===//
void loop() {
  // put your main code here, to run repeatedly:]
  // Display level1();
  if (!levelWon){
    level1();
    player(currRow, currCol);
    TickFct_ButtonMove();
  }
  else{
    TickFct_LevelWon();
    //levelWon = 0;  
  }
}
