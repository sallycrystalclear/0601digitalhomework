#include "pitches.h"

#define ROW1 9
#define ROW2 8
#define ROW3 4
#define ROW4 A3
#define ROW5 3
#define ROW6 10
#define ROW7 11
#define ROW8 6
#define COL1 A2
#define COL2 12
#define COL3 A4
#define COL4 13
#define COL5 5
#define COL6 A5
#define COL7 7
#define COL8 2

#define BUTTON A0

const int row[] = {
  ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8
};
const int col[] = {
  COL1,COL2, COL3, COL4, COL5, COL6, COL7, COL8
};

byte scan[8][8] = {
  {1, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 1}
};

byte E[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,1},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,1},
  {0,0,0,0,0,0,0,0}
  };

int melody0[] = {
  NOTE_C4, NOTE_C4, NOTE_C4, NOTE_E4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_E4,  NOTE_E4, NOTE_E4, NOTE_G4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_B3,
};
int noteDurations[] = {
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1
};


int melody1[]={
NOTE_A3, NOTE_C4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_A4, NOTE_C4, NOTE_E4, NOTE_D4, NOTE_A4, NOTE_A5,  
};
int noteDurationsD[] = {
4, 4, 4, 8, 4, 4, 8, 4, 4, 2, 4, 4, 2, 4, 4, 2
};

int thisNote=-1,noteDuration=0;
long presentTime=0,previousTime=0,pauseBetweenNotes=0;
byte previousState=1, presentState=1, patternNumber=0;

void setup()
{
  for (byte i = 0; i <= 8; i++) {
    pinMode(row[i], OUTPUT);
  }
  for (byte i = 0; i <= 8; i++) {
    pinMode(col[i], OUTPUT);
  }
  pinMode(A0,INPUT_PULLUP);
}



void check(){
  presentTime=millis();
  if(presentTime-previousTime>=pauseBetweenNotes){
    thisNote+=1;
    if (thisNote>=16)
    {
      thisNote=-1;
      pauseBetweenNotes=1000;
      previousTime=millis();
    }
   else{
    noteDuration=1000/noteDurations[thisNote];
    tone(A1, melody0[thisNote], noteDuration);
    pauseBetweenNotes = noteDuration * 1.30;
    previousTime=millis();
    }
  }
}

void check2(){
  presentTime=millis();
  if(presentTime-previousTime>=pauseBetweenNotes){
    thisNote+=1;
    if(thisNote>=16){
      thisNote=-1;
      pauseBetweenNotes=1000;
      previousTime=millis();
    }
    else{
      noteDuration = 1000 / noteDurationsD[thisNote];
      tone(A1, melody1[thisNote], noteDuration);
      pauseBetweenNotes = noteDuration * 1.2;
      previousTime=millis();
    }
  }
}

void loop() {
  presentState = digitalRead(BUTTON);
  if(presentState==0&&previousState==1){
    patternNumber++;
    if(patternNumber>1)patternNumber=0;
  }
  if(patternNumber==0){
    showPattern(scan);
    check();
  }
  else{
    showPattern(E);
    check2();
  }
  previousState=presentState;
}

void showPattern(byte matrix[8][8]){
  for(byte i = 0; i < 8; i++){
    for(byte j = 0; j < 8; j++){
      digitalWrite(row[j], 1 - scan[i][j]);
      digitalWrite(col[j], 1 - matrix[i][j]);	
    }
    for(byte j = 0; j < 8; j++){
      digitalWrite(row[j], HIGH);
      digitalWrite(col[j], LOW);	
    }
  }
}






    












