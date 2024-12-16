<h1 align="center">UR-MatchstickEquations - Readme</h1>
<p align="center">
  <strong>
    Project from my studies at <a href="https://www.ur.edu.pl/pl/kolegia/kolegium-nauk-przyrodniczych">University of Rzeszów (UR)</a>
  </strong>
</p>
<div align="center">
  <a href="https://www.ur.edu.pl/pl/kolegia/kolegium-nauk-przyrodniczych">
    <img src="_for_readme/ur_banner.jpg?">
  </a>
</div>

<br>

# Table of Contents
* [Overview :sparkles:](#overview-sparkles)
  * [About](#about)
  * [Features](#features)
  * [Technologies](#technologies)
  * [Elements](#elements)
  * [Setup](#setup)
* [Details :scroll:](#details-scroll)
  * [User interface](#user-interface)
  * [Matchstick representation](#matchstick-representation)
  * [Equation generator](#equation-generator)
  * [Project structure](#project-structure)

<br>

# Overview :sparkles:

## About
The project involved creating an Arduino circuit on a breadboard and a program that uses the created circuit in a sensible way.

This project creates solvable equation and presents it in the form of matches on the console or MAX7219 32×8 LED Dot Matrix display. The player must move one match to correct the equation.

<br>

![preview](/_for_readme/preview.png)

## Features
- Binary representation of numbers (0–9) and operators (+-) matches a seven-segment display, mimicking matchstick arrangements.
- Simulation of matchstick movement by adding, removing, or repositioning segments.
- Real-time feedback on valid and invalid moves.
- Dynamic equation generator:
  - Random values and modifications ensure replayability.
  - Generating valid mathematical equation.
  - Modifiying equation by manipulating matchsticks to create broken mathematical equations.
  - Ensuring the equation has correct numbers and operators, which can be fixed with one move.
- Arduino version:
  - Displaying equations dynamically on a MAX7219 32×8 LED Matrix display.
  - Blinking animation effect for highlighting matchstick manipulation.
  - Interactive control using buttons.
  - Preventing removing a matchstick from an empty position or placing it in an occupied spot.
- Console version:
  - Visual representation of the equations on the console.
  - Dividing the equation into columns (A-D) and segments (1-7).
  - Control using input values (e.g., column and segment, like B1 D7).

<br>

> [!NOTE]  
> Room for improvements:
> - Moving more than one matchstick
> - Adding 2nd display and using 2-digit numbers
> - Multiplication and divide operators (X and /)

## Technologies
- [Arduino Yún](https://docs.arduino.cc/retired/boards/arduino-yun/)

Languages:
- [Arduino C++](https://docs.arduino.cc/language-reference/)
- C
- JS
- Prolog
  
Programs:
- [Wokwi - Arduino Uno simulator](https://wokwi.com/projects/new/arduino-uno)
- [Arduino IDE](https://www.arduino.cc/en/software)
- [Dev-C++](https://www.bloodshed.net)
- [VSCode](https://code.visualstudio.com)

Libraries:
-	[Bounce2](https://github.com/thomasfredericks/Bounce2)
-	[MD_MAX72XX](https://majicdesigns.github.io/MD_MAX72XX/)


## Elements
- 1x Arduino Yún
- 1x MAX7219 32×8 LED Dot Matrix display
- 1x Half-Size Breadboard
- 6x Microswitch 6x6mm 2 pin
- 1x Red LED 5mm
- 1x Green LED 5mm
- 2x 220 Ohm Resistor
- 22x Jumper wires

## Setup
Download this repo and:

#### Console version
- To run the program run console.exe file
- To edit the program:
  - Edit console.c file using any editor or IDE
  - Compile and run using gcc or IDE

#### Arduino version
- To run and edit the program in WOKWI simualtor:
  - Copy sketch.ino, diagram.json files to WOKWI
  - Add libraries.txt file or libraries from this file to WOKWI
  - Start simulation

- To run and edit the program on real Arduino:
  - Recreate program circuit
  - Open sketch.ino file in Arduino IDE
  - Install libraries listed in libraries.txt
  - Select your port and Arduino board
  - Connect the Arduino to your computer
  - Upload a sketch to the Arduino

<br> 

# Details :scroll:

## User interface
### Console version
![console version preview screenshot](/_for_readme/Console/console_preview.png)
The UI of the console version is represented using ASCII characters. The equation is divided into columns, and each column is further divided into segments. To move a matchstick, the user must input a column letter (A-D) and a segment number (1-7 for numbers or 1 for the operator).

![console wrong answer](/_for_readme/Console/console_01_wrong.png)
The game starts by displaying a printed equation and waits for user input. If the user makes a valid move that results in an incorrect answer or a non-existent number, the incorrect equation is displayed along with an error message.

![console wrong answer](/_for_readme/Console/console_02_wrong.png)
If the user tries to pick a matchstick from an empty segment, an error message is displayed.

![console wrong answer](/_for_readme/Console/console_03_wrong.png)
If the user tries to place a matchstick on an already-occupied segment, an error message is displayed.

![console correct answer](/_for_readme/Console/console_04_correct.png)
If the user makes a valid move that results in the correct answer, the correct equation is displayed along with a win message. The user is then asked whether they want to play again. If they choose "No" (N), the program ends. If they choose "Yes" (Y), the console is cleared, and a new equation is generated.

### Arduino version
![arduino version preview screenshot](/_for_readme/Arduino/arduino_preview.png)
The Arduino version is a hardware implementation of the matchstick game, using a MAX7219 32×8 LED Dot Matrix display to visually represent the equation. The game is controlled through physical buttons, and game status is indicated by two LEDs (red and green).

#### Equation Representation:
- The equation is displayed on the LED matrix, with each digit, operator, and equals sign represented using illuminated points.
- The equation is divided into "columns," with each column corresponding to a digit or operator.

#### Buttons beneath the display allow players to interact:
- **First Button Press:** Selects a column and highlights the first available matchstick or space in that column, depending on the game state.
- **Subsequent Presses:** Cycles through matchsticks or free spaces within the selected column. The selected element blinks for visual feedback.

#### Buttons on the left and right allow players to interact:
- **Left button (Cancel):**
  - If game state is ***column select*** it will generate new incorrect equation
  - If game state is ***match select*** it will cancel match and column selection
  - If game state is ***column select*** and ***match is picked*** it will put back the matchstick to the original place
  - If game state is ***game over*** it will replay the same equation
- **Right button (Confirm):**
  - If game state is ***column select*** it will submit the equation
  - If game state is ***match select*** it will pick selected match selection
  - If game state is ***column select*** and ***match is picked*** it will submit the equation
  - If game state is ***game over*** it will generate new equation

#### Game Feedback:
- **Red LED:** Lights up when the player's move results in an invalid equation.
- **Green LED:** Lights up when the equation is corrected successfully, signaling the player has won the round.

#### Game Logic:
- The game validates each move:
  - If the player doesn’t move a matchstick, the result will be incorrect.
  - If the player picks a matchstick but doesn’t place it, the result will be incorrect.
  - If the player's move creates a non-existing number, the result will be incorrect.
  - If the player moves a matchstick and forms an incorrect equation, the result will be incorrect.
  - The game handles edge cases such as attempting to select an empty space or placing a matchstick in an already-occupied space.
- If the game state is ***column select*** and ***no matchstick is picked***:
  - The player must select a column from which to pick a matchstick.
  - The player can generate a new equation using the cancel button.
  - The player can submit the equation using the confirm button.
- If the game state is ***match select*** and ***no matchstick is picked***:
  - The player must select a matchstick to pick.
  - The player can select another column to pick a matchstick.
  - The player can cancel the selected column using the cancel button.
  - The player can pick the selected matchstick using the confirm button.
- If the game state is ***column select*** and ***a matchstick is picked***:
  - The player must select a column where they will place the picked matchstick.
  - The player can cancel the picked matchstick using the cancel button.
  - The player can submit the equation using the confirm button.
- If the game state is ***match select*** and ***a matchstick is picked***:
  - The player must select an empty space to place the picked matchstick.
  - The player can select another column to pick a matchstick.
  - The player can cancel the selected column using the cancel button.
  - The player can place the matchstick in the selected space using the confirm button.
- After submitting the equation:
  - The player can press the cancel button to replay the game.
  - The player can press the confirm button to start a new game.

<img src="/_for_readme/Arduino/wokwi_cropped.gif" alt="arduino wokwi gif" width="100%">

## Matchstick representation
Each matchstick arrangement in a number can be represented as a binary number, where a matchstick is either present or absent in the corresponding position of a seven-segment digit.
```                     
   _______                                
  |   1   |        This bits:            |       |
6 |       | 2      7 6 5 4 3 2 1       6 |       | 2
  |_______|        1 1 0 0 1 1 0         |_______|
  |   7   |                                  7   |
5 |       | 3      Are equivalent of             | 3
  |_______|        number 4 because:             |
      4
```

A matchstick can be checked or added using AND and removed using OR operations with the appropriate bit, for example:
```
Checking if bit is set (match is in position):
      7 6 5 4 3 2 1 
      0 0 0 0 1 1 1  = 7 
AND   0 0 0 0 0 1 0 
      0 0 0 0 0 1 0  <- matchstick in the number 7 is at position 2
                ^ 
```
```
Setting bit to 0 (taking a match):
      7 6 5 4 3 2 1 
      1 0 1 1 0 1 1  = 2 
AND   1 1 0 1 1 1 1 
      1 0 0 1 0 1 1  <- matchstick removed from position 5 
          ^      
```
```
Setting bit to 1 (putting a match): 
      7 6 5 4 3 2 1 
      1 0 1 1 0 1 1  = 2 (without the matchstick in segment 5) 
OR    0 0 0 0 1 0 0 
      1 0 0 1 1 1 1  <- matchstick inserted at position 3 
              ^
```

Operator in the equation is represented in two ways: 
- For the console version it is an 8th bit of the number making them a sign-magnitude notation.  
- For the Arduino version it is boolean variable so the numbers are equivalent of 7 bit numbers.
```
239, // -9 = 11101111 = 239    -----|
255, // -8 = 11111111 = 255         |
135, // -7 = 10000111 = 135         |
253, // -6 = 11111101 = 253         |
237, // -5 = 11101101 = 237         |--- binary equivalents of numbers  
230, // -4 = 11100110 = 230         |--- only for console version 
207, // -3 = 11001111 = 207         |
219, // -2 = 11011011 = 219         |
134, // -1 = 10000110 = 134         |
191, // -0 = 10111111 = 191    -----|

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
```

## Equation generator
Generating new equation starts with randomly creating correct equation, then it is breaked in every way and then one of incorrect equations is choosed randomly.

### Genearting correct equation
First, all possible equations were generated using prolog. Then using that I noticed the pattern and came up with the formula.
```
//   N1   OP    N2  =   R
// (0-9) (+-) (0-9) = (0-9)

R = random(0, 9)
IS_PLUS = random(0, 1)
N1 = (IS_PLUS) ? random(0, R) : random(R, 9 - R)
N2 = (IS_PLUS) ? R - N1 : N1 - R
```
Check *Console/equation_generation_1.pl* file for more info.

### Breaking correct equation
The equation breaking process must satisfy these rules:
- The column is a number or operator which we can transform
- Transformation is:
  - moving a match in the same column
  - taking it from one column AND puting it in another
- Match cannot be picked from empty segment
- Match cannot be put in occupied segment
- Match cannot be moved to the starting place
- Broken equation must consist of the valid numbers and valid operator 

After getting correct equations I manually created an array with all possible transformations of numbers.
```
can_become = [[
    // by moving
    [6, 9],     // 0
    [],         // 1
    [3],        // 2
    [2, 5],     // 3
    [],         // 4
    [3],        // 5
    [0, 9],     // 6
    [],         // 7
    [],         // 8
    [0, 6]      // 9
  ], [
    // by taking
    [],         // 0
    [],         // 1
    [],         // 2
    [],         // 3
    [],         // 4
    [],         // 5
    [5],        // 6
    [1],        // 7
    [0, 6, 9],  // 8
    [3, 5]      // 9
  ], [
    // by putting
    [8],        // 0
    [7],        // 1
    [],         // 2
    [9],        // 3
    [],         // 4
    [6, 9],     // 5
    [8],        // 6
    [],         // 7
    [],         // 8
    [8]         // 9
  ]]
```

Then, using brute force method I created function for printing all incorrect equations.
```
//   a    operator    b   =   c
// (0-9)    (+-)    (0-9) = (0-9)

1. Transform by moving
  1.1. moving a
  1.2. moving b
  1.3. moving c
2. Transform by taking from '+' operator
  2.1. and putting to a
  2.2. and putting to b
  2.3. and putting to c
3. Transform by taking from a
  3.1. and putting to '-' operator
  3.2. and putting to b
  3.3. and putting to c
4. Transform by taking from b
  4.1. and putting to '-' operator
  4.2. and putting to a
  4.3. and putting to c
5. Transform by taking from c
  5.1. and putting to '-' operator
  5.2. and putting to a
  5.3. and putting to b
```

After getting all incorrect equations I modified function to get correct equation and randomly select one of its incorrect equations.

Check *Console/equation_generation_2.html* file for more info and run it for full list of broken equations.

## Project structure
- :file_folder: UR-MatchstickEquations (project folder)
  - :page_facing_up: *github config*
  - :page_facing_up: *readme file*
  - :file_folder: _for_readme - :page_facing_up: *files for readme*
  - :file_folder: Arduino
    - :page_facing_up: *diagram.json file - wokwi scheme of the project*
    - :page_facing_up: *libraries.txt file - used libraries*
    - :page_facing_up: *sketch.ino file - code of the Arduino version*
    - :page_facing_up: *real_circuit.png file - photo of real life circuit*
    - :page_facing_up: *wokwi_circuit.png file - screen of wokwi circuit* 
  - :file_folder: Console
    - :page_facing_up: *console.c file - code of the console version*
    - :page_facing_up: *console.exe file - console version program*
    - :page_facing_up: *equation_generation_1.pl file - used to create correct equations*
    - :page_facing_up: *equation_generation_2.html file - used to change correct equations*
