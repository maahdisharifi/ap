# Memory Logging and Sentiment Analysis Application

## Project Description:
This C++ project is a personal memory logging application that allows users to record daily events, capture sentiments through positive word detection, and retrieve past logs based on various queries. The system includes functions to track and display daily memories, show the longest entry, and identify the best day based on the occurrence of positive words. The project implements basic text processing, sentiment analysis, and data storage mechanisms.

## Key Features:
- **Day Logging**: Users can log daily memories by specifying the date and adding text for each day. The system supports multiple entries per day.
- **View Logs**: Users can view the content of a specific day or the longest day based on the length of the entry.
- **Best Day Detection**: The application can identify the "best day" by counting positive words in the entries, based on a predefined list of positive words.
- **Command Interface**: A simple command-line interface allows users to interact with the program by using commands like `start_day`, `show_day`, `show_the_longest_day`, and `show_the_best_day`.
- **File I/O**: The program reads from a file containing positive words (`positive-words.txt`) to evaluate the sentiment of the daily logs.

## Technologies Used:
- **C++**: Utilized for core functionality, including string manipulation, file handling, and data structures such as vectors and structs.
- **Text Processing**: Involves parsing user input and using string functions to analyze and store memory logs.
- **Sentiment Analysis**: Sentiment analysis is performed using a list of positive words to determine the most "positive" day.

## Usage:
- **To start a new day log**:
    ```
    start_day day/month/year
    ```
    Followed by the memory entry for that day.

- **To view a day's entry**:
    ```
    show_day day/month/year
    ```

- **To view the longest day (based on memory length)**:
    ```
    show_the_longest_day
    ```

- **To determine the best day (based on positive word occurrence)**:
    ```
    show_the_best_day
    ```

## Code Overview:
- The program uses a `struct` (`info`) to store memory data, including the date, caption, and word occurrences.
- It provides a comparison function to determine which day is the longest or the best based on sentiment analysis.
- A basic file handling system is used to load and count positive words from a file (`positive-words.txt`).

## How to Run:
1. Compile the code using a C++ compiler (e.g., `g++`).
2. Provide input through the terminal as described in the usage section.
3. Ensure the `positive-words.txt` file is available in the same directory for sentiment analysis.

## Example Input and Output:

**Input**:

start_day 24/9/2022 Today was a long day I do not even know where to begin
start_day 25/9/2022 Boring day
show_the_longest_day


**Output**:

24/9/2022 Today was a long day I do not even know where to begin