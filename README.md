<h1 align="center">UR-LoldleSolver - Readme</h1>
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
  * [Features](#features)
  * [Setup](#setup)
  * [How to use](#how-to-use)
* [Details :scroll:](#details-scroll)
  * [User interface](#user-interface)
  * [Data sources](#data-sources)
  * [Knowledge base structure](#knowledge-base-structure)
  * [SPARQL queries structure](#sparql-queries-structure)
  * [Project structure](#project-structure)

<br>

## Overview :eye:

### About
The project involved creating an ontological knowledge base using real-world data. The chosen environment for this task was [Ontorion Fluent Editor 2015](https://www.cognitum.eu/semantics/fluenteditor/).

This project creates a knowledge base of characters from League of Legends and uses the Fluent Editor environment to help solve the daily [Loldle game in classic mode](https://loldle.net/classic).

The knowledge base contains around 1,700 sentences written in CNL (Controlled Natural Language), which is a controlled language specific to the Fluent Editor environment. The data includes character names, regions, resources used by the character, attack range, gender, species, release year, and the character's in-game position.

<br>

![preview](/_for_readme/preview.png)

----------------------------------

### Technologies
Languages:
- HTML
- CSS
- JS
- SPARQL
  
Programs:
- [FluentEditor](https://www.cognitum.eu/semantics/fluenteditor/)
- [VSCode](https://code.visualstudio.com)
  
----------------------------------

### Features
- Generating champion data for the Fluent Editor ontology
- Generating the full knowledge base from champion data
- Adding guessed champion data and marking it
- Generating SPARQL queries to find the best solution

<br>

> [!NOTE]  
> Room for improvements:
> - Choosing champions instead of copy-pasting its data
> - Updating champions data from patch notes
> - Automatically web scraping champions data
> - More games (Dotadle, Pokedle etc.)

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

#### Fluent editor
![fluent editor](/_for_readme/UI/fluent_editor.png)

The generated query should be pasted into the SPARQL tab and executed. Then, you need to enter the name of the first character from the list into the Loldle game. 
If the guess is not correct, you need to copy the newly guessed character's data, paste it into the generator, mark the correctness, and once again generate and execute the query.

##### Document area
Document is a section for all knowledge base in the ontology. It contains all data about champions and everything associated with them.

##### Taxonomy tree
Taxonomy tree is a tree representation of all existing types of data and its individuals.

##### SPARQL tab
You can acces it at the bottom of the window. It's a tab where you must paste the generated query and execute it to get the most probable results.

----------------------------------

### Data sources
The knowledge base for the project was generated automatically using data collected manually from the website [https://loldle.net/classic](https://loldle.net/classic).

The data was collected by manually entering all possible answers for the Loldle game. These include champion names and their attributes, which were then used to automatically populate the knowledge base using a JavaScript script.

----------------------------------

### Knowledge base structure

The key elements of the ontological knowledge base are classes, their instances (individuals), and the relationships between these elements. The database has a flat structure, consisting of 7 classes, 6 relations, and 2 attributes.

#### Class descriptions
- **Class "gender"** - Describes the gender of characters. Currently, there are 3 genders in the game.

![gender class](/_for_readme/Details/gender_class.png)

<br>

- **Class "position"** - Describes the positions a character is currently played in. There are 5 positions in the game, and characters are often played in multiple positions.

![gender class](/_for_readme/Details/position_class.png)

<br>

- **Class "resource"** - Describes the resource used by the character in the game. Currently, characters use one of 13 types of resources.

![gender class](/_for_readme/Details/resource_class.png)

<br>

- **Class "species"** - Describes the species/race of a character. Characters may belong to one or more of 29 species.

![gender class](/_for_readme/Details/species_class.png)

<br>

- **Class "range-type"** - Describes the attack range of a character.

![gender class](/_for_readme/Details/range-type_class.png)

<br>

- **Class "region"** - Describes the locations associated with the characters. There are 16 main regions in the game’s lore.

![gender class](/_for_readme/Details/region_class.png)

<br>

- **Class "champion"** - Describes the existing champions. There are 167 champions available for players.

![gender class](/_for_readme/Details/champion_class.png)


#### Attribute descriptions
- **Attribute "released-in"** - Describes the year of a champion's release.
- **Attribute "have-importance"** - Describes the amount of information about a character. This attribute is artificially generated for use in finding the best choice during the Loldle game and does not exist in the game itself.


#### Relationship descriptions
- **Relation "have-gender"** - Links a character to their gender.
- **Relation "play-in"** - Links a character to the positions they are played in.
- **Relation "use-resource"** - Links a character to the resource they use.
- **Relation "have-range-type"** - Links a character to their attack types.
- **Relation "have-species"** - Links a character to their species.
- **Relation "belong-to"** - Links a character to the regions they are associated with.


#### CNL diagram
Below is a CNL diagram of the ontological knowledge base. White rectangles represent classes, green rectangles represent class instances or individuals, and black connections signify class containment. Green connections represent user-defined relationships.

![cnl diagram](/_for_readme/Details/CNL_diagram_2.JPG)

----------------------------------

### SPARQL queries structure

The query generated by program is based on functionalities presented below in form of small queries.

- Query listing champions by region and species, filtering for male characters
```SPARQL
select ?x ?region ?species {
    ?x rdf:type :Champion.
    ?x :hasGender :Male.
    ?x :belongsTo ?region.
    ?x :hasSpecies ?species.
}
```
<br>

- Query listing melee champions not from Runeterra or Shurima
```SPARQL
select ?x {
    ?x rdf:type :Champion.
    ?x :hasRangeType :Melee.
    FILTER NOT EXISTS {?x :belongsTo :Runeterra.}
    FILTER NOT EXISTS {?x :belongsTo :Shurima.}
}
```
<br>

- Query listing champions who are either Darkins or God-Warriors
```SPARQL
select ?x {
    ?x rdf:type :Champion.
    ?x :hasSpecies ?sp.
    FILTER (?sp IN (:Darkin, :GodWarrior))
}
```
<br>

- Query listing champions sorted by release year up to 2015
```SPARQL
select ?x ?y {
    ?x rdf:type :Champion.
    ?x :releasedsIn ?y.
    FILTER (?y <= 2015).
} ORDER BY DESC(?y)
```
<br>

**Example final query in less accurate form:**

- A query listing champions sorted by importance, who are male, not played in the jungle, played in support or top lane, not being undead, demons, or spirits, use mana, fight in melee, do not belong to the regions of Camavor, the Shadow Isles, Bilgewater, or Runeterra, and were released after 2015.
```SPARQL
SELECT ?x {
    ?x rdf:type :Champion.
    ?x :hasGender :Male.
    FILTER NOT EXISTS {?x :playsIn :Jungle}.
    ?x :playsIn ?pos.
    FILTER (?pos IN (:Support, :Top)).
    FILTER NOT EXISTS {?x :hasSpecies :Undead}.
    FILTER NOT EXISTS {?x :hasSpecies :Demon}.
    FILTER NOT EXISTS {?x :hasSpecies :Spirit}.
    ?x :usesResource :Mana.
    ?x :hasRangeType :Melee.
    FILTER NOT EXISTS {?x :belongsTo :Camavor}.
    FILTER NOT EXISTS {?x :belongsTo :ShadowIsles}.
    FILTER NOT EXISTS {?x :belongsTo :Bilgewater}.
    FILTER NOT EXISTS {?x :belongsTo :Runeterra}.
    ?x :releasedsIn ?y.
    FILTER (?y > 2015).
    FILTER (?y < 9999).
    ?x :hasImportance ?ord.
} ORDER BY DESC(?ord)
```
<br>

**Example final query in more accurate form:**

- A query listing champions sorted by importance, who are male and not any other gender, played in the jungle and not any other position, not being vastayan, darkin, human or magically altered, use mana and not any other resource, fight in melee and not any other range-type, belongs to at least one the regions of Ionia, Noxus, Runeterra or Shurima, and were released before 2017.
```SPARQL
SELECT ?x {
    ?x rdf:type :Champion.
    ?x :hasGender :Male.
    FILTER NOT EXISTS {
        ?x :hasGender ?g.
        FILTER (?g IN (:Female, :Other)).
    }
    ?x :playsIn :Jungle.
    FILTER NOT EXISTS {
        ?x :playsIn ?pos.
        FILTER (?pos IN (:Top, :Middle, :Support, :Bottom)).
    }
    FILTER NOT EXISTS {
        ?x :hasSpecies ?sp.
        FILTER (?sp IN (:Vastayan, :Darkin, :Human, :MagicallyAltered)).
    }
    ?x :usesResource :Mana.
    FILTER NOT EXISTS {
        ?x :usesResource ?res.
        FILTER (?res IN (:Manaless, :Energy, :HealthCosts, :Rage, :Courage, :Shield, :Fury, :Ferocity, :Heat, :Grit, :Bloodthirst, :Flow)).
    }
    ?x :hasRangeType :Melee.
    FILTER NOT EXISTS {
        ?x :hasRangeType ?rt.
        FILTER (?rt IN (:Ranged)).
    }
    FILTER NOT EXISTS {
        ?x :belongsTo ?reg.
        FILTER (?reg IN (:Freljord)).
    }
    ?x :belongsTo ?reg.
    FILTER (?reg IN (:Ionia, :Noxus, :Runeterra, :Shurima)).
    ?x :releasedsIn ?y.
    FILTER (?y > 0).
    FILTER (?y < 2017).
    ?x :hasImportance ?ord.
} ORDER BY DESC(?ord)
```

----------------------------------

### Project structure
The project directory tree looks like this:
- :file_folder: UR-LoldleSolver (project folder)
  - :page_facing_up: *github config*
  - :page_facing_up: *readme file*
  - :page_facing_up: *index.html file*
  - :page_facing_up: *style.css file*
  - :page_facing_up: *script.js file*
  - :page_facing_up: *Ontology.encnl file*
  - :file_folder: _for_readme - :page_facing_up: *files for readme*
  - :file_folder: data
    - :page_facing_up: *champions.txt file*
    - :page_facing_up: *champions_data.txt file*

<!--
----------------------------------

### Code organization

![program diagram](/_for_readme/program_diagram.png)

> [!WARNING]  
> Classes must be loaded from bottom to the top to avoid situation when class does not exist in the time of its objects creation

Menu is entry of the program.

Menu creates and manages one instance of each of the classes:
- MenuWindow (Credits)
- Difficulty
- TopScore
- Game

Difficulty and TopScore classes are extension of MenuWindow class which is responsible for showing and hiding menu window with transition

Game class creates and manages:
- One instance of RoadBackground class
- Two instances of treesBackground class (left and right side)
- One instance of classes:
  - HealthBar
  - EnergyBar
  - PointsCounter
  - GameOver
- One instance of Player class
- Many instances of classes:
  - Enemy
  - Deer
  - HappyDeer

-->
