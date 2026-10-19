#include <Arduino.h>

const int pedalIn = A0;

const int row1 = 10;
const int row2 = 9;
const int row3 = 7;
const int row4 = 8;
const int rowSwitch = 6;
const int selectA = 5;
const int selectB = 4;
const int selectC = 3;
const int enableSelect = 2;

const int buttonsShiftLoad = A3;
const int buttonsOutput = A5;

const int buttonsSi = A4;
const int buttonsSCK = 11;
const int buttonsG = A1;
const int buttonsRCK = A2;


uint8_t keyToMidiMap[49];
bool keyPressed[60];

int pedalValue = 0;
int noteVelocity = 127;
int octaveDisplacement = 0;

void setup() {
  // pin setup for existing circuits ICs
  pinMode(selectA, OUTPUT);
  pinMode(selectB, OUTPUT);
  pinMode(selectC, OUTPUT);
  pinMode(enableSelect, OUTPUT);

  pinMode(pedalIn, INPUT);


  pinMode(row1, INPUT);
  pinMode(row2, INPUT);
  pinMode(row3, INPUT);
  pinMode(row4, INPUT);
  pinMode(rowSwitch, OUTPUT);

  pinMode(buttonsShiftLoad, OUTPUT);
  pinMode(buttonsOutput, INPUT);

  pinMode(buttonsSi, INPUT);
  pinMode(buttonsSCK, OUTPUT);
  pinMode(buttonsG, OUTPUT);
  pinMode(buttonsRCK, OUTPUT);

  
  // key to note mapping
  // TODO: add a switch for octave up/down
  keyToMidiMap[0] = 36;
	keyToMidiMap[1] = 37;
	keyToMidiMap[2] = 38;
	keyToMidiMap[3] = 39;
	keyToMidiMap[4] = 40;
	keyToMidiMap[5] = 41;
	keyToMidiMap[6] = 42;
	keyToMidiMap[7] = 43;

	keyToMidiMap[8] = 44;
	keyToMidiMap[1 + 8] = 45;
	keyToMidiMap[2 + 8] = 46;
	keyToMidiMap[3 + 8] = 47;
	keyToMidiMap[4 + 8] = 48;
	keyToMidiMap[5 + 8] = 49;
	keyToMidiMap[6 + 8] = 50;
	keyToMidiMap[7 + 8] = 51;

	keyToMidiMap[16] = 52;
	keyToMidiMap[1 + 16] = 53;
	keyToMidiMap[2 + 16] = 54;
	keyToMidiMap[3 + 16] = 55;
	keyToMidiMap[4 + 16] = 56;
	keyToMidiMap[5 + 16] = 57;
	keyToMidiMap[6 + 16] = 58;
	keyToMidiMap[7 + 16] = 59;

	keyToMidiMap[24] = 60;
	keyToMidiMap[1 + 24] = 61;
	keyToMidiMap[2 + 24] = 62;
	keyToMidiMap[3 + 24] = 63;
	keyToMidiMap[4 + 24] = 64;
	keyToMidiMap[5 + 24] = 65;
	keyToMidiMap[6 + 24] = 66;
	keyToMidiMap[7 + 24] = 67;

  keyToMidiMap[32] = 68;
	keyToMidiMap[1 + 32] = 69;
	keyToMidiMap[2 + 32] = 70;
	keyToMidiMap[3 + 32] = 71;
	keyToMidiMap[4 + 32] = 72;
	keyToMidiMap[5 + 32] = 73;
	keyToMidiMap[6 + 32] = 74;
	keyToMidiMap[7 + 32] = 75;

  keyToMidiMap[40] = 76;
	keyToMidiMap[1 + 40] = 77;
	keyToMidiMap[2 + 40] = 78;
	keyToMidiMap[3 + 40] = 79;
	keyToMidiMap[4 + 40] = 80;
	keyToMidiMap[5 + 40] = 81;
	keyToMidiMap[6 + 40] = 82;
	keyToMidiMap[7 + 40] = 83;

  keyToMidiMap[48] = 84;
	keyToMidiMap[1 + 48] = 85;
	keyToMidiMap[2 + 48] = 86;
	keyToMidiMap[3 + 48] = 87;
	keyToMidiMap[4 + 48] = 88;
	keyToMidiMap[5 + 48] = 89;
	keyToMidiMap[6 + 48] = 90;
	keyToMidiMap[7 + 48] = 91;

  Serial.begin(31250);

    
  digitalWrite(enableSelect, LOW);
  // give it a second to spin up, just in case
  delay(1000);


}

