#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <Bounce2.h>

/* ---------------- BOARD ELEMENTS ---------------- */

// MAX7219 LED display
#define CS_PIN 10
#define DATA_PIN 11
#define CLK_PIN 13
#define MAX_DEVICES 4
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Columns buttons
#define COL_1_BUTTON_PIN 5
#define COL_2_BUTTON_PIN 4
#define COL_3_BUTTON_PIN 3
#define COL_4_BUTTON_PIN 2

Bounce  COL_1_BUTTON_debouncer = Bounce();
Bounce  COL_2_BUTTON_debouncer = Bounce();
Bounce  COL_3_BUTTON_debouncer = Bounce();
Bounce  COL_4_BUTTON_debouncer = Bounce();

// Cancel and Confirm buttons
#define CANCEL_BUTTON_PIN 7
#define CONFIRM_BUTTON_PIN 6

Bounce CANCEL_BUTTON_debouncer = Bounce();
Bounce CONFIRM_BUTTON_debouncer = Bounce();

// Wrong and Correct LEDs
#define WRONG_LED_PIN 9
#define CORRECT_LED_PIN 8


/* ---------------- FUNCTIONS ---------------- */

// game functions
void selectColumn(byte column);     // select one of the columns
void selectMatchPlace(byte column); // select match place in selected column
byte getNextPlace();                // get next available place for match
void cancelMatchSelect();           // cancel match select
void pickMatch();                   // confirm selected match
void restart();                     // restart current equation

// display functions
void blinkMatch(byte column, byte match_position, bool tick);
void printEquation(bool print_plus);
void printNumber(byte n, byte x, byte y, byte blink_match, bool is_on);
void printOperator(bool print_plus);
void printEqualSign();
void showPickedMatch(bool show);

// matches functions
byte binaryEquivalent(byte n);                 // convert n to dec equivalent of bin number
byte numberEquivalent(byte n);                 // convert dec equivalent of bin number to number
bool isMatchInPosition(byte n, byte position); // test if match is on specified position
bool takeMatch(byte *n, byte position);        // take match from specified position 
bool putMatch(byte *n, byte position);         // put match on specified position


/* ---------------- GLOBAL VARIABLES ---------------- */

// numbers positions
#define NUM_POS_Y 1
#define A_POS_X 26
#define B_POS_X 13
#define C_POS_X 1

// starting numbers
byte starting_a = binaryEquivalent(8);
byte starting_b = binaryEquivalent(1);
byte starting_c = binaryEquivalent(4);
bool starting_plus_operator = 0;

byte a = starting_a;
byte b = starting_b;
byte c = starting_c;
bool plus_operator = starting_plus_operator;

enum GameState { COLUMN_SELECT, MATCH_SELECT, GAME_OVER };
enum GameState game_state = COLUMN_SELECT;

byte selected_column = 0;
byte selected_match = 0;
byte picked_column = 0;
byte picked_match = 0;

bool display_ticked = 0;
word last_tick_time = 0;


/* ---------------- MAIN FUNCTIONS ---------------- */

void setup() {
  // MAX7219 LED display
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY / 2);
  mx.control(MD_MAX72XX::UPDATE, 0);

  // Columns buttons
  pinMode(COL_1_BUTTON_PIN, INPUT_PULLUP);
  pinMode(COL_2_BUTTON_PIN, INPUT_PULLUP);
  pinMode(COL_3_BUTTON_PIN, INPUT_PULLUP);
  pinMode(COL_4_BUTTON_PIN, INPUT_PULLUP);

  COL_1_BUTTON_debouncer.attach(COL_1_BUTTON_PIN);
  COL_2_BUTTON_debouncer.attach(COL_2_BUTTON_PIN);
  COL_3_BUTTON_debouncer.attach(COL_3_BUTTON_PIN);
  COL_4_BUTTON_debouncer.attach(COL_4_BUTTON_PIN);

  COL_1_BUTTON_debouncer.interval(5);
  COL_2_BUTTON_debouncer.interval(5);
  COL_3_BUTTON_debouncer.interval(5);
  COL_4_BUTTON_debouncer.interval(5);

  // Cancel and Confirm buttons
  pinMode(CANCEL_BUTTON_PIN, INPUT_PULLUP);
  pinMode(CONFIRM_BUTTON_PIN, INPUT_PULLUP);

  CONFIRM_BUTTON_debouncer.attach(CONFIRM_BUTTON_PIN);
  CANCEL_BUTTON_debouncer.attach(CANCEL_BUTTON_PIN);

  CONFIRM_BUTTON_debouncer.interval(5);
  CANCEL_BUTTON_debouncer.interval(5);

  // Wrong and Correct LEDs
  pinMode(WRONG_LED_PIN, OUTPUT);
  pinMode(CORRECT_LED_PIN, OUTPUT);

  printEquation(plus_operator);
  Serial.begin(9600);
}

