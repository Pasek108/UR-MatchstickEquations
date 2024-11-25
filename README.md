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

## Table of Contents
* [Overview :eye:](#overview-eye)
  * [About](#about)
  * [Technologies](#technologies)
  * [Technologies](#technologies)
  * [Features](#features)
  * [Setup](#setup)
  * [How to use](#how-to-use)
* [Details :scroll:](#details-scroll)
  * [User interface](#user-interface)
  * [Project structure](#project-structure)

<br>

## Overview :eye:

### About
The project involved creating an Arduino circuit on a breadboard and a program that uses the created circuit in a sensible way.

This project creates solvable equation and presents it in the form of matches on the console or MAX7219 32×8 LED Matrix. The player must move one match to correct the equation.

<br>

![preview](/_for_readme/preview.png)

----------------------------------

### Technologies
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
  
----------------------------------

### Features
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

----------------------------------

### Setup
- Download this repo
- Download [FluentEditor](https://www.cognitum.eu/semantics/fluenteditor/)
- Start live server ([VSCode LiveServer Extension](https://marketplace.visualstudio.com/items?itemName=ritwickdey.LiveServer), [Prepros](https://prepros.io/) etc.)
- Open *Ontology.encnl* file
- Update champions data (see [Updating data](#updating-data))

----------------------------------

### How to use

#### Finding solution

1. Input your guess/es on Loldle
2. Copy your guessed champion/s data
3. Paste it to "Guessed champions data" textbox
4. Click "Add champions" button
5. Mark your data as it is marked in Loldle (see images below)
6. Click "Generate SPQRQL" button
7. Copy generated query
8. Paste copied query in Fluent Editor SPARQL tab (last one in the bottom)
9. Execute query using "Execute" button
10. Enter the name of the first character from the list into the Loldle game
11. If guess wasn't correct, go back to step 2

<br>
<img alt="loldle guesses" src="/_for_readme/Details/loldle_guesses.png" width="500px">
<img alt="marked champions" src="/_for_readme/Details/marked_champions.png" width="500px">

For more data check [Middle column](#middle-column) section


#### Updating data 

Method 1:
1. Copy new or updated champion data
2. Add new champion name to *data/champions.txt* file
3. Add new or replace champion data in *data/champions_data.txt* file
4. Click "Generate all champions"
5. Replace all data in *Ontology.encnl* file

Method 2:
1. Copy new or updated champion data
3. Input champion name in "champion name" input
4. Input champion data in "champion data" textbox
5. Click "Generate champion"
6. Add new or replace existing champion data in *Ontology.encnl* file
7. Manually add new individuals of new champion if they not exist 

<br>

## Details :scroll:

### User interface
#### Solver
![main screen](/_for_readme/UI/main_screen.png)

Creating a query manually is a time-consuming task that requires knowledge of SPARQL and ensuring accuracy. 
Therefore, a query generator was prepared, allowing queries to be generated based on data copied from the Loldle website.

##### Left column
The left column of the generator allows for the generation of a new character's ontology by entering their name and copied data, or the entire knowledge base based on data in the files *champions.txt* and *champions_data.txt* in the */data* folder.

##### Middle column
The middle column is used to create containers with character data by pasting data copied from the website. 

It is possible to paste data for multiple characters at once, for example, if the player wants to use the program as a hint after several incorrect guesses, or to paste data one by one as characters are guessed with the help of the program. Next, by clicking on the containers, the player must reflect the correctness of the guessed character's data. 

The data is categorized into three types:
- **Red** – Incorrect, none of the data in the square is correct.
- **Yellow** – Partially correct, at least one element is correct, but some information is missing or incorrect.
- **Green** – Correct, all data matches.


- The order of the characters does not matter.
- Repetitions do not affect the program's operation.
- Once the correct data is marked in the column, you do not need to mark it again in other guesses.
- Unwanted containers can be deleted by clicking the X icon.

##### Right column
The right column of the program is used to generate a query based on the provided data by pressing the "Generate SPARQL" button.

----------------------------------

### Project structure
The project directory tree looks like this:
- :file_folder: UR-MatchstickEquations (project folder)
  - :page_facing_up: *github config*
  - :page_facing_up: *readme file*
  - :file_folder: _for_readme - :page_facing_up: *files for readme*
  - :file_folder: Arduino
    - :page_facing_up: *diagram.json file - wokwi scheme of the project*
    - :page_facing_up: *libraries.txt file - used libraries*
    - :page_facing_up: *sketch.ino file - code of the Arduino version*
  - :file_folder: Console
    - :page_facing_up: *console.c file - code of the console version*
    - :page_facing_up: *console.exe file - console version program*
    - :page_facing_up: *equation_generation_1.pl file - used to create correct equations*
    - :page_facing_up: *equation_generation_2.html file - used to change correct equations*
