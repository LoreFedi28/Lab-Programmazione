# Todo List Project

This is a C++ project that implements a simple Todo List application. The application allows users to manage tasks (activities) by adding, removing, displaying, saving to a file, and loading from a file.

## Features

- **Activity Management**:
  - Add activities with descriptions.
  - Mark activities as completed or not completed.
  - Remove activities by index.
  - Display all activities with their statuses.

- **File Operations**:
  - Save activities to a file in a serialized format.
  - Load activities from a file, restoring the list.

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
  - Saving and loading activities from files.

## How to Build and Run

### Prerequisites
- A C++ compiler supporting C++11 or higher (e.g., g++, clang++)
- CMake (optional but recommended for building)
- Google Test (for running unit tests)

### Build Instructions

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-folder>
   ```

2. Compile the source code:
   ```bash
   g++ main.cpp Activity.cpp TodoList.cpp -o TodoListApp
   ```

3. Run the application:
   ```bash
   ./TodoListApp
   ```

### Run Tests

1. Compile the test suite:
   ```bash
   g++ -std=c++11 -I/path/to/gtest/include -L/path/to/gtest/lib Test/TodoListTest.cpp Activity.cpp TodoList.cpp -lgtest -lgtest_main -pthread -o TodoListTest
   ```

2. Run the tests:
   ```bash
   ./TodoListTest
   ```

## Usage

1. Run the application.
2. Use the menu to interact with the Todo List:
   - Add a new activity by entering a description.
   - Remove an activity by specifying its number.
   - Display the list of activities.
   - Save or load activities using file names.

## Example Interaction

```
Todo List
1. Add Activity
2. Remove Activity
3. Display Activities
4. Save to File
5. Load from File
0. Exit
Choose an option: 1
Enter activity description: Complete the C++ project
Todo List
1. Add Activity
2. Remove Activity
3. Display Activities
4. Save to File
5. Load from File
0. Exit
Choose an option: 3
1. Complete the C++ project [Not Done]
```

## Author
This project was created by Lorenzo Fedi.

## License
This project is open-source and available under the MIT License.

