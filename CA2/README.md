# Recursive Problem Solving in C++

This collection of four C++ projects demonstrates the application of recursive techniques to solve various algorithmic challenges. Recursion, a method where a function calls itself with modified parameters, is an essential concept in computer science, particularly useful for problems that can be broken down into smaller subproblems. The projects showcase the power of recursion to solve real-world problems efficiently and elegantly.

## Key Features:
- **Recursive Algorithms**: Each project utilizes recursion to break down complex problems into simpler, manageable subproblems.
- **Diverse Applications**: The projects span a range of problems, from string manipulation and array processing to pathfinding and game-solving.
- **C++ Implementation**: All projects are implemented in C++, utilizing standard libraries to facilitate recursion, input/output handling, and basic algorithms.

---


# Question 0: String Capitalization in C++

## Description
This project features a C++ program that reads user input and recursively converts each character of the input string to uppercase. The solution showcases the use of recursion and string manipulation techniques in C++.

## Key Features
- Recursively processes and converts all characters to uppercase.
- Handles multiple lines of input.
- Efficient string manipulation using recursion.

# Question 1: Max/Min Recursive Array Navigation

## Description
This project implements a recursive algorithm to navigate through an array, alternating between calculating the maximum and minimum values based on predefined conditions. The program prints out a sequence of elements during the traversal.

## Key Features
- Utilizes recursion to alternate between max and min operations.
- Prints out an array of numbers in a sequence based on dynamic conditions.
- Demonstrates recursion and array manipulation.

# Question 3: Path Counting in a Grid

## Description
This project features a recursive C++ solution for counting the number of distinct paths in a grid. The program ensures the paths do not exceed the grid's boundaries, starting from the top-left corner and reaching the bottom-right corner.

## Key Features
- Recursive backtracking solution to calculate distinct paths in a grid.
- Ensures paths are safe and within grid boundaries.
- Tracks all valid paths from the starting point to the destination.
## Example

### Input:

    3


### Output:

    5


### Explanation:
The program calculates and outputs the number of distinct paths from the top-left to the bottom-right corner in a 3x3 grid.

# Question 4: Reversi Game Solver in C++

## Description
This C++ project implements a solver for the game of Reversi. Using a backtracking algorithm, it navigates the board, making optimal moves based on the current state of the game.

## Key Features
- Implements the Reversi game board.
- Uses backtracking to solve the game and determine optimal moves.
- Outputs the sequence of moves required to solve the puzzle.
- Backtracking Algorithm

## Example

### Input:

    XXOOOXX
    XXOOOXX
    OOOOOOO
    OONOONO
    OOOONNO
    XXONOXX
    XXOOOXX


### Output:

    E6 LEFT
    F4 UP
    D3 RIGHT
    D6 LEFT


### Explanation:
The Reversi solver uses a backtracking algorithm to find the optimal moves. Given the initial board