/*  Author: Zergio Ruvalcaba
 *  Lab Section: 21
 *  Assignment: Project 1
 *
 *  Project Description: Welcome to Labitynth! This is an arcade-like game implemented
 *  on the Arduino Uno, using an 8x8 LED Matrix with the MAX7219.
 *  The objective of the game is to traverse the LED maze from left to right without touching the lit LEDs
 *  or going out of bounds of the matrix. The player can move to the left, up, or down.
 *  The player is represented by a rapidly blinking LED, while the exit the is represented 
 *  by a slowly blinking LED. This version of the game has 5 levels.
 *  The player is given 3 lives for the game. If the player does an invalid move, a life is taken. 
 *  If the player ends up with no lives, the game restarts. If the player gets through all the levels
 *  without loosing all their lives, they win the game and it restarts. 
 *  To begin the game press any button.
 *
 *  I acknowledge all content contained herein, excluding template, provided code, or example
 *  code, is my own original work.
 *  
 *  Demo Link: <>
 *  GitHub Repo: <https://github.com/Zorten/Labitynth>
 */




//======HEADER FILES======//

//I used this library to control my LED Matrix. Obtained from here: <https://www.arduino.cc/reference/en/libraries/ledcontrol/>
#include "LedControl.h"

//I created this header file to hold values and functions that would clutter this code
#include "Levels.h"

//======HEADER FILES END======//

//======VARIABLES======//

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

//initial level
int initLevel = 1;

//keep track of current level
int currLevel = initLevel;

//total number of levels
int maxLevel = 5;

//distinct frequencies to be played by buzzer
const double F4_freq = 349.228;
const double D5_freq = 587.33;
const double F5_freq = 698.46;
const double G5_freq = 783.99;
const double A5_freq = 880.00;

//buttons
const int up = 9;
const int right = 8;
const int down = 7;

//buzzer
const int buzzer = 6;

//possible moves
const int moveUp = 1;
const int moveRight = 1;
const int moveDown = 1;

//flags for seeing which move to do 
bool goUp = 0;
bool goRight = 0;
bool goDown = 0;

//flag for seeing if button was pressed to start game
bool menuButton = 0;

//determine if game is over
bool gameOver = 0;

//keep track of lives
int lives = 3;

//total number of lives
int maxLives = 3;

//flags to see if wrong/correct move was made
bool wrongMove = 0;
bool validMove = 0;

//used to determine when to toggle exit LED
int loops = 5;

//used to blink exit LED
int toggle = 1;

//to keep track of menu Display
int circleUp = 1;
int circleDown = 4;

//determine if game should start
bool gameStart = 0;

//======END VARIABLES======//


//======HELPER FUNCTIONS======//

//  Function to display player in specified row and column
//  Also blinks the exit
void player(int row, int col){
    loops--;
    if (loops <= 0){
      toggle = !toggle;
      lc.setLed(0, finalRow, finalCol, toggle);
      loops = 5;
        
    }
    lc.setLed(0, row, col, 1);
    delay(100);
    lc.setLed(0, row,col, 0);
    delay(100);
}

//======HELPER FUNCTIONS END======//

//======STATE MACHINE FUNCTIONS======//


//This state machine will wait for and capture
//user input on the Menu and then begin the game
//If no input, the state machine will display a light show on the matrix
enum Menu_states { Menu_waitPress, Menu_waitRelease, Menu_start} Menu_state;
void TickFct_Menu(){
  switch(Menu_state) { // Transitions
        
     case Menu_waitPress: // Initial transition - wait for user to press button
        if ((digitalRead(right) == LOW) && (digitalRead(up) == LOW) && (digitalRead(down) == LOW) ){
          Menu_state = Menu_waitPress;  
        }
        else if ((digitalRead(right) == HIGH) || (digitalRead(up) == HIGH) || (digitalRead(down) == HIGH)){
          Menu_state = Menu_waitRelease; 
        }
        else{
          Menu_state = Menu_waitPress;
        }
        break;
        
     case Menu_waitRelease: //wait for user to release button
        if ((digitalRead(right) == HIGH) || (digitalRead(up) == HIGH) || (digitalRead(down) == HIGH)){
          Menu_state = Menu_waitRelease;  
        }
        else{
          Menu_state = Menu_start;
        }

        break;

     case Menu_start: //after veryfing press, go back to waiting for input
        Menu_state = Menu_waitPress;
        
     default:
        Menu_state = Menu_waitPress;
   } // Transitions

  switch(Menu_state) { // state actions
     //display light show while no input
     case Menu_waitPress:
        if (circleUp <= 4 ){
          circles(circleUp);
          delay(50);
          circleUp++; 
        }
        else{
          circles(circleDown);
          delay(50);
          circleDown--;
          if (circleDown == 0){
              circleUp = 1;
              circleDown = 4;  
          }  
        }
        break;

     case Menu_waitRelease:
        //clear display after button to start has been pressed
        lc.clearDisplay(0);
        break;
        
     case Menu_start:
        //set flag to begin game
        gameStart = 1;
        tone(buzzer, F5_freq); 
        delay(50);
        noTone(buzzer);
        break;
     default:
        break;
  } //state actions
}


