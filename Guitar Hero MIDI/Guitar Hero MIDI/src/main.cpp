#include <MIDI.h>
#include <Arduino.h>
MIDI_CREATE_DEFAULT_INSTANCE();

static int START_BTN = 2;
static int SELECT_BTN = 3;
static int NECK_BTN_1 = 4;
static int NECK_BTN_2 = 5;
static int NECK_BTN_3 = 6;
static int NECK_BTN_4 = 7;
static int NECK_BTN_5 = 8;
static int WHAMMY_BAR = A1;
static int UP_STROKE_BTN = 9;
static int DOWN_STROKE_BTN = 10;

// remove this
static int STAR_POWER_X = A2;
static int STAR_POWER_Y = A3;
static int STAR_POWER_Z = A4;

static int BTN_1_PRESSED = 0;
static int BTN_2_PRESSED = 0;
static int BTN_3_PRESSED = 0;
static int BTN_4_PRESSED = 0;
static int BTN_5_PRESSED = 0;
// ponder if this is the best way
static bool NECK_BTNS_ON[10]; // 0,1 btn1, 2,3 btn2, etc. etc., even is up, odd is down
static bool START_PRESSED;
static bool SELECT_PRESSED;


int WHAMMY_STATE;
int NORM_WHAMMY_STATE;
int START_STATE;
int  prev_NORM_WHAMMY_STATE;

int SELECT_STATE;
int NECK_BTN_1_STATE;
int NECK_BTN_2_STATE;
int NECK_BTN_3_STATE;
int NECK_BTN_4_STATE;
int NECK_BTN_5_STATE;

int UP_STROKE_BTN_STATE;
int DOWN_STROKE_BTN_STATE;

int UP_STROKE_BTN_PRESSED = 0;
int DOWN_STROKE_BTN_PRESSED = 0;


int STAR_POWER_X_STATE;
int STAR_POWER_Y_STATE;
int STAR_POWER_Z_STATE;

void setup() {
  
  MIDI.begin(MIDI_CHANNEL_OMNI);

  pinMode(START_STATE, INPUT);
  pinMode(SELECT_STATE, INPUT); 
  pinMode(NECK_BTN_1_STATE, INPUT);
  pinMode(NECK_BTN_2_STATE, INPUT);
  pinMode(NECK_BTN_3_STATE, INPUT);
  pinMode(NECK_BTN_4_STATE, INPUT);
  pinMode(NECK_BTN_5_STATE, INPUT);
  pinMode(WHAMMY_BAR, INPUT);
  pinMode(UP_STROKE_BTN_STATE, INPUT);
  pinMode(DOWN_STROKE_BTN_STATE, INPUT);
  pinMode(STAR_POWER_X_STATE, INPUT);
  pinMode(STAR_POWER_Y_STATE, INPUT);
  pinMode(STAR_POWER_Z_STATE, INPUT);
  
  Serial.begin(31250);
}