void readCol(int a, int b, int c, int row, int index) {
  // read rows by group
  digitalWrite(selectA, a);
  digitalWrite(selectB, b);
  digitalWrite(selectC, c);
  digitalWrite(rowSwitch, HIGH);
  int group4 = digitalRead(row1);
  int group5 = digitalRead(row2);
  int group7 = digitalRead(row3);
  int group6 = digitalRead(row4);
  digitalWrite(rowSwitch, LOW);
  int group1 = digitalRead(row2);
  int group3 = digitalRead(row3);
  int group2 = digitalRead(row4);

  // act on the results
  if(!group1 && !keyPressed[row]){
    keyPressed[row] = true;
    noteOn(0x91, keyToMidiMap[row-8], noteVelocity);
  }
  
  if(!group2 && !keyPressed[row + 8]){
      keyPressed[row + 8] = true;
      noteOn(0x91, keyToMidiMap[row-8+8], noteVelocity);
  }

  if(!group3 && !keyPressed[row + 16]){
      keyPressed[row + 16] = true;
      noteOn(0x91, keyToMidiMap[row-8+16], noteVelocity);
  }

  if(!group4 && !keyPressed[row + 24]){
      keyPressed[row + 24] = true;
      noteOn(0x91, keyToMidiMap[row-8+24], noteVelocity);
  }

  if(!group5 && !keyPressed[row + 32]){
      keyPressed[row + 32] = true;
      noteOn(0x91, keyToMidiMap[row-8+32], noteVelocity);
  }

  if(!group6 && !keyPressed[row+40]){
      keyPressed[row + 40] = true;
      noteOn(0x91, keyToMidiMap[row-8+40], noteVelocity);
  }

  if(!group7 && !keyPressed[row + 48]){
      keyPressed[row + 48] = true;
      noteOn(0x91, keyToMidiMap[row-8+48], noteVelocity);
  }

  if(group1 && keyPressed[row]){
    keyPressed[row] = false;
    noteOn(0x91, keyToMidiMap[row-8], 0);
  }
  
  if(group2 && keyPressed[row + 8]){
      keyPressed[row + 8] = false;
      noteOn(0x91, keyToMidiMap[row-8+8], 0);
  }

  if(group3 && keyPressed[row + 16]){
      keyPressed[row + 16] = false;
      noteOn(0x91, keyToMidiMap[row-8+16], 0);
  }

  if(group4 && keyPressed[row + 24]){
      keyPressed[row + 24] = false;
      noteOn(0x91, keyToMidiMap[row-8+24], 0);
  }

  if(group5 && keyPressed[row + 32]){
      keyPressed[row + 32] = false;
      noteOn(0x91, keyToMidiMap[row-8+32], 0);
  }

  if(group6 && keyPressed[row+40]){
      keyPressed[row + 40] = false;
      noteOn(0x91, keyToMidiMap[row-8+40], 0);
  }

  if(group7 && keyPressed[row + 48]){
      keyPressed[row + 48] = false;
      noteOn(0x91, keyToMidiMap[row-8+48], 0);
  }




}

void setOn(int index){
  keyPressed[index] = true;
}

void PitchBend(int value){
  int change = 0x2000 + value;
  char low = change & 0x7F;
  char high = (change >> 7) & 0x7F;

  noteOn(0xE1, low, high);
}

void loop() {

  // put your main code here, to run repeatedly:
  for(int i = 0; i < 50; i ++){
      readCol(0, 0, 1, 8,  i + 0);
      readCol(1, 0, 1, 9,  i + 1);
      readCol(0, 1, 1, 10, i + 2);
      readCol(1, 1, 1, 11, i + 3);
      readCol(0, 0, 0, 4, i + 4);
      readCol(1, 0, 0, 5, i + 5);
      readCol(0, 1, 0, 6, i + 6);
      readCol(1, 1, 0, 7, i + 7);
  }

  // TODO: only trigger if the previous states pitchbend value is different
  PitchBend(map(analogRead(pedalIn), 0, 550, -0, 8000));
}

void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
	Serial.write(pitch);
	Serial.write(velocity);
}
