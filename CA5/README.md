# Mission Assignment and Tracking System

## Overview

This project provides a Mission Assignment and Tracking System for drivers, with a focus on **utilizing polymorphism and inheritance**. The system allows the assignment of different types of missions (time-based, distance-based, and count-based) to drivers, tracks their progress, and provides rewards upon completion. The system also includes features for managing mission statuses and ensuring that no duplicate missions are assigned.

The main goal of this project is to demonstrate the principles of polymorphism and inheritance in object-oriented programming. Through the use of these concepts, the project enables flexible mission handling and driver-task assignment. The system is structured to allow easy extension for additional mission types in the future, as well as offering dynamic behavior through polymorphic function calls.

## Key Features

- **Mission Assignment**: Allows the assignment of time, distance, and count-based missions to drivers, each with its own specific parameters.
- **Mission Tracking**: Tracks the progress and completion status of assigned missions.
- **Rewards System**: Provides rewards for completed missions based on the type and completion.
- **Polymorphism**: Uses polymorphism to define a common interface for different mission types (time, distance, count), allowing the system to dynamically handle mission-specific logic.
- **Inheritance**: The mission types (time, distance, and count) all inherit from a common mission base class, ensuring a structured and extendable codebase.
- **Real-time Updates**: The system uses timestamps to monitor mission progress and calculate rewards.

## Command List

1. **add_time_mission**
    - **Description**: Adds a time-based mission for a driver.
    - **Arguments**:
        - `mission_id`: Unique identifier for the mission.
        - `start_timestamp`: Start time of the mission (in Unix timestamp format).
        - `end_timestamp`: End time of the mission (in Unix timestamp format).
        - `target_time_in_minutes`: The target time for completion in minutes.
        - `reward_amount`: The reward for completing the mission.
    - **Example**:
    ```bash
    add_time_mission 1 1680347116 1980349516 10000 200000
    ```

2. **add_distance_mission**
    - **Description**: Adds a distance-based mission for a driver.
    - **Arguments**:
        - `mission_id`: Unique identifier for the mission.
        - `start_timestamp`: Start time of the mission (in Unix timestamp format).
        - `end_timestamp`: End time of the mission (in Unix timestamp format).
        - `target_distance_in_meters`: The target distance for completion in meters.
        - `reward_amount`: The reward for completing the mission.
    - **Example**:
    ```bash
    add_distance_mission 3 1076347116 1580349516 250000 200000
    ```

3. **add_count_mission**
    - **Description**: Adds a count-based mission for a driver.
    - **Arguments**:
        - `mission_id`: Unique identifier for the mission.
        - `start_timestamp`: Start time of the mission (in Unix timestamp format).
        - `end_timestamp`: End time of the mission (in Unix timestamp format).
        - `target_number`: The target number for completion.
        - `reward_amount`: The reward for completing the mission.
    - **Example**:
    ```bash
    add_count_mission 2 1076347116 1580349516 70 200000
    ```

4. **assign_mission**
    - **Description**: Assigns a specific mission to a driver.
    - **Arguments**:
        - `mission_id`: Unique identifier for the mission.
        - `driver_id`: Unique identifier for the driver.
    - **Example**:
    ```bash
    assign_mission 1 1
    ```

5. **record_ride**
    - **Description**: Records the completion of a ride for a driver, marking the mission as completed and calculating the reward.
    - **Arguments**:
        - `start_timestamp`: Start time of the ride.
        - `end_timestamp`: End time of the ride.
        - `driver_id`: Unique identifier for the driver.
        - `distance`: Distance covered during the ride.
    - **Example**:
    ```bash
    record_ride 1680347116 1680349516 1 20000
    ```

6. **show_missions_status**
    - **Description**: Displays the current status of missions assigned to a specific driver.
    - **Arguments**:
        - `driver_id`: Unique identifier for the driver.
    - **Example**:
    ```bash
    show_missions_status 1
    ```

## Usage

- **Mission Assignment**: You can assign missions based on the type (time, distance, or count) by using the corresponding command (`add_time_mission`, `add_distance_mission`, or `add_count_mission`).
- **Driver Assignment**: Once missions are created, they can be assigned to drivers using the `assign_mission` command.
- **Mission Tracking**: The system tracks mission progress in real-time, and the completion status can be checked using `show_missions_status`.
- **Recording Rides**: Once a driver completes a ride, use the `record_ride` command to mark the mission as completed and calculate the rewards.

## Example Workflow

1. **Add a time-based mission**:
    ```bash
    add_time_mission 1 1680347116 1980349516 10000 200000
    ```

2. **Assign the mission to a driver**:
    ```bash
    assign_mission 1 1
    ```

3. **Record the completion of the ride**:
    ```bash
    record_ride 1680347116 1680349516 1 20000
    ```

4. **Check the mission status for the driver**:
    ```bash
    show_missions_status 1
    ```