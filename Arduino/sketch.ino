#include <MD_MAX72xx.h>
#include <Bounce2.h>

/* ---------------- BOARD ELEMENTS ---------------- */

// MAX7219 LED display
#define CS_PIN 11
#define DATA_PIN 10
#define CLK_PIN 9
#define MAX_DEVICES 4
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

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
#define CANCEL_BUTTON_PIN 8
#define CONFIRM_BUTTON_PIN 6

Bounce CANCEL_BUTTON_debouncer = Bounce();
Bounce CONFIRM_BUTTON_debouncer = Bounce();

// Wrong and Correct LEDs
#define WRONG_LED_PIN 13
#define CORRECT_LED_PIN 12


/* ---------------- FUNCTIONS ---------------- */

// game functions
void selectColumn(byte column);     // select one of the columns
void selectMatchPlace(byte column); // select match place in selected column
byte getNextPlace();                // get next available place for match
void cancelMatchSelect();           // cancel match select
void pickMatch();                   // confirm place to pick selected match
void putMatch();                    // confirm place to put selected match
bool checkEquation();               // check if equation and its digits are correct
void restart();                     // restart current equation

// equation generation functions
void startNewGame();                             // genarate new equation and start new game
bool breakEquation(byte *equation);              // take correct equation and make it incorrect
void saveEquation(byte *saveTo, byte *equation); // copy equation
void logEquation(byte *equation);                // print equation on console

// display functions
void printEquation(bool print_plus);                  // print equation on display
void printEquationAndBlink(byte column, byte *blink); // print equation on display with one match on/off
void printNumber(byte n, byte *pos, byte *blink);     // print number on display
void printOperator(byte *blink);                      // print operator on display
void printEqualSign();                                // print equal sign on display
void printPickedMatch(bool show);                     // print picked match indicator on display

// matches functions
byte binaryEquivalent(byte n);                 // convert n to dec equivalent of bin number
byte numberEquivalent(byte n);                 // convert dec equivalent of bin number to number
bool isMatchInPosition(byte n, byte position); // test if match is on specified position
bool takeMatch(byte *n, byte position);        // take match from specified position
bool putMatch(byte *n, byte position);         // put match on specified position


/* ---------------- GLOBAL VARIABLES ---------------- */

// numbers positions
#define OPERATOR_POS_Y 2
#define OPERATOR_POS_X 19

#define EQUAL_SIGN_POS_Y 3
#define EQUAL_SIGN_POS_X 7

#define NUM_POS_Y 1
#define A_POS_X 26
#define B_POS_X 13
#define C_POS_X 1

byte pos_a[2] = {A_POS_X, NUM_POS_Y};
byte pos_b[2] = {B_POS_X, NUM_POS_Y};
byte pos_c[2] = {C_POS_X, NUM_POS_Y};

// starting numbers and opeartor
byte starting_a = binaryEquivalent(6);
byte starting_b = binaryEquivalent(2);
byte starting_c = binaryEquivalent(7);
bool starting_plus_operator = false;

// game state
enum GameState { COLUMN_SELECT, MATCH_SELECT, GAME_OVER };
enum GameState game_state = COLUMN_SELECT;

// current numbers and opeartor
byte a = starting_a;
byte b = starting_b;
byte c = starting_c;
bool plus_operator = starting_plus_operator;

// game variables
bool equation_checked = false;
byte selected_column = 0;
byte selected_match = 0;
byte picked_column = 0;
byte picked_match = 0;

bool display_ticked = false;
unsigned long last_tick_time = 0;


/* ---------------- MAIN FUNCTIONS ---------------- */

