# Employee and Team Management System

## Overview

This project is a C++ application designed for managing employee working hours, salaries, and team bonuses. It provides an automated system for tracking and calculating the total working hours, salary, and bonuses of employees and their respective teams. The system incorporates various commands to generate reports on employee salaries, team salaries, and employee working hours.

The design follows **Object-Oriented Programming (OOP)** principles, and it handles employee data, working hours, salary configurations, and team management using well-defined classes and structures.

## Features
- **Employee Management**: Stores employee data including personal information, working hours, salary, and level.
- **Team Management**: Manages team structures, including team heads, members, and team-specific bonuses.
- **Salary Calculation**: Calculates salaries based on working hours and tax percentages, while considering team bonuses.
- **Working Hours Report**: Generates reports on total working hours per day, per employee, or per team.
- **Bonus Management**: Updates and reports bonuses for teams based on working hours and variance.
- **Salary Configuration**: Configures and updates salary structures for different employee levels (junior, senior, expert, team lead).
- **Reports**: Generates various reports including individual employee salaries, team salaries, and total working hours.

## Command List

1. **report_salaries**
    - **Description**: Displays the total working hours and earnings for all employees in the company.
    - **Arguments**: None
    - **Usage Example**:
    ```
    report_salaries
    ```

2. **report_employee_salary**
    - **Description**: Displays detailed salary data for a specific employee, including their total working hours, earnings, and bonuses.
    - **Arguments**:
        - `employee_id`: The ID of the employee.
    - **Usage Example**:
    ```
    report_employee_salary <employee_id>
    ```

3. **report_team_salary**
    - **Description**: Displays salary details for a specific team, including the total salary and bonuses for all members of the team.
    - **Arguments**:
        - `team_id`: The ID of the team.
    - **Usage Example**:
    ```
    report_team_salary <team_id>
    ```

4. **report_total_hours_per_day**
    - **Description**: Shows the total working hours for each day within a given range. This helps identify peak working days.
    - **Arguments**:
        - `start_date`: The start date of the range.
        - `end_date`: The end date of the range.
    - **Usage Example**:
    ```
    report_total_hours_per_day <start_date> <end_date>
    ```

5. **report_employee_per_hour**
    - **Description**: Provides the average working hours of employees within a given period.
    - **Arguments**:
        - `start_date`: The start date of the period .
        - `end_date`: The end date of the period .
    - **Usage Example**:
    ```
    report_employee_per_hour <start_date> <end_date>
    ```

6. **show_salary_config**
    - **Description**: Displays the salary configuration for a given employee level, including base salary, bonuses, and other factors affecting compensation.
    - **Arguments**:
        - `employee_level`: The level of the employee (e.g., "junior", "senior").
    - **Usage Example**:
    ```
    show_salary_config <employee_level>
    ```

7. **update_salary_config**
    - **Description**: Updates the salary configuration for a given employee level, allowing modifications to base salary, bonuses, etc.
    - **Arguments**:
        - `employee_level`: The level of the employee (e.g., "junior", "senior").
        - `base_salary`: The new base salary to be set.
        - `bonus_percentage`: The new bonus percentage to be applied.
    - **Usage Example**:
    ```
    update_salary_config <employee_level> <base_salary> <bonus_percentage>
    ```

8. **add_working_hours**
    - **Description**: Adds working hours for an employee on a specific day, updating their total hours worked.
    - **Arguments**:
        - `employee_id`: The ID of the employee.
        - `date`: The date on which hours are being added.
        - `hours`: The number of hours worked on that day.
    - **Usage Example**:
    ```
    add_working_hours <employee_id> <date> <hours>
    ```

9. **delete_working_hours**
    - **Description**: Removes working hours for an employee on a specific day, updating their total hours worked.
    - **Arguments**:
        - `employee_id`: The ID of the employee.
        - `date`: The date from which hours are being removed .
    - **Usage Example**:
    ```
    delete_working_hours <employee_id> <date>
    ```

10. **update_team_bonus**
    - **Description**: Updates the bonus percentage for a given team based on their performance or other factors.
    - **Arguments**:
        - `team_id`: The ID of the team.
        - `new_bonus_percentage`: The new bonus percentage to be applied.
    - **Usage Example**:
    ```
    update_team_bonus <team_id> <new_bonus_percentage>
    ```

11. **find_teams_for_bonus**
    - **Description**: Identifies teams eligible for a bonus based on working hours and variance. This can be used to reward high-performing teams.
    - **Arguments**:
        - `minimum_hours`: The minimum number of hours that a team must have worked to be eligible for a bonus.
        - `variance_threshold`: The threshold variance that teams must meet in their working hours.
    - **Usage Example**:
    ```
    find_teams_for_bonus <minimum_hours> <variance_threshold>
    ```


## Data Files

The system reads and processes data from several CSV files, each containing specific information about employees, teams, and salary configurations:

- **employees.csv**: Contains data about employees, including ID, name, age, and level.
- **working_hours.csv**: Tracks the working hours for each employee on specific days.
- **teams.csv**: Contains data about teams, including team ID, head ID, member IDs, and bonus criteria.
- **salary_configs.csv**: Contains the salary configurations for each employee level, including base salary, hourly rates, and tax percentages.

