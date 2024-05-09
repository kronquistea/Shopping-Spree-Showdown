# Shopping Spree Showdown

## Project Overview

Welcome to "Shopping Spree Showdown," a competitive and strategic game that tests your savvy in a virtual shopping arena. Imagine a grid, each square brimming with potential treasures in the form of item boxes. These aren't ordinary items; they're your ticket to victory, but only if you navigate the grid wisely. Your objective? Fill your cart with the most valuable items, maximizing your points while staying within your budget.

### The Game

You're not alone in this quest. The game features at least three actors on the board, fellow players or computer-controlled entities, each with the same goal. The twist? Each box on the grid will give two random items, and once a box is chosen, it's gone. These items aren't just varied in value; they bring surprises — power-ups to propel you forward or debuffs to set you back.

## Gameplay Criteria and Requirements

### The Simulation Environment

The battlefield of "Shopping Spree Showdown" is a 5x5 grid, each cell potentially holding item boxes.
    
- **Cell Contents:** Each cell on the grid may contain an item box. These boxes are the primary source of items for players, adding an element of surprise and strategy to each move. A token can also be connected to a cell on the grid.
### Initial Setup

- **Game Modes**: The game will either be initialized randomly or from a file. The factors you need to keep in mind include:
	- The master list of items to use in the game
	- The contents of each item box on the grid (see notes)
	- Initial Placement of Players
	- Initial Placement of Computers players
- **Token Placement**: Player and computers will both choose any square they wish to start in during their first turn.
- **Item Placement**: At the beginning of the game, the item boxes will be "filled" with 5 random items from the master list.
- **Notes on Item Box filling**:
	- For file initialization, the contents of each box will be specified by the file.
	- For random initialization, as each item is selected to go in the box, use the following probabilities to determine the item type.

| Item Type   | Chance |
| ----------- | ------ |
| Normal Item | 4 in 7 |
| Power Up    | 2 in 7 |
| Debuff      | 1 in 7 |
### Item Boxes and Items

Item boxes and the surprises they contain are the core of the game show.

#### Item Boxes - A Trove of 5 items

- Upon opening an item box, it chooses 2 of its items to give the player. These 2 are chosen at random. This element of chance adds a layer of unpredictability to each opened box.
- Players must be able to afford the items they receive. The game checks each item's price one at a time, and if the player's budget allows, the item is automatically purchased and added to their inventory.

#### Items - The Good, The Bad, and The Alright

**Normal Items:** These items are the backbone of a player's inventory, each with its own name, price, and point value. Your master list needs to include at least 10 normal items. These items should have varying levels of desirability. For example, a desirable/good item would have a high point value with a low cost, an undesirable/bad item would have a low point value with a high cost, and average items have more proportional values and costs.

**Power-Ups:** Beyond enhancing a player's score, these items offer special effects that can significantly influence the game's course. They retain the basic structure of normal items but with the added dimension of a game-altering ability. Your master list needs to include at least 3 Power Ups. Possible effects include:

- **Budget Boost:** Adds more money to the player's budget, allowing for more purchases.
- **Point Surge:** Provides an immediate point increase, boosting the player's score.
- **Refund Request:** Enables the player to return an item for a full refund, adding a layer of strategic item management.
- **Sabotage:** Allows a player to send a debuff to an opponent, introducing direct player interaction and competition.

**Debuffs:** These items introduce challenges and obstacles, testing players' adaptability and resilience. The effects of debuffs can range from financial setbacks to temporary restrictions on actions. Your master list needs to include at least 3 Debuffs. Possible effects include:

- **Monetary Drain:** A loss of money from the player's budget, tightening financial constraints.
- **Item Vanish:** An item disappears from the player's inventory without a refund, diminishing their resources.
- **Box Ban:** The player is temporarily unable to choose a new item box, limiting their advancement opportunities.

##### Think about what point values / costs you'd like to assign your Power Ups and Debuffs, if any.

##### Get creative when building out your items, the examples given are only suggestions.
### Game Tokens

#### Player

Each player controls a token that represents their presence on the grid. This token moves to adjacent cells during the player's turn, reflecting strategic positioning and movement decisions. If a player's token lands on a cell with an item box, they get to open it and potentially gain items.

#### Computer-Controlled

These tokens also have their designated spots on the grid but move differently. On their turn, they can move to any random cell on the board, adding an element of unpredictability to the game.

### Taking Turns

Each turn will involve a few different components:

#### Players
1. **Movement**: Player will move their token into an adjacent cell of their choice. If it has an unopened item box, they open it.
	1. Item boxes can only be opened once and should be removed from the game after being opened.
	2. Players can move to cells with no box.
2. **Item Use**: Players can choose to use any/all of their Power Ups. Debuffs are automatically applied if acquired.
	1. Both Power-Ups and Debuffs are single use, though their effects should persist as applicable.
	2. Track the turn number for used items.
3. **End Turn**: Player concludes their turn and gameplay moves on.

#### Computer-Controlled
1. **Movement**: Computer will move their token into a random cell. If it has an unopened item box, they open it. You can choose to apply logic so computers prefer cells with item boxes, if you'd like.
	1. Item boxes can only be opened once and should be removed from the game after being opened.
2. **Item Use**: Computer will have a 1 in 3 chance to use each of their Power Ups. Debuffs are automatically applied if acquired.
	1. Both Power-Ups and Debuffs are single use, though their effects should persist as applicable.
	2. Track the turn number for used items.
3. **End Turn**: Computer concludes their turn and gameplay moves on.

### Goals
#### Scoring and Budget Management
Players aim to amass the highest point total through strategic item collection and use, all while keeping within a set budget limit. This balance of risk and reward is central to the game's strategy.

