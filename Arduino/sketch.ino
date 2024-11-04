#include <MD_Parola.h>
#include <MD_MAX72xx.h>

// MAX7219 LED display
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES 4
#define CS_PIN 10
#define DATA_PIN 11
#define CLK_PIN 13

// Columns buttons
#define COL_1_BUTTON_PIN 3
#define COL_2_BUTTON_PIN 2
#define COL_3_BUTTON_PIN 1
#define COL_4_BUTTON_PIN 0

// Cancel and Ok buttons
#define CANCEL_BUTTON_PIN 3
#define OK_BUTTON_PIN 2

// Wrong and correct LEDs
#define WRONG_LED_PIN 3
#define CORRECT_LED_PIN 2

// functions
int binaryEquivalent(int n, bool is_negative); // converts n to dec equivalent of bin number in sign magnitude notation
int numberEquivalent(int n);                   // converts dec equivalent of bin number in sign magnitude notation to number
bool isMatchInPosition(int n, int position);   // tests if match is on specified position (checks n-th bit)
bool takeMatch(int *n, int position);          // takes match from specified position (n-th bit = 0) - return true, if there is no match (bit already empty) - return false
bool putMatch(int *n, int position);           // puts match in specified position (n-th bit = 1) - return true, if there is already match (bit not empty) - return false

// global variables
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// starting numbers
int num_pos_y = 1;

int a = binaryEquivalent(1, false);
int a_pos_x = 26;

int b = binaryEquivalent(9, true);
int b_pos_x = 13;

int c = binaryEquivalent(4, false);
int c_pos_x = 1;

void setup() {
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY / 2);
  mx.clear();
}

void loop() {
  printNumber(c, 1, 1);
  printSign();
  printNumber(b, 13, 1);
  printEquals(); 
  printNumber(a, 26, 1);

  delay(1000);
}

void printNumber(int n, int start_x, int start_y) {
  for (int i = 0; i < 4; i++) {
    if (isMatchInPosition(n, 1)) mx.setPoint(start_y + 0, start_x + i, true);
    if (isMatchInPosition(n, 4)) mx.setPoint(start_y + 6, start_x + i, true);
    if (isMatchInPosition(n, 7)) mx.setPoint(start_y + 3, start_x + i, true);

    if (isMatchInPosition(n, 2)) mx.setPoint(start_y + i + 0, start_x, true);
    if (isMatchInPosition(n, 3)) mx.setPoint(start_y + i + 3, start_x, true);
    if (isMatchInPosition(n, 5)) mx.setPoint(start_y + i + 3, start_x + 3, true);
    if (isMatchInPosition(n, 6)) mx.setPoint(start_y + i + 0, start_x + 3, true);
  }
  
  mx.update();
}

void printSign() {
  for (int i = 0; i < 4; i++) {
    mx.setPoint(3, 7 + i, true);
    mx.setPoint(5, 7 + i, true);
  } 

  mx.update();
}

void printEquals() {
  for (int i = 0; i < 5; i++) {
    mx.setPoint(2 + i, 21, true); 
    mx.setPoint(4, 19 + i, true); 
  } 

  mx.update();
}

int binaryEquivalent(int n, bool is_negative) {
    int binary_equivalents[] = {
        239, // -9 = 11101111 = 239
        255, // -8 = 11111111 = 255
        135, // -7 = 10000111 = 135
        253, // -6 = 11111101 = 253
        237, // -5 = 11101101 = 237
        230, // -4 = 11100110 = 230
        207, // -3 = 11001111 = 207
        219, // -2 = 11011011 = 219
        134, // -1 = 10000110 = 134
        191, // -0 = 10111111 = 191
        63,  //  0 = 00111111 = 63
        6,   //  1 = 00000110 = 6
        91,  //  2 = 01011011 = 91
        79,  //  3 = 01001111 = 79
        102, //  4 = 01100110 = 102
        109, //  5 = 01101101 = 109
        125, //  6 = 01111101 = 125
        7,   //  7 = 00000111 = 7
        127, //  8 = 01111111 = 127
        111, //  9 = 01101111 = 111
    };
    
    if (is_negative) return binary_equivalents[9 - n];
    return binary_equivalents[10 + n];
}

int numberEquivalent(int n) {
    switch(n) {
        case 239: return -9; // -9 = 11101111 = 239
        case 255: return -8; // -8 = 11111111 = 255
        case 135: return -7; // -7 = 10000111 = 135
        case 253: return -6; // -6 = 11111101 = 253
        case 237: return -5; // -5 = 11101101 = 237
        case 230: return -4; // -4 = 11100110 = 230
        case 207: return -3; // -3 = 11001111 = 207
        case 219: return -2; // -2 = 11011011 = 219
        case 134: return -1; // -1 = 10000110 = 134
        case 191: return -0; // -0 = 10111111 = 191
        case 63:  return  0; //  0 = 00111111 = 63
        case 6:   return  1; //  1 = 00000110 = 6
        case 91:  return  2; //  2 = 01011011 = 91
        case 79:  return  3; //  3 = 01001111 = 79
        case 102: return  4; //  4 = 01100110 = 102
        case 109: return  5; //  5 = 01101101 = 109
        case 125: return  6; //  6 = 01111101 = 125
        case 7:   return  7; //  7 = 00000111 = 7
        case 127: return  8; //  8 = 01111111 = 127
        case 111: return  9; //  9 = 01101111 = 111
        default:  return 99; // 99 = number not correct 
    };
}

bool isMatchInPosition(int n, int position) {
    // move specified bit to begining and check it
    return (n >> (position - 1)) & 1;
}

bool takeMatch(int *n, int position) {
    // if checking sign check if bit is empty and add it (because + is 0, - is 1)
    if (position == 8) {
        if (isMatchInPosition(*n, 8)) return false;
        *n = *n | (int)pow(2, position - 1);
        return true;
    }
    
    // check if bit is not empty and remove it
    if (!isMatchInPosition(*n, position)) return false;
    *n = *n & (~(int)pow(2, position - 1));
    return true;
}

bool putMatch(int *n, int position) {
    // if puting sign check if bit is not empty and remove it (because + is 0, - is 1)
    if (position == 8) {
        if (!isMatchInPosition(*n, 8)) return false;
        *n = *n & (~(int)pow(2, position - 1));
        return true;
    }
    
    // check if bit is empty and add it
    if (isMatchInPosition(*n, position)) return false;
    *n = *n | (int)pow(2, position - 1);
    return true;
}