void loop() {

  START_STATE = digitalRead(START_BTN);
  SELECT_STATE = digitalRead(SELECT_BTN);
  NECK_BTN_1_STATE = digitalRead(NECK_BTN_1);
  NECK_BTN_2_STATE = digitalRead(NECK_BTN_2);
  NECK_BTN_3_STATE = digitalRead(NECK_BTN_3);
  NECK_BTN_4_STATE = digitalRead(NECK_BTN_4);
  NECK_BTN_5_STATE = digitalRead(NECK_BTN_5);
  WHAMMY_STATE = analogRead(WHAMMY_BAR);

  prev_NORM_WHAMMY_STATE = NORM_WHAMMY_STATE;
  NORM_WHAMMY_STATE = map(WHAMMY_STATE, 30, 459, 0, 8192);

  UP_STROKE_BTN_STATE = digitalRead(UP_STROKE_BTN);
  DOWN_STROKE_BTN_STATE = digitalRead(DOWN_STROKE_BTN);

  STAR_POWER_X_STATE = analogRead(STAR_POWER_X);
  STAR_POWER_Y_STATE = analogRead(STAR_POWER_Y);
  STAR_POWER_Z_STATE = analogRead(STAR_POWER_Z);

  // TODO: Remove the serial.prints, and add a "last state"
  // START BUTTON LISTENER
  if (START_STATE > 0 && START_PRESSED == false) {
    START_PRESSED = true;
    Serial.println("START PRESSED");
  };
  if (START_STATE == 0 && START_PRESSED == true) {
    START_PRESSED = false;
    Serial.println("START RELEASED");
  };

  // SELECT BUTTON LISTENER
  if (SELECT_STATE > 0 && SELECT_PRESSED == false) {
    SELECT_PRESSED = true;
    Serial.println("SELECT PRESSED");
  };
  if (SELECT_STATE == 0 && SELECT_PRESSED == true) {
    SELECT_PRESSED = false;
    Serial.println("SELECT RELEASED");
  };

  // BUTTON 1 (GREEN) LISTENER
  if (NECK_BTN_1_STATE == 1 && BTN_1_PRESSED == 0){
    BTN_1_PRESSED = 1;
    Serial.println("BTN 1 PRESSED");
  };
  if (NECK_BTN_1_STATE == 0 && BTN_1_PRESSED == 1){
    BTN_1_PRESSED = 0;
    Serial.println("BTN 1 RELEASED");
  };

    // BUTTON 2 (RED) LISTENER
  if (NECK_BTN_2_STATE == 1 && BTN_2_PRESSED == 0){
    BTN_2_PRESSED = 1;
    Serial.println("BTN 2 PRESSED");
  };
  if (NECK_BTN_2_STATE == 0 && BTN_2_PRESSED == 1){
    BTN_2_PRESSED = 0;
    Serial.println("BTN 2 RELEASED");
  };

      // BUTTON 3 (YELLOW) LISTENER
  if (NECK_BTN_3_STATE == 1 && BTN_3_PRESSED == 0){
    BTN_3_PRESSED = 1;
    Serial.println("BTN 3 PRESSED");
  };
  if (NECK_BTN_3_STATE == 0 && BTN_3_PRESSED == 1){
    BTN_3_PRESSED = 0;
    Serial.println("BTN 3 RELEASED");
  };

      // BUTTON 4 (BLUE) LISTENER
  if (NECK_BTN_4_STATE == 1 && BTN_4_PRESSED == 0){
    BTN_4_PRESSED = 1;
    Serial.println("BTN 4 PRESSED");
  };
  if (NECK_BTN_4_STATE == 0 && BTN_4_PRESSED == 1){
    BTN_4_PRESSED = 0;
    Serial.println("BTN 4 RELEASED");
  };

      // BUTTON 5 (ORANGE) LISTENER
  if (NECK_BTN_5_STATE == 1 && BTN_5_PRESSED == 0){
    BTN_5_PRESSED = 1;
    Serial.println("BTN 5 PRESSED");
  }
  if (NECK_BTN_5_STATE == 0 && BTN_5_PRESSED == 1){
    BTN_5_PRESSED = 0;
    Serial.println("BTN 5 RELEASED");
  };

  // UP LISTENER
  if (UP_STROKE_BTN_STATE == 1 && UP_STROKE_BTN_PRESSED == 0) {
    UP_STROKE_BTN_PRESSED = 1;
    Serial.println("UP PRESSED");
  };
  if (UP_STROKE_BTN_STATE == 0 && UP_STROKE_BTN_PRESSED == 1) {
    UP_STROKE_BTN_PRESSED = 0;
    Serial.println("UP RELEASED");
  };

  // DOWN LISTENER
  if (DOWN_STROKE_BTN_STATE == 1 && DOWN_STROKE_BTN_PRESSED == 0) {
    DOWN_STROKE_BTN_PRESSED = 1;
    Serial.println("DOWN PRESSED");
  };
  if (DOWN_STROKE_BTN_STATE == 0 && DOWN_STROKE_BTN_PRESSED == 1) {
    DOWN_STROKE_BTN_PRESSED = 0;
    Serial.println("DOWN RELEASED");
  };




  // TODO: make this work and also be sensical, need prev_state to really work right though
  if (NECK_BTN_1_STATE > 0 && UP_STROKE_BTN_STATE > 0) {
    NECK_BTNS_ON[0] = false;
    // MIDI.sendNoteOff(42, 127, 1);
    NECK_BTNS_ON[0] = true;
    Serial.println("BTN 1 UP ON");
    // MIDI.sendNoteOn(42, 127, 1);
    //}

    if(NECK_BTNS_ON[1]){
      Serial.println("BTN 1 DOWN OFF");
      NECK_BTNS_ON[1] = false;
      // MIDI.sendNoteOff(60, 127, 1);
    };
  };
  if(NECK_BTNS_ON[0] && NECK_BTN_1_STATE == 0){
    NECK_BTNS_ON[0] = false;
    Serial.println("BTN 1 UP OFF");
    // MIDI.sendNoteOff(42, 127, 1);
  }
  
  if (NECK_BTN_1_STATE > 0 && DOWN_STROKE_BTN_STATE > 0) {
    
    //if (NECK_BTNS_ON[1] == false) {
      Serial.println("BTN 1 DOWN ON");
      NECK_BTNS_ON[1] = true;
      // MIDI.sendNoteOn(60, 127, 1);
    //}

    if(NECK_BTNS_ON[0]){
      Serial.println("BTN 1 UP OFF");
      NECK_BTNS_ON[0] = false;
      // MIDI.sendNoteOff(42, 127, 1);
    };
    
  };
  if(NECK_BTNS_ON[1] && NECK_BTN_1_STATE == 0){
    NECK_BTNS_ON[1] = false;
    Serial.println("BTN 1 DOWN OFF");
    // MIDI.sendNoteOff(60, 127, 1);
  }
  
  // TODO: Remove, this is the wrong part, accidentally put in an accelerometer instead of a rotation sensor
  Serial.print("X ");
  Serial.print(STAR_POWER_X_STATE);
  Serial.print(" Y ");
  Serial.print(STAR_POWER_Y_STATE);
  Serial.print(" Z ");
  Serial.println(STAR_POWER_Z_STATE);
  
  // Serial.println(SELECT_STATE);
}
