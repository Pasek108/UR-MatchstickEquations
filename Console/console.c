#include <stdio.h>
#include <stdbool.h>
#include <math.h>

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

int main() {
    // save starting numbers
    int starting_a = binaryEquivalent(1, false);
    int starting_b = binaryEquivalent(9, true);
    int starting_c = binaryEquivalent(4, false);
    
    int a, b, c;
    char from_number, to_number;
    int from_position, to_position;

    // loop until correct answer
    while (true) {
        printf("------ przeloz zapalke ------\n");                  
        bool is_correct = true;
        
        // begin with starting numbers
        a = starting_a;
        b = starting_b;
        c = starting_c;
    
        // print equation and wait for user input
        printEquation(a, b, c);
        printf("Podaj pozycje (skad, dokad): ");
        scanf(" %c %d %c %d", &from_number, &from_position, &to_number, &to_position);
        
        // print user move
        printf("\nRuch z %c%d do %c%d\n", from_number, from_position, to_number, to_position);
        
        // error and start again if position does not consist from letter A-D and position 1-8 
        if (from_number < 'A' || from_number > 'D' ||
            from_position < 1 || from_position > 8 ||
            to_number < 'A' || to_number > 'D' ||
            to_position < 1 || to_position > 8) {
            printf("Bledny ruch - pozycja nie istnieje\n\n");
            continue;
        }
        
        // error and start again if position letter is B and position is not 1
        if ((from_number == 'B' && from_position != 1) ||
            (to_number == 'B' && to_position != 1)) {
            printf("Bledny ruch - pozycja nie istnieje\n\n");
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
            printf("Bledny ruch - nie ma zapalki do wziecia w podanej pozycji\n\n");
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
            printf("Bledny ruch- na pozycji docelowej jest juz zapalka\n\n");
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
            printf("Poprawna odpowiedz!!\n\n");
            break;
        }
        
        printf("Bledna odpowiedz\n\n");
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

