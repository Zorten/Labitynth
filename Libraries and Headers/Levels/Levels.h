/*
* I made this header file to hold functions that would have clogged
* the code in the main implementation file.
*/


using namespace std;
#include "../LedControl/src/LedControl.h" //include library



//initialize LED matrix
LedControl lc = LedControl(12, 11, 10, 1);

//level 1 display
byte l1[8]= {B11111111,B11111111,B11110001,B00010101,B11000100,B11111111,B11111111,B11111111};
void level1(){
    lc.setRow(0,0,l1[0]);
    lc.setRow(0,1,l1[1]);
    lc.setRow(0,2,l1[2]);
    lc.setRow(0,3,l1[3]);
    lc.setRow(0,4,l1[4]);
    lc.setRow(0,5,l1[5]);
    lc.setRow(0,6,l1[6]);
    lc.setRow(0,7,l1[7]);
}

//level 2 display
byte l2[8]= {B11111111, B11000001, B11011101, B00011101, B11011000, B11011011, B11001011, B11100011};
void level2(){
    lc.setRow(0,0,l2[0]);
    lc.setRow(0,1,l2[1]);
    lc.setRow(0,2,l2[2]);
    lc.setRow(0,3,l2[3]);
    lc.setRow(0,4,l2[4]);
    lc.setRow(0,5,l2[5]);
    lc.setRow(0,6,l2[6]);
    lc.setRow(0,7,l2[7]);
}

//level 3 display
byte l3[8]= {B11111000, B10000010, B10111100, B00011101, B11011100, B11011101, B11011101, B11000001};
void level3(){
    lc.setRow(0,0,l3[0]);
    lc.setRow(0,1,l3[1]);
    lc.setRow(0,2,l3[2]);
    lc.setRow(0,3,l3[3]);
    lc.setRow(0,4,l3[4]);
    lc.setRow(0,5,l3[5]);
    lc.setRow(0,6,l3[6]);
    lc.setRow(0,7,l3[7]);
}

//level 4 display
byte l4[8]= {B11000011, B10011011, B10111001, B00011101, B11011000, B10011101, B10111101, B10000001};
void level4(){
    lc.setRow(0,0,l4[0]);
    lc.setRow(0,1,l4[1]);
    lc.setRow(0,2,l4[2]);
    lc.setRow(0,3,l4[3]);
    lc.setRow(0,4,l4[4]);
    lc.setRow(0,5,l4[5]);
    lc.setRow(0,6,l4[6]);
    lc.setRow(0,7,l4[7]);
}

//level 5 display
byte l5[8]= {B10001000, B10101010, B10100010, B00111101, B01000100, B01010101, B01010101, B00010001};
void level5(){
    lc.setRow(0,0,l5[0]);
    lc.setRow(0,1,l5[1]);
    lc.setRow(0,2,l5[2]);
    lc.setRow(0,3,l5[3]);
    lc.setRow(0,4,l5[4]);
    lc.setRow(0,5,l5[5]);
    lc.setRow(0,6,l5[6]);
    lc.setRow(0,7,l5[7]);
}

//function to display each level corresponding to argument 
void levels(int num){
    switch(num){
        case 1:
            level1();
            break;

        case 2:
            level2();
            break;

        case 3:
            level3();
            break;

        case 4:
            level4();
            break;

        case 5:
            level5();
            break;

        default:
            level1();
            break;
    }
}

//level won display
byte c1[8] = {B00000000, B00000000, B00000000, B00011000, B00011000, B00000000, B00000000, B00000000};
byte c2[8] = {B00000000, B00000000, B00011000, B00100100, B00100100, B00011000, B00000000, B00000000};
byte c3[8] = {B00000000, B00111100, B01000010, B01000010, B01000010, B01000010, B00111100, B00000000};
byte c4[8] = {B00111100, B01000010, B10000001, B10000001, B10000001, B10000001, B01000010, B00111100};

//circles for celebration animation
void circle1(){
    lc.setRow(0,0,c1[0]);
    lc.setRow(0,1,c1[1]);
    lc.setRow(0,2,c1[2]);
    lc.setRow(0,3,c1[3]);
    lc.setRow(0,4,c1[4]);
    lc.setRow(0,5,c1[5]);
    lc.setRow(0,6,c1[6]);
    lc.setRow(0,7,c1[7]);
}

