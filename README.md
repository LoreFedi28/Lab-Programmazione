# Todo List Project

This is a C++ project that implements a simple Todo List application. The application allows users to manage tasks (activities) by adding, removing, displaying, saving to a file, and loading from a file.

## Features

- **Activity Management**:
  - Add activities with descriptions and due dates.
  - Mark activities as completed or not completed.
  - Remove activities by index with confirmation.
  - Display all activities with their statuses, sorted by due date.

- **File Operations**:
  - Save activities to a file in a serialized format.
  - Load activities from a file, restoring the list.
  - Automatically load activities from the last saved file at startup.

- **Unit Testing**:
  - Comprehensive tests for `Activity` and `TodoList` classes using Google Test.

## Files

### Source Code
- `Activity.h` and `Activity.cpp`: Define and implement the `Activity` class.
- `TodoList.h` and `TodoList.cpp`: Define and implement the `TodoList` class.
- `main.cpp`: Entry point for the application, providing a simple menu interface.

### Unit Tests
- `Test/TodoListTest.cpp`: Unit tests using Google Test for key functionalities:
  - Serialization and deserialization of activities.
  - Adding and removing activities in the list.
  - Marking activities as completed.
  - Saving and loading activities from files.

## How to Build and Run

### Prerequisites
- A C++ compiler supporting C++17 or higher (e.g., g++, clang++)
- CMake (optional but recommended for building)
- Google Test (for running unit tests)

### Build Instructions

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-folder>
   ```

2. Compile the source code using CMake:
   ```bash
   mkdir -p cmake-build-debug
   cd cmake-build-debug
   cmake ..
   cmake --build .
   ```

3. Run the application:
   ```bash
   ./LabProgrammazione
   ```

### Run Tests

1. Compile the test suite:
   ```bash
   ./runLabProgrammazioneTest
   ```

## Usage

1. Run the application.
2. Use the menu to interact with the Todo List:
   - Add a new activity by entering a description and a due date.
   - Remove an activity by specifying its number (confirmation required).
   - Display the list of activities, sorted by due date.
   - Save or load activities using file names.
   - Mark an activity as completed.

## Example Interaction

```
Todo List
1. Add Activity
2. Remove Activity
3. Display Activities
4. Save to File
5. Load from File
6. Mark Activity as Completed
0. Exit
Choose an option: 1
Enter activity description: Complete the C++ project
Enter due date (YYYY-MM-DD HH:MM): 2025-03-10 15:00
Todo List
1. Add Activity
2. Remove Activity
3. Display Activities
4. Save to File
5. Load from File
6. Mark Activity as Completed
0. Exit
Choose an option: 3
1. Complete the C++ project [Not Done] (Due: Mon Mar 10 15:00:00 2025)
```

## Author
This project was created by Lorenzo Fedi.

## License
This project is open-source and available under the MIT License.