void loop() {
  // update debouncers
  COL_1_BUTTON_debouncer.update();
  COL_2_BUTTON_debouncer.update();
  COL_3_BUTTON_debouncer.update();
  COL_4_BUTTON_debouncer.update();

  CANCEL_BUTTON_debouncer.update();
  CONFIRM_BUTTON_debouncer.update();

  // column select state
  if (game_state == COLUMN_SELECT) {
    if (COL_1_BUTTON_debouncer.fell()) selectColumn(1);
    if (COL_2_BUTTON_debouncer.fell()) selectColumn(2);
    if (COL_3_BUTTON_debouncer.fell()) selectColumn(3);
    if (COL_4_BUTTON_debouncer.fell()) selectColumn(4);

    if (CANCEL_BUTTON_debouncer.fell()) {
      if (picked_match == 0) ;// new problem
      else restart();
    }

    if (CONFIRM_BUTTON_debouncer.fell()) ; // accept solution
  }

  // match select state
  if (game_state == MATCH_SELECT) {
    if (COL_1_BUTTON_debouncer.fell()) selectMatchPlace(1);
    if (COL_2_BUTTON_debouncer.fell()) selectMatchPlace(2);
    if (COL_3_BUTTON_debouncer.fell()) selectMatchPlace(3);
    if (COL_4_BUTTON_debouncer.fell()) selectMatchPlace(4);

    unsigned long time = millis();

    if (time - last_tick_time > 250) {
      last_tick_time = time;
      blinkMatch(selected_column, selected_match, display_ticked);
      display_ticked = !display_ticked;
    }

    if (CANCEL_BUTTON_debouncer.fell()) cancelMatchSelect();
    if (CONFIRM_BUTTON_debouncer.fell()) pickMatch();
  }

  // game over state
  if (game_state == GAME_OVER) {
    // digitalWrite(WRONG_LED_PIN, HIGH);
    // digitalWrite(CORRECT_LED_PIN, HIGH);
  }

  delay(1);
}


/* ---------------- GAME FUNCTIONS ---------------- */

void selectColumn(byte column) {
  selected_column = column;
  selected_match = 0;

  game_state = MATCH_SELECT;
}

void selectMatchPlace(byte column) {
  blinkMatch(selected_column, selected_match, (picked_match == 0));

  if (selected_column == column) {
    if (selected_column != 2) selected_match = getNextPlace();
    else selected_match = (picked_match == 0) ? (byte)plus_operator : (byte)!plus_operator;
  } else {
    selectColumn(column);
    selectMatchPlace(column);
  }
}

byte getNextPlace() {
  byte selected_place = selected_match;
  bool can_select = false;
  byte count = 0;

  do {
    selected_place = (selected_place % 7) + 1;
    if (count++ >= 7) return 0;

    switch (selected_column) {
      case 1: can_select = isMatchInPosition(a, selected_place); break;
      case 2: can_select = plus_operator; break;
      case 3: can_select = isMatchInPosition(b, selected_place); break;
      case 4: can_select = isMatchInPosition(c, selected_place); break;
    }
  } while ((picked_match == 0) ? !can_select : can_select);

  return selected_place;
}

void cancelMatchSelect() {
  blinkMatch(selected_column, selected_match, (picked_match == 0));

  selected_column = 0;
  selected_match = 0;

  game_state = COLUMN_SELECT;
}

void pickMatch() {
  if (selected_column == 0 || selected_match == 0) return;

  showPickedMatch(true);

  picked_column = selected_column;
  picked_match = selected_match;
  selected_column = 0;
  selected_match = 0;

  switch (picked_column) {
    case 1: takeMatch(&a, picked_match); break;
    case 2: plus_operator = false; break;
    case 3: takeMatch(&b, picked_match); break;
    case 4: takeMatch(&c, picked_match); break;
  }

  blinkMatch(picked_column, picked_match, false);
  game_state = COLUMN_SELECT;
}

void restart() {
  a = starting_a;
  b = starting_b;
  c = starting_c;
  plus_operator = starting_plus_operator;

  picked_column = 0;
  picked_match = 0;
  selected_column = 0;
  selected_match = 0;

  game_state = COLUMN_SELECT;

  mx.clear();
  printEquation(plus_operator);
}


/* ---------------- DISPLAY FUNCTIONS ---------------- */

void blinkMatch(byte column, byte match_position, bool tick) {
  switch (column) {
    case 1: printNumber(a, A_POS_X, NUM_POS_Y, match_position, tick); break;
    case 2: if (match_position != 0) printOperator(tick); break;
    case 3: printNumber(b, B_POS_X, NUM_POS_Y, match_position, tick); break;
    case 4: printNumber(c, C_POS_X, NUM_POS_Y, match_position, tick); break;
  }

  mx.update();
}

