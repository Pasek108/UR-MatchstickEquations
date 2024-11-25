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
  * [Technologies](#technologies)
  * [Elements](#elements)
  * [Features](#features)
  * [Setup](#setup)
* [Details :scroll:](#details-scroll)
  * [User interface](#user-interface)
  * [Project structure](#project-structure)

<br>

# Overview :sparkles:

## About
The project involved creating an Arduino circuit on a breadboard and a program that uses the created circuit in a sensible way.

This project creates solvable equation and presents it in the form of matches on the console or MAX7219 32×8 LED Matrix display. The player must move one match to correct the equation.

<br>

![preview](/_for_readme/preview.png)

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

## Elements
- 1x Arduino Yún
- 1x MAX7219 32×8 LED Matrix display
- 1x Half-Size Breadboard
- 6x Microswitch 6x6mm 2 pin
- 1x Red LED 5mm
- 1x Green LED 5mm
- 2x 220 Ohm Resistor
- 22x Jumper wires

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
  - Install libraries fromlisted in libraries.txt
  - Select your port and Arduino board
  - Connect the Arduino to your computer
  - Upload a sketch

<br> 

# Details :scroll:

## User interface
### Solver
![main screen](/_for_readme/UI/main_screen.png)

Creating a query manually is a time-consuming task that requires knowledge of SPARQL and ensuring accuracy. 
Therefore, a query generator was prepared, allowing queries to be generated based on data copied from the Loldle website.

## Project structure
The project directory tree looks like this:
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
