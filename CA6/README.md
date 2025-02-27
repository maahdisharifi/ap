# Football Fantasy Project

## Overview

This project allows users to manage their football fantasy teams via a command-line interface (CLI). It features the creation of teams, player management, budget management, weekly performance tracking, and player transfers. The system has been built and extended to provide more advanced features and dynamic team management, as well as seamless player transfers.  
Given the scale of the project, it was developed in two serial phases, allowing us to build upon the initial foundation and progressively introduce more advanced features. To ensure the project could be effectively scaled, we followed clean code practices, including the use of Object-Oriented Programming (OOP) principles to structure the code and maintain readability and extensibility.


## Phase 1: CLI Commands

Phase 1 includes various CLI commands that form the foundation of the system. Users can interact with the system by executing commands related to managing their fantasy team, including registering, logging in, buying, and selling players.

### Commands in Phase 1:

1. **POST signup**
    - **Description**: Registers a new team with a team name and password.
    - **Example**: 
    ```bash
    POST signup? team_name Liverpool password abc123
    ```

2. **POST login**
    - **Description**: Logs the user in by verifying their team name and password.
    - **Example**: 
    ```bash
    POST login? team_name Liverpool password abc123
    ```

3. **GET show_team**
    - **Description**: Displays the current fantasy football team with all players and their stats.
    - **Example**: 
    ```bash
    GET show_team
    ```

4. **GET show_budget**
    - **Description**: Displays the remaining budget available for purchasing players.
    - **Example**: 
    ```bash
    GET show_budget
    ```

5. **GET players**
    - **Description**: Retrieves a list of available players along with their stats (price, position, goals, assists, etc.).
    - **Example**: 
    ```bash
    GET players
    ```

6. **POST buy_player**
    - **Description**: Buys a player and adds them to your team (if within budget).
    - **Example**: 
    ```bash
    POST buy_player? name Mohamed Salah
    ```

7. **POST sell_player**
    - **Description**: Sells a player and removes them from your team.
    - **Example**: 
    ```bash
    POST sell_player? name Virgil Van Dijk
    ```

8. **GET week_stats**
    - **Description**: Retrieves the current week's match results and stats for players.
    - **Example**: 
    ```bash
    GET week_stats
    ```

9. **GET team_performance**
    - **Description**: Displays the overall performance of your team, including points and player stats.
    - **Example**: 
    ```bash
    GET team_performance
    ```

## Phase 2: Advanced Features

Phase 2 introduces enhanced features, including improved player management, transfer handling, and detailed stats for better team performance tracking. These features provide a more sophisticated and dynamic experience for managing fantasy football teams.

### Commands in Phase 2:

1. **POST signup**
    - **Description**: Same as in Phase 1, registers a new team.
    - **Example**: 
    ```bash
    POST signup? team_name Arsenal password xyz123
    ```

2. **POST login**
    - **Description**: Same as in Phase 1, logs the user in.
    - **Example**: 
    ```bash
    POST login? team_name Arsenal password xyz123
    ```

3. **GET show_team**
    - **Description**: Same as in Phase 1, shows the current team lineup with stats.
    - **Example**: 
    ```bash
    GET show_team
    ```

4. **GET show_budget**
    - **Description**: Displays the current budget available.
    - **Example**: 
    ```bash
    GET show_budget
    ```

5. **GET players**
    - **Description**: Same as in Phase 1, retrieves available players and their stats.
    - **Example**: 
    ```bash
    GET players
    ```

6. **POST buy_player**
    - **Description**: Same as in Phase 1, buys a player.
    - **Example**: 
    ```bash
    POST buy_player? name Kevin De Bruyne
    ```

7. **POST sell_player**
    - **Description**: Same as in Phase 1, sells a player.
    - **Example**: 
    ```bash
    POST sell_player? name Sergio Ramos
    ```

8. **GET week_stats**
    - **Description**: Retrieves the performance of players for the current week.
    - **Example**: 
    ```bash
    GET week_stats
    ```

9. **GET team_performance**
    - **Description**: Displays overall team performance based on weekly stats.
    - **Example**: 
    ```bash
    GET team_performance
    ```

10. **POST transfer_window_open**
    - **Description**: Opens the transfer window, allowing players to be bought or sold.
    - **Example**: 
    ```bash
    POST transfer_window_open
    ```

11. **POST transfer_window_close**
    - **Description**: Closes the transfer window, halting any further player transfers.
    - **Example**: 
    ```bash
    POST transfer_window_close
    ```

12. **GET league_standings**
    - **Description**: Displays the current standings of all fantasy teams.
    - **Example**: 
    ```bash
    GET league_standings
    ```

13. **GET top_players**
    - **Description**: Retrieves the top-performing players based on stats like goals, assists, and clean sheets.
    - **Example**: 
    ```bash
    GET top_players
    ```

14. **GET match_results**
    - **Description**: Displays the results of recent matches, including goals and assists.
    - **Example**: 
    ```bash
    GET match_results
    ```

15. **GET upcoming_matches**
    - **Description**: Lists upcoming fixtures in the football league.
    - **Example**: 
    ```bash
    GET upcoming_matches
    ```

## Technical Details

### Languages and Tools

- **C++**: The core language used for the CLI and handling user interactions.
- **File I/O**: The system uses CSV files to store and retrieve player stats, team data, and performance updates, allowing persistence across sessions.
### File Structure

The project has the following directory structure:  
        data/  
        │  
        ├── premier_league.csv           # Contains player data: names, positions, stats  
        ├── weeks_stats/                 # Directory for weekly performance stats (week_1.csv, week_2.csv, etc.)  
        │   ├── week_1.csv  
        │   ├── week_2.csv  
        │   └── week_3.csv  
    

## Note:
Only Phase 2 codes will be uploaded as the final version. Phase 2 builds upon the foundational features developed in Phase 1. It introduces more advanced management features, including transfer windows, dynamic team performance tracking, and integration with player statistics.
