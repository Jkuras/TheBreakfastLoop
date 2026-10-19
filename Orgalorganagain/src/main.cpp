#include <Arduino.h>
int dataPin;
int clockPin;
int latchPin;
int numNotes = 61;
// change noteMod depending on which keyboard is running through this arduino
// (this code is the same for both upper keybeds and the footpedals)
int noteMod = 48;
int notes[61]; 
int note_pressed[61];

void setup() {
  // fill note_pressed array
  for(int l = 0; l < 61; l++){
    note_pressed[l] = 0;
  }

  // define pins
  // TODO: condense the three microcontrollers to a single arduino, with midi channels-per-keybed
  latchPin = 4;
  clockPin = 3;
  dataPin = 2;

  // define note array
  // TODO: add switch to adjust noteMod
  notes[0]= 0 + noteMod;
  notes[1]= 1 + noteMod;
  notes[2]= 2 + noteMod;
  notes[3]= 3 + noteMod;
  notes[4]= 4 + noteMod;
  notes[5]= 5 + noteMod;
  notes[6]= 6 + noteMod;
  notes[7]= 7 + noteMod;
  notes[8]= 8 + noteMod;
  notes[9]= 9 + noteMod;
  notes[10]= 10 + noteMod;
  notes[11]= 11 + noteMod;
  notes[12]= 12 + noteMod;
  notes[13]= 14 + noteMod;
  notes[14]= 13 + noteMod;
  notes[15]= 15 + noteMod;
  notes[16]= 16 + noteMod;
  notes[17]= 17 + noteMod;
  notes[18]= 18 + noteMod;
  notes[19]= 19 + noteMod;
  notes[20]= 20 + noteMod;
  notes[21]= 21 + noteMod;
  notes[22]= 22 + noteMod;
  notes[23]= 23 + noteMod;
  notes[24]= 24 + noteMod;
  notes[25]= 25 + noteMod;
  notes[26]= 26 + noteMod;
  notes[27]= 27 + noteMod;
  notes[28]= 28 + noteMod;
  notes[29]= 29 + noteMod;
  notes[30]= 30 + noteMod;
  notes[31]= 31 + noteMod;
  notes[32]= 32 + noteMod;
  notes[33]= 33 + noteMod;
  notes[34]= 34 + noteMod;
  notes[35]= 35 + noteMod;
  notes[36]= 36 + noteMod;
  notes[37]= 37 + noteMod;
  notes[38]= 38 + noteMod;
  notes[39]= 39 + noteMod;
  notes[40]= 40 + noteMod;
  notes[41]= 41 + noteMod;
  notes[42]= 42 + noteMod;
  notes[43]= 43 + noteMod;
  notes[44]= 44 + noteMod;
  notes[45]= 45 + noteMod;
  notes[46]= 46 + noteMod;
  notes[47]= 47 + noteMod;
  notes[48]= 48 + noteMod;
  notes[49]= 49 + noteMod;
  notes[50]= 50 + noteMod;
  notes[51]= 51 + noteMod;
  notes[52]= 52 + noteMod;
  notes[53]= 53 + noteMod;
  notes[54]= 54 + noteMod;
  notes[55]= 55 + noteMod;
  notes[56]= 56 + noteMod;
  notes[57]= 57 + noteMod;
  notes[58]= 58 + noteMod;
  notes[59]= 59 + noteMod;
  notes[60]= 60 + noteMod;
  notes[61]= 61 + noteMod;

  pinMode(dataPin, INPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);


  Serial.begin(31250);
}

void loop() {
  digitalWrite(latchPin, LOW);
  digitalWrite(latchPin, HIGH);
  // shift everything in
  for (int i = 0; i < numNotes; i++){
    int chk = digitalRead(dataPin);

    
    if(chk && !note_pressed[i]){
      noteOn( 0x92, notes[i], 127);
      // Serial.println(notes[i]);
    };
    if(!chk & note_pressed[i]){
      noteOn( 0x92, notes[i], 0);
      // Serial.println(notes[i]);
    };
    note_pressed[i] = chk;

    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  };

}

// play a note as needed
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
