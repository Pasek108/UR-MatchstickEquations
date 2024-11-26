#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// converts number to dec equivalent of bin number in sign magnitude notation
int binaryEquivalent(int n, bool is_negative);

// converts dec equivalent of bin number in sign magnitude notation to number
int numberEquivalent(int n);

// prints equation on console
void printEquation(int a, int b, int c);

// tests if match is on specified position (checks n-th bit)
bool isMatchInPosition(int n, int position);

// takes match from specified position (n-th bit = 0) - return true
// if there is no match (bit already empty) - return false
bool takeMatch(int *n, int position);

// puts match in specified position (n-th bit = 1) - return true
// if there is already match (bit not empty) - return false
bool putMatch(int *n, int position);

// copy one equation values to the other equation
void saveEquation(int *saveTo, int *equation);

// breaks correct equation in every possible way and returns one broken equation
bool breakEquation(int *equation);

// starts new game by randomly creating correct equation and breaking it until success
int* startNewGame();


int main() {
    srand(time(NULL));
    
    bool end_game = 0;
    char player_decision = 'Y';
    
    while (!end_game) {
        // create equation
        int *equation = startNewGame();
        int starting_a = binaryEquivalent(equation[0], false);
        int starting_b = binaryEquivalent(equation[2], (bool)(!equation[1]));
        int starting_c = binaryEquivalent(equation[3], false);
        
        int a, b, c;
        char from_number, to_number;
        int from_position, to_position;
    
        // loop until correct answer
        while (true) {
            printf("------ move one match ------\n");                  
            bool is_correct = true;
            
            // begin with starting numbers
            a = starting_a;
            b = starting_b;
            c = starting_c;
        
            // print equation and wait for user input
            printEquation(a, b, c);
            printf("Input positions (from-to, np. A2 C7): ");
            scanf(" %c%d %c%d", &from_number, &from_position, &to_number, &to_position);
            
            // print user move
            printf("\nMove from %c%d to %c%d\n", from_number, from_position, to_number, to_position);
            
            // error and start again if position does not consist from letter A-D and position 1-8 
            if (from_number < 'A' || from_number > 'D' ||
                from_position < 1 || from_position > 8 ||
                to_number < 'A' || to_number > 'D' ||
                to_position < 1 || to_position > 8) {
                printf("Wrong move - position does not exist\n\n");
                continue;
            }
            
            // error and start again if position letter is B and position is not 1
            if ((from_number == 'B' && from_position != 1) ||
                (to_number == 'B' && to_position != 1)) {
                printf("Wrong move - position does not exist\n\n");
                continue;
            }
            
            // take match from specified position
            // error and start again if operation is not correct       
            switch(from_number) {
                case 'A': is_correct = takeMatch(&a, from_position); break;
                case 'B': is_correct = takeMatch(&b, 8); break;
                case 'C': is_correct = takeMatch(&b, from_position); break;
                case 'D': is_correct = takeMatch(&c, from_position); break;
            }
            
            if (!is_correct) {
                printf("Wrong move - no match to take from this position\n\n");
                continue;
            }
            
            // put match in specified position
            // error and start again if operation is not correct 
            switch(to_number) {
                case 'A': is_correct = putMatch(&a, to_position); break;
                case 'B': is_correct = putMatch(&b, 8); break;
                case 'C': is_correct = putMatch(&b, to_position); break;
                case 'D': is_correct = putMatch(&c, to_position); break;
            }
            
            if (!is_correct) {
                printf("Wrong move - there is a match in this position\n\n");
                continue;
            }
            
            // print equation and convert numbers to it's real form 
            printEquation(a, b, c);
            
            a = numberEquivalent(a);
            b = numberEquivalent(b);
            c = numberEquivalent(c);
            
            // if equation is correct end game, if not start again 
            // if number does not exist it will be big and equation also will be incorrect
            if (a + b == c) {
                printf("Correct answer!!\n\n");
                break;
            }
            
            printf("Wrong answer\n\n");
        }
        
        free(equation);
        
        // ask player for starting new game
        printf("Do you want to play more? (Y/N): ");
        scanf(" %c", &player_decision);
        printf("%c", player_decision);
        end_game = (player_decision != 'Y');
        system("@cls||clear");
    }
            
    return 0;
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

void printEquation(int a, int b, int c) {
    /* ---- EXAMPLE ----
    printf("   A     B     C           D   \n");
    printf("              ___         ___  \n");
    printf(" |   |           |           | \n");
    printf(" |___|  _|_   ___|  ---      | \n");
    printf("     |   |   |      ---      | \n");
    printf("     |       |___            | \n");
    */
    
    //first row
    printf("   A     B     C           D   \n");
    
    //second row
    printf("  ");
    printf((isMatchInPosition(a, 1)) ? "___" : "   ");
    
    printf("         ");
    printf((isMatchInPosition(b, 1)) ? "___" : "   ");
    printf("         ");
    
    printf((isMatchInPosition(c, 1)) ? "___" : "   ");
    printf("  \n");
    
    //third row
    printf(" ");
    printf((isMatchInPosition(a, 6)) ? "|" : " ");
    printf("   ");
    printf((isMatchInPosition(a, 2)) ? "|" : " ");
    
    printf("       ");
    printf((isMatchInPosition(b, 6)) ? "|" : " ");
    printf("   ");
    printf((isMatchInPosition(b, 2)) ? "|" : " ");
    printf("       ");
    
    printf((isMatchInPosition(c, 6)) ? "|" : " ");
    printf("   ");
    printf((isMatchInPosition(c, 2)) ? "|" : " ");
    printf(" \n");
    
    //fourth row
    printf(" ");
    printf((isMatchInPosition(a, 6)) ? "|" : " ");
    printf((isMatchInPosition(a, 7)) ? "___" : "   ");
    printf((isMatchInPosition(a, 2)) ? "|" : " ");
    
    printf("  ");
    printf((isMatchInPosition(b, 8)) ? "___" : "_|_");
    printf("  ");
    
    printf((isMatchInPosition(b, 6)) ? "|" : " ");
    printf((isMatchInPosition(b, 7)) ? "___" : "   ");
    printf((isMatchInPosition(b, 2)) ? "|" : " ");
	
    printf("  ---  ");
    
    printf((isMatchInPosition(c, 6)) ? "|" : " ");
    printf((isMatchInPosition(c, 7)) ? "___" : "   ");
    printf((isMatchInPosition(c, 2)) ? "|" : " ");
    printf(" \n");
    
    //fifth row
    printf(" ");
    printf((isMatchInPosition(a, 5)) ? "|" : " ");
    printf("   ");
    printf((isMatchInPosition(a, 3)) ? "|" : " ");
    
    printf("  ");
    printf((isMatchInPosition(b, 8)) ? "   " : " | ");
    printf("  ");
    
    printf((isMatchInPosition(b, 5)) ? "|" : " ");
    printf("   ");
    printf((isMatchInPosition(b, 3)) ? "|" : " ");
	
    printf("  ---  ");
    
    printf((isMatchInPosition(c, 5)) ? "|" : " ");
    printf("   ");
    printf((isMatchInPosition(c, 3)) ? "|" : " ");
    printf(" \n");
    
    //sixth row
    printf(" ");
    printf((isMatchInPosition(a, 5)) ? "|" : " ");
    printf((isMatchInPosition(a, 4)) ? "___" : "   ");
    printf((isMatchInPosition(a, 3)) ? "|" : " ");
    
    printf("       ");
    printf((isMatchInPosition(b, 5)) ? "|" : " ");
    printf((isMatchInPosition(b, 4)) ? "___" : "   ");
    printf((isMatchInPosition(b, 3)) ? "|" : " ");
    printf("       ");
    
    printf((isMatchInPosition(c, 5)) ? "|" : " ");
    printf((isMatchInPosition(c, 4)) ? "___" : "   ");
    printf((isMatchInPosition(c, 3)) ? "|" : " ");
    printf(" \n\n");
}

bool isMatchInPosition(int n, int position) {
    // move specified bit to begining and check it
    return (n >> (position - 1)) & 1;
}

bool takeMatch(int *n, int position) {
    // if checking sign check if bit is empty and add it (because + is 0, - is 1)
    if (position == 8) {
        if (isMatchInPosition(*n, 8)) return false;
        *n = *n | (1 << (position - 1));
        return true;
    }
    
    // check if bit is not empty and remove it
    if (!isMatchInPosition(*n, position)) return false;
    *n = *n & (~(1 << (position - 1)));
    return true;
}

bool putMatch(int *n, int position) {
    // if puting sign check if bit is not empty and remove it (because + is 0, - is 1)
    if (position == 8) {
        if (!isMatchInPosition(*n, 8)) return false;
        *n = *n & (~(1 << (position - 1)));
        return true;
    }
    
    // check if bit is empty and add it
    if (isMatchInPosition(*n, position)) return false;
    *n = *n | (1 << (position - 1));
    return true;
}

int* startNewGame() {
    // random correct equation
    int r = ((rand() % 10) + 0);
    int is_plus = ((rand() % 2) + 0);
    int n1 = (is_plus) ? ((rand() % (r + 1)) + 0) : ((rand() % (10 - r)) + r);
    int n2 = (is_plus) ? r - n1 : n1 - r;
    
    // make equation incorrect
    int* equation = (int*)malloc(4 * sizeof(int));
    
    if (equation == NULL) {
        // Exit if memory allocation failed
        printf("Memory allocation failed!\n");
        exit(1);  
    }
    
    equation[0] = n1;
    equation[1] = is_plus;
    equation[2] = n2;
    equation[3] = r;
      
    bool can_break = breakEquation(equation);
    if (!can_break) return startNewGame();
    
    return equation;
}

bool breakEquation(int *equation) {
    // 255 is a stop for iterating
    int can_become[3][10][4] = {{ 
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
    
    int a  = equation[0];
    int b  = equation[2];
    int c  = equation[3];
    char op = equation[1];
    
    int broken_equations[25][4];
    int equations_counter = 0;
    
    /* ------------- by moving ------------- */
    // moving a
    for (int i = 0; i < 4 && can_become[0][a][i] != 255; i++) {
        int new_a = can_become[0][a][i];
        
        if ((op == 0 && new_a - b != c) || (op == 1 && new_a + b != c)) {
            int possible_equation[4] = {new_a, op, b, c};
            saveEquation(broken_equations[equations_counter], possible_equation);
            equations_counter++;
        }
    }
    
    // moving b
    for (int i = 0; i < 4 && can_become[0][b][i] != 255; i++) {
    int new_b = can_become[0][b][i];
    
        if ((op == 0 && a - new_b != c) || (op == 1 && a + new_b != c)) {
            int possible_equation[4] = {a, op, new_b, c};
            saveEquation(broken_equations[equations_counter], possible_equation);
            equations_counter++;
        }
    }
    
    // moving c
    for (int i = 0; i < 4 && can_become[0][c][i] != 255; i++) {
    int new_c = can_become[0][c][i];
    
        if ((op == 0 && a - b != new_c) || (op == 1 && a + b != new_c)) {
            int possible_equation[4] = {a, op, b, new_c};
            saveEquation(broken_equations[equations_counter], possible_equation);
            equations_counter++;
        }
    }
    
    /* ------------- by taking from op == '+' ------------- */ 
    if (op == 1) {
        // and putting to a
        for (int i = 0; i < 4 && can_become[2][a][i] != 255; i++) {
            int new_a = can_become[2][a][i];
            
            if (new_a - b != c) {
                int possible_equation[4] = {new_a, 0, b, c};
                saveEquation(broken_equations[equations_counter], possible_equation);
                equations_counter++;
            }
        }
        
        // and putting to b
        for (int i = 0; i < 4 && can_become[2][b][i] != 255; i++) {
            int new_b = can_become[2][b][i];
            
            if (a - new_b != c) {
                int possible_equation[4] = {a, 0, new_b, c};
                saveEquation(broken_equations[equations_counter], possible_equation);
                equations_counter++;
            }
        }
        
        // and putting to c
        for (int i = 0; i < 4 && can_become[2][c][i] != 255; i++) {
            int new_c = can_become[2][c][i];
            
            if (a - b != new_c) {
                int possible_equation[4] = {a, 0, b, new_c};
                saveEquation(broken_equations[equations_counter], possible_equation);
                equations_counter++;
            }
        }
    }
    
    /* ------------- by taking from a ------------- */ 
    for (int i = 0; i < 4 && can_become[1][a][i] != 255; i++) {
        int new_a = can_become[1][a][i];
        
        // and putting to op == '-'
        if (op == 0 && new_a + b != c) {
            int possible_equation[4] = {new_a, 1, b, c};
            saveEquation(broken_equations[equations_counter], possible_equation);
            equations_counter++;
        }
        
        // and putting to b
        for (int j = 0; j < 4 && can_become[2][b][j] != 255; j++) {
            int new_b = can_become[2][b][j];
            
            if ((op == 0 && new_a - new_b != c) || (op == 1 && new_a + new_b != c)) {
                int possible_equation[4] = {new_a, op, new_b, c};
                saveEquation(broken_equations[equations_counter], possible_equation);
                equations_counter++;
            }
        }
        
        // and putting to c
        for (int j = 0; j < 4 && can_become[2][c][j] != 255; j++) {
            int new_c = can_become[2][c][j];
            
            if ((op == 0 && new_a - b != new_c) || (op == 1 && new_a + b != new_c)) {
                int possible_equation[4] = {new_a, op, b, new_c};
                saveEquation(broken_equations[equations_counter], possible_equation);
                equations_counter++;
            }
        }
    }
    
    /* ------------- by taking from b ------------- */ 
    for (int i = 0; i < 4 && can_become[1][b][i] != 255; i++) {
        int new_b = can_become[1][b][i];
        
        // and putting to op
        if (op == 0 && a + new_b != c) {
            int possible_equation[4] = {a, 1, new_b, c};
            saveEquation(broken_equations[equations_counter], possible_equation);
            equations_counter++;
        }
        
        // and putting to a
        for (int j = 0; j < 4 && can_become[2][a][j] != 255; j++) {
            int new_a = can_become[2][a][j];
            
            if ((op == 0 && new_a - new_b != c) || (op == 1 && new_a + new_b != c)) {
                int possible_equation[4] = {new_a, op, new_b, c};
                saveEquation(broken_equations[equations_counter], possible_equation);
                equations_counter++;
            }
        }
        
        // and putting to c
        for (int j = 0; j < 4 && can_become[2][c][j] != 255; j++) {
            int new_c = can_become[2][c][j];
            
            if ((op == 0 && a - new_b != new_c) || (op == 1 && a + new_b != new_c)) {
                int possible_equation[4] = {a, op, new_b, new_c};
                saveEquation(broken_equations[equations_counter], possible_equation);
                equations_counter++;
            }
        }
    }
    
    /* ------------- by taking from c ------------- */ 
    for (int i = 0; i < 4 && can_become[1][c][i] != 255; i++) {
        int new_c = can_become[1][c][i];
        
        // and putting to op
        if (op == 0 && a + b != new_c) {
            int possible_equation[4] = {a, 1, b, new_c};
            saveEquation(broken_equations[equations_counter], possible_equation);
            equations_counter++;
        }
        
        // and putting to a
        for (int j = 0; j < 4 && can_become[2][a][j] != 255; j++) {
            int new_a = can_become[2][a][j];
            
            if ((op == 0 && new_a - b != new_c) || (op == 1 && new_a + b != new_c)) {
                int possible_equation[4] = {new_a, op, b, new_c};
                saveEquation(broken_equations[equations_counter], possible_equation);
                equations_counter++;
            }
        }
        
        // and putting to b
        for (int j = 0; j < 4 && can_become[2][b][j] != 255; j++) {
            int new_b = can_become[2][b][j];
            
            if ((op == 0 && a - new_b != new_c) || (op == 1 && a + new_b != new_c)) {
                int possible_equation[4] = {a, op, new_b, new_c};
                saveEquation(broken_equations[equations_counter], possible_equation);
                equations_counter++;
            } 
        }
    }
    
    if (equations_counter == 0) return false;
    
    int random_equation = ((rand() % equations_counter) + 0);
    saveEquation(equation, broken_equations[random_equation]);
    return true;
}

void saveEquation(int *saveTo, int *equation) {
    saveTo[0] = equation[0];
    saveTo[1] = equation[1];
    saveTo[2] = equation[2];
    saveTo[3] = equation[3];
}