void setup() {
  // Serial.begin(9600);
  randomSeed(analogRead(0));

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

  startNewGame();
  mx.clear();
  printEquation(plus_operator);
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
      if (picked_match == 0) startNewGame();
      else restart();
    }

    if (CONFIRM_BUTTON_debouncer.fell()) game_state = GAME_OVER;
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
      byte blink[2] = {selected_match, (byte)display_ticked};
      printEquationAndBlink(selected_column, blink);
      display_ticked = !display_ticked;
    }

    if (CANCEL_BUTTON_debouncer.fell()) cancelMatchSelect();
    if (CONFIRM_BUTTON_debouncer.fell()) {
      if (picked_match == 0) pickMatch();
      else putMatch();
    }
  }

  // game over state
  if (game_state == GAME_OVER) {
    if (equation_checked) {
      if (CANCEL_BUTTON_debouncer.fell()) restart();
      if (CONFIRM_BUTTON_debouncer.fell()) startNewGame();
    } else {
      bool is_equation_correct = checkEquation();
      equation_checked = true;
      digitalWrite((is_equation_correct) ? CORRECT_LED_PIN : WRONG_LED_PIN, HIGH);
    }
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
  byte blink[2] = {selected_match, (byte)(picked_match == 0)};
  printEquationAndBlink(selected_column, blink);

  if (selected_column == column) {
    if (selected_column != 2) selected_match = getNextPlace();
    else selected_match = (byte)((!picked_match) ? plus_operator : !plus_operator);
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
  byte blink[2] = {selected_match, (byte)(picked_match == 0)};
  printEquationAndBlink(selected_column, blink);

  selected_column = 0;
  selected_match = 0;

  game_state = COLUMN_SELECT;
}

void pickMatch() {
  if (selected_column == 0 || selected_match == 0) return;

  printPickedMatch(true);

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

  byte blink[2] = {picked_match, (byte)false};
  printEquationAndBlink(picked_column, blink);
  game_state = COLUMN_SELECT;
}

void putMatch() {
  if (selected_column == 0 || selected_match == 0) return;

  printPickedMatch(false);

  switch (selected_column) {
    case 1: putMatch(&a, selected_match); break;
    case 2: plus_operator = true; break;
    case 3: putMatch(&b, selected_match); break;
    case 4: putMatch(&c, selected_match); break;
  }

  byte blink[2] = {selected_match, (byte)true};
  printEquationAndBlink(selected_column, blink);
  game_state = GAME_OVER;
}

bool checkEquation() {
  byte real_a = numberEquivalent(a);
  byte real_b = numberEquivalent(b);
  byte real_c = numberEquivalent(c);
  bool is_plus_sign = plus_operator;

  if (real_a == 255 || real_b == 255 || real_c == 255) return false;

  if (is_plus_sign) return real_a + real_b == real_c;

  return real_a - real_b == real_c;
}

void restart() {
  a = starting_a;
  b = starting_b;
  c = starting_c;
  plus_operator = starting_plus_operator;

  game_state = COLUMN_SELECT;

  equation_checked = false;
  selected_column = 0;
  selected_match = 0;
  picked_column = 0;
  picked_match = 0;

  display_ticked = false;
  last_tick_time = 0;

  mx.clear();
  printEquation(plus_operator);

  digitalWrite(CORRECT_LED_PIN, LOW);
  digitalWrite(WRONG_LED_PIN, LOW);
}


/* ---------------- EQUATION GENERATION FUNCTIONS ---------------- */

void startNewGame() {
  // random correct equation
  byte r = (byte)random(0, 10);
  byte is_plus = (byte)random(0, 2);
  byte n1 = (is_plus) ? (byte)random(0, r + 1) : (byte)random(r, 10);
  byte n2 = (is_plus) ? r - n1 : n1 - r;

  // make equation incorrect
  byte equation[4] = {n1, is_plus, n2, r};
  bool can_break = breakEquation(equation);

  if (!can_break) return startNewGame();

  // assign new equation and restart
  starting_a = binaryEquivalent(equation[0]);
  starting_b = binaryEquivalent(equation[2]);
  starting_c = binaryEquivalent(equation[3]);
  starting_plus_operator = (bool)equation[1];

  restart();
}

bool breakEquation(byte *equation) {
  // 255 is a stop for iterating
  byte can_become[3][10][4] = {{ 
      // by moving
      {6, 9,        255}, // 0
      {             255}, // 1
      {3,           255}, // 2
      {2, 5,        255}, // 3
      {             255}, // 4
      {3,           255}, // 5
      {0, 9,        255}, // 6
      {             255}, // 7
      {             255}, // 8
      {0, 6,        255}, // 9
    }, { 
      // by taking
      {             255}, // 0
      {             255}, // 1
      {             255}, // 2
      {             255}, // 3
      {             255}, // 4
      {             255}, // 5
      {5,           255}, // 6
      {1,           255}, // 7
      {0, 6, 9,     255}, // 8
      {3, 5,        255}, // 9
    }, { 
      // by putting
      {8,           255}, // 0
      {7,           255}, // 1
      {             255}, // 2
      {9,           255}, // 3
      {             255}, // 4
      {6, 9,        255}, // 5
      {8,           255}, // 6
      {             255}, // 7
      {             255}, // 8
      {8,           255}, // 9
    }
  };

  // Serial.println("---- ");
  // logEquation(equation);

  byte a  = equation[0];
  byte b  = equation[2];
  byte c  = equation[3];
  byte op = equation[1];

  byte broken_equations[25][4];
  byte equations_counter = 0;

  /* ------------- by moving ------------- */
  // moving a
  for (byte i = 0; i < 4 && can_become[0][a][i] != 255; i++) {
    byte new_a = can_become[0][a][i];

    if ((op == 0 && new_a - b != c) || (op == 1 && new_a + b != c)) {
      byte possible_equation[4] = {new_a, op, b, c};
      saveEquation(broken_equations[equations_counter], possible_equation);
      equations_counter++;
    }
  }

  // moving b
  for (byte i = 0; i < 4 && can_become[0][b][i] != 255; i++) {
    byte new_b = can_become[0][b][i];

    if ((op == 0 && a - new_b != c) || (op == 1 && a + new_b != c)) {
      byte possible_equation[4] = {a, op, new_b, c};
      saveEquation(broken_equations[equations_counter], possible_equation);
      equations_counter++;
    }
  }

  // moving c
  for (byte i = 0; i < 4 && can_become[0][c][i] != 255; i++) {
    byte new_c = can_become[0][c][i];

    if ((op == 0 && a - b != new_c) || (op == 1 && a + b != new_c)) {
      byte possible_equation[4] = {a, op, b, new_c};
      saveEquation(broken_equations[equations_counter], possible_equation);
      equations_counter++;
    }
  }

  /* ------------- by taking from op == '+' ------------- */ 
  if (op == 1) {
    // and putting to a
    for (byte i = 0; i < 4 && can_become[2][a][i] != 255; i++) {
      byte new_a = can_become[2][a][i];

      if (new_a - b != c) {
        byte possible_equation[4] = {new_a, 0, b, c};
        saveEquation(broken_equations[equations_counter], possible_equation);
        equations_counter++;
      }
    }

    // and putting to b
    for (byte i = 0; i < 4 && can_become[2][b][i] != 255; i++) {
      byte new_b = can_become[2][b][i];

      if (a - new_b != c) {
        byte possible_equation[4] = {a, 0, new_b, c};
        saveEquation(broken_equations[equations_counter], possible_equation);
        equations_counter++;
      }
    }

    // and putting to c
    for (byte i = 0; i < 4 && can_become[2][c][i] != 255; i++) {
      byte new_c = can_become[2][c][i];

      if (a - b != new_c) {
        byte possible_equation[4] = {a, 0, b, new_c};
        saveEquation(broken_equations[equations_counter], possible_equation);
        equations_counter++;
      }
    }
  }

  /* ------------- by taking from a ------------- */ 
  for (byte i = 0; i < 4 && can_become[1][a][i] != 255; i++) {
    byte new_a = can_become[1][a][i];

    // and putting to op == '-'
    if (op == 0 && new_a + b != c) {
      byte possible_equation[4] = {new_a, 1, b, c};
      saveEquation(broken_equations[equations_counter], possible_equation);
      equations_counter++;
    }

    // and putting to b
    for (byte j = 0; j < 4 && can_become[2][b][j] != 255; j++) {
      byte new_b = can_become[2][b][j];

      if ((op == 0 && new_a - new_b != c) || (op == 1 && new_a + new_b != c)) {
        byte possible_equation[4] = {new_a, op, new_b, c};
        saveEquation(broken_equations[equations_counter], possible_equation);
        equations_counter++;
      }
    }

    // and putting to c
    for (byte j = 0; j < 4 && can_become[2][c][j] != 255; j++) {
      byte new_c = can_become[2][c][j];

      if ((op == 0 && new_a - b != new_c) || (op == 1 && new_a + b != new_c)) {
        byte possible_equation[4] = {new_a, op, b, new_c};
        saveEquation(broken_equations[equations_counter], possible_equation);
        equations_counter++;
      }
    }
  }

  /* ------------- by taking from b ------------- */ 
  for (byte i = 0; i < 4 && can_become[1][b][i] != 255; i++) {
    byte new_b = can_become[1][b][i];

    // and putting to op
    if (op == 0 && a + new_b != c) {
      byte possible_equation[4] = {a, 1, new_b, c};
      saveEquation(broken_equations[equations_counter], possible_equation);
      equations_counter++;
    }

    // and putting to a
    for (byte j = 0; j < 4 && can_become[2][a][j] != 255; j++) {
      byte new_a = can_become[2][a][j];

      if ((op == 0 && new_a - new_b != c) || (op == 1 && new_a + new_b != c)) {
        byte possible_equation[4] = {new_a, op, new_b, c};
        saveEquation(broken_equations[equations_counter], possible_equation);
        equations_counter++;
      }
    }

    // and putting to c
    for (byte j = 0; j < 4 && can_become[2][c][j] != 255; j++) {
      byte new_c = can_become[2][c][j];

      if ((op == 0 && a - new_b != new_c) || (op == 1 && a + new_b != new_c)) {
        byte possible_equation[4] = {a, op, new_b, new_c};
        saveEquation(broken_equations[equations_counter], possible_equation);
        equations_counter++;
      }
    }
  }

  /* ------------- by taking from c ------------- */ 
  for (byte i = 0; i < 4 && can_become[1][c][i] != 255; i++) {
    byte new_c = can_become[1][c][i];

    // and putting to op
    if (op == 0 && a + b != new_c) {
      byte possible_equation[4] = {a, 1, b, new_c};
      saveEquation(broken_equations[equations_counter], possible_equation);
      equations_counter++;
    }

    // and putting to a
    for (byte j = 0; j < 4 && can_become[2][a][j] != 255; j++) {
      byte new_a = can_become[2][a][j];

      if ((op == 0 && new_a - b != new_c) || (op == 1 && new_a + b != new_c)) {
        byte possible_equation[4] = {new_a, op, b, new_c};
        saveEquation(broken_equations[equations_counter], possible_equation);
        equations_counter++;
      }
    }

    // and putting to b
    for (byte j = 0; j < 4 && can_become[2][b][j] != 255; j++) {
      byte new_b = can_become[2][b][j];

      if ((op == 0 && a - new_b != new_c) || (op == 1 && a + new_b != new_c)) {
        byte possible_equation[4] = {a, op, new_b, new_c};
        saveEquation(broken_equations[equations_counter], possible_equation);
        equations_counter++;
      } 
    }
  }

  if (equations_counter == 0) return false;

  byte random_equation = (byte)random(0, equations_counter);
  saveEquation(equation, broken_equations[random_equation]);
  return true;
}

void saveEquation(byte *saveTo, byte *equation) {
  saveTo[0] = equation[0];
  saveTo[1] = equation[1];
  saveTo[2] = equation[2];
  saveTo[3] = equation[3];

  // logEquation(saveTo);
}

void logEquation(byte *equation) {
  Serial.print(equation[0]);
  Serial.print((equation[1]) ? "+" : "-");
  Serial.print(equation[2]);
  Serial.print("=");
  Serial.println(equation[3]);
}


/* ---------------- DISPLAY FUNCTIONS ---------------- */

void printEquationAndBlink(byte column, byte *blink) {
  switch (column) {
    case 1: printNumber(a, pos_a, blink); break;
    case 2: printOperator(blink); break;
    case 3: printNumber(b, pos_b, blink); break;
    case 4: printNumber(c, pos_c, blink); break;
  }

  mx.update();
}

void printEquation(bool print_plus) {
  byte blink[2] = {0, (byte)true};
  byte blink_plus[2] = {1, (byte)print_plus};

  printNumber(a, pos_a, blink);
  printOperator(blink_plus);
  printNumber(b, pos_b, blink);
  printEqualSign();
  printNumber(c, pos_c, blink);

  mx.update();
}

void printNumber(byte n, byte *pos, byte *blink) {
  byte x = pos[0]; 
  byte y = pos[1];

  byte match = blink[0]; 
  bool is_on = blink[1];

  for (byte i = 0; i < 4; i++) {
    switch (match) {
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
    if (match != 1 && isMatchInPosition(n, 1)) mx.setPoint(y + 0, x + i, true);
    if (match != 4 && isMatchInPosition(n, 4)) mx.setPoint(y + 6, x + i, true);
    if (match != 7 && isMatchInPosition(n, 7)) mx.setPoint(y + 3, x + i, true);

    // vertical matches
    if (match != 2 && isMatchInPosition(n, 2)) mx.setPoint(y + i + 0, x, true);
    if (match != 3 && isMatchInPosition(n, 3)) mx.setPoint(y + i + 3, x, true);
    if (match != 5 && isMatchInPosition(n, 5)) mx.setPoint(y + i + 3, x + 3, true);
    if (match != 6 && isMatchInPosition(n, 6)) mx.setPoint(y + i + 0, x + 3, true);
  }

  mx.update();
}

void printOperator(byte *blink) {
  byte match = blink[0]; 
  bool is_on = blink[1];

  for (byte i = 0; i < 5; i++) {
    mx.setPoint(OPERATOR_POS_Y + i, OPERATOR_POS_X + 2, (match) ? is_on : plus_operator);
    mx.setPoint(OPERATOR_POS_Y + 2, OPERATOR_POS_X + i, true);
  }

  mx.update();
}

void printEqualSign() {
  for (byte i = 0; i < 4; i++) {
    mx.setPoint(EQUAL_SIGN_POS_Y + 0, EQUAL_SIGN_POS_X + i, true);
    mx.setPoint(EQUAL_SIGN_POS_Y + 2, EQUAL_SIGN_POS_X + i, true);
  }

  mx.update();
}

void printPickedMatch(bool show) {
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