//This state machine will wait for and capture user input on the buttons
//and then move the LED on the maze accordingly, restarting if wall was hit or went out of bounds
enum ButtonMove_BM_states { Button_waitPress, Button_waitRelease, Button_check} BM_state;
void TickFct_ButtonMove(){
  switch(BM_state) { // Transitions
        
     case Button_waitPress: // Initial transition - wait for user to press button
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
        
     case Button_waitRelease: //wait for user to release button
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

  switch(BM_state) { // state actions
     case Button_check: //check which button was pressed and respond accordingly
        if (goUp){
          //litUp is 1 if the LED you're trying to move to is on
          litUp = lc.getLed(currRow - moveUp, currCol);
          //if the LED is on or if it is out of bounds, 
          //move player to starting position and mark a wrong move
          if (litUp || ((currRow - moveUp) < 0)){
            currCol = initCol;
            currRow = initRow;
            wrongMove = 1;
            
          }
          //otherwise move player to specified spot and mark a valid move
          else{
            currCol = currCol;
            currRow = currRow - moveUp;
            validMove = 1;  
          }
          goUp = 0; //reset flag
        }
        else if (goRight){
          litUp = lc.getLed(currRow, currCol + moveRight);
          if (litUp || ((currCol + moveRight) > 7)){
            currCol = initCol;
            currRow = initRow;
            wrongMove = 1;
          }
          else{
            currCol += moveRight;
            currRow = currRow;  
            validMove = 1;
          } 
          goRight = 0;
        } 
        else if (goDown){
          litUp = lc.getLed(currRow + moveDown, currCol);
          if (litUp || ((currRow + moveDown) > 7)){
            currCol = initCol;
            currRow = initRow;
            wrongMove = 1;
          }
          else{
            currCol = currCol;
            currRow += moveDown;
            validMove = 1;  
          }
          goDown = 0;
        }    

        if (wrongMove){ //take a life and play tune to indicate invalid move
          wrongMove = 0;
          lives--;
          tone(buzzer, F5_freq);
          delay(100);
          tone(buzzer, G5_freq);
          delay(100);
          noTone(buzzer);  
        }

        if (validMove){ //play a tune when valid move is made
          validMove = 0;
          tone(buzzer, F5_freq); 
          delay(50);
          noTone(buzzer); 
        }

        //check if user has lost all lives and restart game if so
        if (lives <= 0){
           gameOver = 1;
           delay(500);          
        }
            
        //check if the player has reached the exit, and if so set the levelWon flag
        //and return player to starting positon
        if ((currRow == finalRow) && (currCol == finalCol)){
          levelWon = 1; 
        }
        break;
     default:
        break;
  } //state actions
}


//This function displays a little animation and plays
//a tune to indicate level was passed.
//Only one state since animation needs to play at once.
enum LevelWon_States { LW_celebration } LW_state;
void TickFct_LevelWon(){
  switch(LW_state) { // Transitions
     case LW_celebration: // Initial transition
        LW_state = LW_celebration;
        break;
        
     default:
        LW_state = LW_celebration;
   } // Transitions

  switch(LW_state) { // state actions
     case LW_celebration:
        lc.clearDisplay(0);
        tone(buzzer, A5_freq);
        circle1();
        delay(500);
        lc.clearDisplay(0);
        tone(buzzer, D5_freq);
        circle2();
        delay(500);
        lc.clearDisplay(0);
        tone(buzzer, F5_freq);
        circle3();
        delay(500);
        lc.clearDisplay(0);
        tone(buzzer, G5_freq);
        circle4();
        delay(500);
        noTone(buzzer); 
        lc.clearDisplay(0);      
        break;
     default:
        break;
  } // BM_state actions
}

//This function shows a message telling the user they won and plays a tune
enum GameWon_States { GW_celebration } GW_state;
void TickFct_GameWon(){
  switch(GW_state) { // Transitions
     case GW_celebration: // Initial transition
        GW_state = GW_celebration;
        break;
        
     default:
        GW_state = GW_celebration;
   } // Transitions

  switch(GW_state) { // state actions
     case GW_celebration:
        lc.clearDisplay(0);
        tone(buzzer, G5_freq);
        charU();
        delay(800);
        lc.clearDisplay(0);
        tone(buzzer, F5_freq);
        charW();
        delay(800);
        lc.clearDisplay(0);
        tone(buzzer, D5_freq);
        charO();
        delay(800);
        lc.clearDisplay(0);
        tone(buzzer, A5_freq);
        charN();
        delay(800);
        lc.clearDisplay(0);
        tone(buzzer, A5_freq);
        happyFace();
        delay(1000);
        noTone(buzzer); 
        lc.clearDisplay(0);      
        break;
     default:
        break;
  } //state actions
}

//This function tells the user they lost, and plays a tune
enum GameLost_States { GL_lost } GL_state;
void TickFct_GameLost(){
  switch(GL_state) { // Transitions
     case GL_lost: // Initial transition
        GL_state = GL_lost;
        break;
        
     default:
        GL_state = GL_lost;
   } // Transitions

  switch(GL_state) { // state actions
     case GL_lost:
        lc.clearDisplay(0);
        tone(buzzer, A5_freq);
        circle4();
        delay(500);
        lc.clearDisplay(0);
        tone(buzzer, G5_freq);
        circle3();
        delay(500);
        lc.clearDisplay(0);
        tone(buzzer, F5_freq);
        circle2();
        delay(500);
        lc.clearDisplay(0);
        tone(buzzer, D5_freq);
        circle1();
        delay(800);
        lc.clearDisplay(0);
        tone(buzzer, D5_freq);
        sadFace();
        delay(500);
        noTone(buzzer); 
        lc.clearDisplay(0);      
        break;
     default:
        break;
  } //state actions
}

//======STATE MACHINE FUNCTIONS END======//

//======SETUP======//
void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  
  // Make sure display is not in shutdown mode
  lc.shutdown(0,false);
  
  // Set brightness to a low value to minimize power consumption
  lc.setIntensity(0,3);
  
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
  Menu_state = Menu_waitPress;
  GW_state = GW_celebration;
  GL_state = GL_lost;

}
//======END SETUP======//