void printEquation(bool print_plus) {
  printNumber(a, A_POS_X, NUM_POS_Y, 0, true);
  printOperator(print_plus);
  printNumber(b, B_POS_X, NUM_POS_Y, 0, true);
  printEqualSign();
  printNumber(c, C_POS_X, NUM_POS_Y, 0, true);

  mx.update();
}

void printNumber(byte n, byte x, byte y, byte blink_match, bool is_on) {
  for (byte i = 0; i < 4; i++) {
    switch (blink_match) {
      case 1: mx.setPoint(y + 0, x + i, is_on); break;
      case 4: mx.setPoint(y + 6, x + i, is_on); break;
      case 7: mx.setPoint(y + 3, x + i, is_on); break;
      case 2: mx.setPoint(y + i + 0, x, is_on); break;
      case 3: mx.setPoint(y + i + 3, x, is_on); break;
      case 5: mx.setPoint(y + i + 3, x + 3, is_on); break;
      case 6: mx.setPoint(y + i + 0, x + 3, is_on); break;
    }
  }

  for (byte i = 0; i < 4; i++) {
    // horizontal matches
    if (blink_match != 1 && isMatchInPosition(n, 1)) mx.setPoint(y + 0, x + i, true);
    if (blink_match != 4 && isMatchInPosition(n, 4)) mx.setPoint(y + 6, x + i, true);
    if (blink_match != 7 && isMatchInPosition(n, 7)) mx.setPoint(y + 3, x + i, true);

    // vertical matches
    if (blink_match != 2 && isMatchInPosition(n, 2)) mx.setPoint(y + i + 0, x, true);
    if (blink_match != 3 && isMatchInPosition(n, 3)) mx.setPoint(y + i + 3, x, true);
    if (blink_match != 5 && isMatchInPosition(n, 5)) mx.setPoint(y + i + 3, x + 3, true);
    if (blink_match != 6 && isMatchInPosition(n, 6)) mx.setPoint(y + i + 0, x + 3, true);
  }

  mx.update();
}

void printOperator(bool print_plus) {
  for (byte i = 0; i < 5; i++) {
    mx.setPoint(2 + i, 21, print_plus);
    mx.setPoint(4, 19 + i, true);
  }

  mx.update();
}

void printEqualSign() {
  for (byte i = 0; i < 4; i++) {
    mx.setPoint(3, 7 + i, true);
    mx.setPoint(5, 7 + i, true);
  }

  mx.update();
}

void showPickedMatch(bool show) {
  for (byte i = 0; i < 4; i++) mx.setPoint(0 + i, 31, show);
  mx.update();
}

/* ---------------- MATCHES FUNCTIONS ---------------- */

byte binaryEquivalent(byte n) {
  byte binary_equivalents[] = {
    63,  // 0 = 00111111 = 63
    6,   // 1 = 00000110 = 6
    91,  // 2 = 01011011 = 91
    79,  // 3 = 01001111 = 79
    102, // 4 = 01100110 = 102
    109, // 5 = 01101101 = 109
    125, // 6 = 01111101 = 125
    7,   // 7 = 00000111 = 7
    127, // 8 = 01111111 = 127
    111, // 9 = 01101111 = 111
  };

  return binary_equivalents[n];
}

byte numberEquivalent(byte n) {
  switch (n) {
    case 63:  return  0;  //   0 = 00111111 = 63
    case 6:   return  1;  //   1 = 00000110 = 6
    case 91:  return  2;  //   2 = 01011011 = 91
    case 79:  return  3;  //   3 = 01001111 = 79
    case 102: return  4;  //   4 = 01100110 = 102
    case 109: return  5;  //   5 = 01101101 = 109
    case 125: return  6;  //   6 = 01111101 = 125
    case 7:   return  7;  //   7 = 00000111 = 7
    case 127: return  8;  //   8 = 01111111 = 127
    case 111: return  9;  //   9 = 01101111 = 111
    default:  return 255; // 255 = 11111111 = number not correct
  };
}

bool isMatchInPosition(byte n, byte position) {
  // shift specified bit to begining and check it
  return (n >> (position - 1)) & 1;
}

bool takeMatch(byte *n, byte position) {
  // check if bit is not empty and remove it
  if (!isMatchInPosition(*n, position)) return false;
  *n = *n & (~(1 << (position - 1)));
  return true;
}

bool putMatch(byte *n, byte position) {
  // check if bit is empty and add it
  if (isMatchInPosition(*n, position)) return false;
  *n = *n | (1 << (position - 1));
  return true;
}