void circle2(){
    lc.setRow(0,0,c2[0]);
    lc.setRow(0,1,c2[1]);
    lc.setRow(0,2,c2[2]);
    lc.setRow(0,3,c2[3]);
    lc.setRow(0,4,c2[4]);
    lc.setRow(0,5,c2[5]);
    lc.setRow(0,6,c2[6]);
    lc.setRow(0,7,c2[7]);
}

void circle3(){
    lc.setRow(0,0,c3[0]);
    lc.setRow(0,1,c3[1]);
    lc.setRow(0,2,c3[2]);
    lc.setRow(0,3,c3[3]);
    lc.setRow(0,4,c3[4]);
    lc.setRow(0,5,c3[5]);
    lc.setRow(0,6,c3[6]);
    lc.setRow(0,7,c3[7]);
}

void circle4(){
    lc.setRow(0,0,c4[0]);
    lc.setRow(0,1,c4[1]);
    lc.setRow(0,2,c4[2]);
    lc.setRow(0,3,c4[3]);
    lc.setRow(0,4,c4[4]);
    lc.setRow(0,5,c4[5]);
    lc.setRow(0,6,c4[6]);
    lc.setRow(0,7,c4[7]);
}

//function to display each circle corresponding to argument 
void circles(int num){
    switch(num){
        case 1:
            circle1();
            break;

        case 2:
            circle2();
            break;

        case 3:
            circle3();
            break;

        case 4:
            circle4();
            break;
        default:
            circle1();
            break;
    }
}

//game won display
byte U[8] = {B00000000, B01100110, B01100110, B01100110, B01100110, B01100110, B01100110, B01111110};
byte W[8] = {B00000000, B01000010, B01000010, B01000010, B01011010, B01011010, B01011010, B01111110};
byte O[8] = {B00000000, B00111100, B01100110, B01000010, B01000010, B01000010, B01100110, B00111100 };
byte N[8] = {B00000000, B01100010, B01100010, B01010010, B01001010, B01000110, B01000110, B01000110 };

 void charU(){
    lc.setRow(0,0,U[0]);
    lc.setRow(0,1,U[1]);
    lc.setRow(0,2,U[2]);
    lc.setRow(0,3,U[3]);
    lc.setRow(0,4,U[4]);
    lc.setRow(0,5,U[5]);
    lc.setRow(0,6,U[6]);
    lc.setRow(0,7,U[7]);
}

 void charW(){
    lc.setRow(0,0,W[0]);
    lc.setRow(0,1,W[1]);
    lc.setRow(0,2,W[2]);
    lc.setRow(0,3,W[3]);
    lc.setRow(0,4,W[4]);
    lc.setRow(0,5,W[5]);
    lc.setRow(0,6,W[6]);
    lc.setRow(0,7,W[7]);
}

 void charO(){
    lc.setRow(0,0,O[0]);
    lc.setRow(0,1,O[1]);
    lc.setRow(0,2,O[2]);
    lc.setRow(0,3,O[3]);
    lc.setRow(0,4,O[4]);
    lc.setRow(0,5,O[5]);
    lc.setRow(0,6,O[6]);
    lc.setRow(0,7,O[7]);
} 

 void charN(){
    lc.setRow(0,0,N[0]);
    lc.setRow(0,1,N[1]);
    lc.setRow(0,2,N[2]);
    lc.setRow(0,3,N[3]);
    lc.setRow(0,4,N[4]);
    lc.setRow(0,5,N[5]);
    lc.setRow(0,6,N[6]);
    lc.setRow(0,7,N[7]);
}

//happy face
byte hf[8]= {B00111100,B01000010,B10100101,B10000001,B10100101,B10011001,B01000010,B00111100};

void happyFace(){
    lc.setRow(0,0,hf[0]);
    lc.setRow(0,1,hf[1]);
    lc.setRow(0,2,hf[2]);
    lc.setRow(0,3,hf[3]);
    lc.setRow(0,4,hf[4]);
    lc.setRow(0,5,hf[5]);
    lc.setRow(0,6,hf[6]);
    lc.setRow(0,7,hf[7]);
}


//sad face
byte sf[8]= {B00111100,B01000010,B10100101,B10000001,B10011001,B10100101,B01000010,B00111100};
void sadFace(){
    lc.setRow(0,0,sf[0]);
    lc.setRow(0,1,sf[1]);
    lc.setRow(0,2,sf[2]);
    lc.setRow(0,3,sf[3]);
    lc.setRow(0,4,sf[4]);
    lc.setRow(0,5,sf[5]);
    lc.setRow(0,6,sf[6]);
    lc.setRow(0,7,sf[7]);
}