#### Winning Conditions
The game concludes when all item boxes have been opened or when everyone has maxed out their budget. The highest-scoring player at this point is declared the winner.

### Conclusion and Analysis

- At the end of the game, print out a nicely formatted summary card of the winner to the terminal. This card should include printouts of things like their Point Total and Final Amount Spent. It should also include an itemized receipt of all the items they acquired during the game, and a rundown of the power-up/debuffs they used and on which turns. Include anything else that would provide needed context to the summary.
- You must also print a game summary, including relevant game statistics and summary cards for all players/computers to an output file.

### Additional Features

- **Visualization:** Consider ways to visually represent the grid, item boxes, and token to make the simulation more engaging and informative.
- **Interactive Menu:** Include a menu for users to view statistics, rerun the simulation, or exit the program.
	- All outputs should be nicely formatted into rows and columns anywhere appropriate.
	- The main menu choices should be at least:
		1. Run Game (2-4 tokens)
			- Randomized Initialization
			- Initialize from file 
		2. Re-play Game
		3. Quit
- **Prompt Menus**:
	- You must also prompt the user for input and explain their possible choices to them to make the game flow properly anywhere it is necessary.
## Grading Criteria

Your project will be evaluated based on how well you've implemented the following Object-Oriented Programming concepts and programming best practices:

1. **Object-Oriented Design:**
    - Your program must be designed around the principles of Object-Oriented Programming. Classes should be used to represent different entities where appropriate.
2. **Use of Dynamic Memory:**
    - Proper use of dynamic memory allocation (using `new` and `delete`) is expected, especially for managing collections of objects.
3. **Class Structures:**
    - Demonstrate understanding of class structures, including attributes, methods, and access specifiers (public, protected, private).
4. **Inheritance and Polymorphism:**
    - Your design should include examples of inheritance, showcasing the relationship between base and derived classes. Polymorphism should be used to allow for dynamic method binding.
5. **Encapsulation and Abstraction:**
    - Encapsulation should be evident through the use of classes to hide implementation details. Abstraction should be used to provide interfaces for classes, making the implementation details irrelevant to the user.
6. **Proper Use of Containers:**
    - Use C++ Standard Library containers (e.g., vectors, lists) to manage collections of objects efficiently.
7. **File Organization:**
    - Code should be well-organized across multiple files, typically separating class declarations in header files (.h) and definitions in implementation files (.cpp).
8. **Macro Guards in Header Files:**
    - Header files should contain macro guards to prevent multiple inclusions.
9. **Code Formatting:**
    - Your code should be well-formatted, using consistent indentation and whitespace to enhance readability.
10. **Efficient Memory Use:**
    - Demonstrate efficient memory use, avoiding memory leaks by properly deallocating dynamically allocated memory.
11. **Use of `const` and Pass-by-Reference:**
    - Where appropriate, use `const` to prevent modification of parameters passed to functions. Utilize pass-by-reference to avoid unnecessary copying of complex objects.
12. **Function Overloading and Default Arguments:**
    - Use function overloading to create functions with the same name but different parameters. Default arguments can be used to provide default values for function parameters.
13. **Error Handling:**
    - Implement error handling to manage unexpected situations or input errors gracefully.
14. **Documentation:**
    - Your code should be well-documented, including comments explaining the purpose of classes and methods, and any complex logic.

## Submission Instructions

To ensure a smooth submission and review process, please adhere to the following guidelines:

1. **Project Submission:**
    - Commit and push your complete project to your assigned GitHub Classroom repository.
2. **File Initialization**: You must include at least 3 files that can be used to load an initial game state from files. The formatting of those files is up to you. You must include a guide to their layout in your README.md documentation.
3. **Documentation:**
    - Alongside your code, include a README.md within your repository. Repository READMEs are written in Markdown, the standard document writing language for code repositories that controls formatting mostly through typing, rather than a toolbar. Here is a page that gives an overview of the formatting commands: [Markdown Cheat Sheet](https://www.markdownguide.org/cheat-sheet/)
    - This README.md should be at the top level of your repo and include at least the following sections.
        - **Compilation Instructions:** Detailed steps on how to compile your project, including any required flags or commands.
        - **Execution Instructions:** Clear instructions on how to run your project, specifying any required arguments or inputs.
        - **Project Status:** An overview of the current state of your project, highlighting whether it is complete, any known bugs, or incomplete features.
        - **Manual**: Include a brief, yet informative instruction manual telling users how to interact with your program and what it does. Include a brief description of your code design and how you went about implementing the project. Assume the reader is not familiar with the project before reading your manual.
        - **UML Diagrams**: Include UML diagrams for all of your classes. We recommend using [Mermaid](https://mermaid.live) , a convenient tool for building charts using a code-like syntax. You can embed the Mermaid code directly into your .md file using a markdown code block (open with \`\`\`mermaid and end the block with \`\`\`) and the code will render into the diagram. Think of the backticks like curly braces bundling the UML code together.
	        - [Mermaid Cheat Sheet](https://mermaid.js.org/syntax/classDiagram.html)
		    You may use whatever tool you like to make the UML Diagrams (like another online tool, or any tool that lets you make tables, like Excel \[Free for you with your student email])
		    Include the UMLs either embedded into your `README.md `or in their own `UML.pdf` file. Your choice.
 4. **Compatibility:**
    - Your project must be fully functional within GitHub Codespaces. This is crucial for ensuring that your project can be run and evaluated in a standardized environment.
    - You can still develop locally, but you should still ensure your code behaves as expected within a Codespace before committing.