//======LOOP======//
void loop() {
  // put your main code here, to run repeatedly:

  //run menu function as long as game hasn't started (no input)
  if (!gameStart){
    TickFct_Menu();  
  }
  else{
    //as long as the game is not over, iterate over the levels 
    if (!gameOver){
      if (!levelWon){
        //as long as level isn't won, call ButtonMove function and adjust position  
        levels(currLevel);
        TickFct_ButtonMove();
        player(currRow, currCol);
      }
      else{
        //if not final level, move on to next level and update postion
        if (currLevel < maxLevel){
          TickFct_LevelWon();
          levelWon = 0;
          currRow = initRow;
          currCol = initCol;
          currLevel++;    
        }
        //if final level passed, display winning message and end game
        else if (currLevel == maxLevel){
          TickFct_LevelWon();
          delay(250);
          TickFct_GameWon();
          delay(500);
          lc.clearDisplay(0);
          currLevel = initLevel;
          gameStart = 0;
        }

        //update variables
        levelWon = 0;
        currRow = initRow;
        currCol = initCol;
      }
    }
    else{
      //if game is lost, update variables to restart and display losing message
      gameOver = 0;
      lives = 3;
      currLevel = initLevel;
      currRow = initRow;
      currCol = initCol;
      levelWon = 0;
      gameStart = 0;
      TickFct_GameLost();
      delay(250);
    }
  }
}
//======END LOOP======//
