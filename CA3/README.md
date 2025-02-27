# Course Scheduling System

## Overview

This project is a C++ application designed to solve the problem of scheduling courses for teachers while considering their available days and time slots. The system processes input data about teachers, courses, and their schedules, and then outputs the best possible schedule with course assignments, including time slots and assigned teachers.

The scheduling algorithm ensures that no teacher is double-booked, and courses are scheduled within the available time slots for each teacher.

The project follows a **Top-Down Design** approach. The main problem is broken down into smaller, manageable components and then solved step-by-step, starting with the high-level requirements and gradually refining the design to meet those requirements. This approach ensures that each subproblem is well-defined and the overall system is efficient and easy to maintain.

## Features
- **Teacher and Course Data Input**: Accepts data for teachers, courses, and available time slots.
- **Scheduling Algorithm**: Ensures optimal scheduling of courses while considering teacher availability and course timing.
- **Output**: Displays the assigned teachers and their course schedules with respective time slots.
- **Error Handling**: If no suitable schedule can be found for a course, it outputs "Not Found" for that course.

## Project Structure

The project consists of the following core components:

- **Teacher Data**: Includes the teacher’s name, available days, and the courses they can teach.
- **Course Data**: Each course includes its name, the days it is offered, and the time range for the class.
- **Scheduling Logic**: The core of the project, ensuring that each course is assigned to a teacher who is available at the right time.
- **Output Generation**: The results are displayed in a sorted manner, showing each course with the assigned teacher(s) and their respective time slots.

## Input Format

### Teachers Input:
Each teacher's data is input in the following format:

<teacher_name> <number_of_free_days> <free_days> <number_of_courses> <courses>


- **teacher_name**: Name of the teacher.
- **number_of_free_days**: The number of days the teacher is free.
- **free_days**: The specific days the teacher is available.
- **number_of_courses**: The number of courses the teacher can teach.
- **courses**: A list of courses the teacher can teach.

### Courses Input:
Each course's data is input in the following format:

<course_name> <day1> <day2> <start_time> <end_time>


- **course_name**: Name of the course.
- **day1, day2**: The two days the course is scheduled.
- **start_time** and **end_time**: The start and end times of the course in **hh:mm** format.

## Example Input:

    2
    Hamid 3 Saturday Monday Wednesday 2 Math
    Physics
    Amin 3 Saturday Sunday Monday 2 Math Science
    3
    Math Saturday Monday 07:30 10:00
    Physics Saturday Wednesday 08:00 11:00
    Science Monday Sunday 07:30 13:00


## Output Format

For each course, the system outputs the following:

<course_name> <teacher_name>: <start_time> <end_time> <teacher_name>: <start_time> <end_time>


If a course cannot be scheduled, it will show:

<course_name> Not Found


### Example Output:

    Math
    Amin: 07:30 09:00
    Hamid: 07:30 09:00
    Physics
    Hamid: 09:30 11:00
    Not Found
    Science
    Amin: 09:30 11:00
    Amin: 11:30 13:00