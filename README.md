# Todo List Project

This is a C++ project that implements a **Todo List** application with advanced **task management** features.
The application allows users to add, edit, remove, and organize activities with due dates while ensuring **automatic UI updates** using the **Observer Pattern**.

## Features

### **Activity Management**
- Add activities with **descriptions** and **due dates**.
- **Edit** activities: change description, status, or due date.
- **Mark activities as completed** or **not completed**.
- **Remove activities** by number or name with **error handling**.
- **Find activities** by name or due date.
- **Display** all activities, sorted by due date.

### **File Operations**
- Save activities to a file in a **serialized format**.
- Load activities from a file and **restore the list**.
- **Handle invalid or missing files** safely.

### **Design Patterns**
- **Observer Pattern**: The user interface updates automatically whenever activities are modified.

### **Observer Pattern Implementation**
- `Subject.h` → Defines the **Subject** class (observable objects).
- `Observer.h` → Defines the **Observer** interface.
- **TodoList** acts as a **Subject**, notifying observers whenever a change occurs.
- **ConsoleDisplay** is an **Observer**, updating the UI in response to changes.

### **Robust Input Handling**
- **Error handling** for invalid or empty inputs.
- **Looped prompts** until a valid input is provided.
- **Date validation** with a structured format (YYYY-MM-DD HH:MM).

### **Unit Testing with Google Test**
- Comprehensive tests for `Activity` and `TodoList` classes.
- **Mock Observer** to test the Observer Pattern behavior.
- **Test cases include**:
    - Serialization & deserialization.
    - Adding, editing, and removing activities.
    - Marking activities as completed.
    - File saving & loading.
    - Observer notifications.

---

## Files & Structure

### **Source Code**
- `Activity.h` / `Activity.cpp` → Defines the **Activity** class (tasks with descriptions & due dates).
- `TodoList.h` / `TodoList.cpp` → Implements the **Todo List** with activity management.
- `Subject.h` → Defines the **Subject** class for the **Observer Pattern**.
- `Observer.h` → Interface for **Observer Pattern**.
- `ConsoleDisplay.h` / `ConsoleDisplay.cpp` → Implements an **observer** that updates the UI.
- `main.cpp` → **Entry point** for the application, with a **console menu** for user interaction.

### **Unit Tests**
- `Test/TodoListTest.cpp` → **Google Test suite** covering:
    - **Serialization & deserialization**.
    - **Adding/removing activities**.
    - **Marking activities as completed**.
    - **Editing activities** with valid & invalid inputs.
    - **Testing observer notifications**.
- `Test/MockObserver.h` → **Mock class** for testing UI updates.

---

## How to Build and Run

### **Prerequisites**
- **C++17 or higher** (g++, clang++, MSVC).
- **CMake** (recommended for building).
- **Google Test** (for running unit tests).

### **Build Instructions**
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

### **Run Tests**
1. Compile and execute the test suite:
   ```bash
   ./runLabProgrammazioneTest
   ```

---

## Usage

Run the program and interact using the **menu-based interface**.

### **Main Menu**
```
Todo List Manager
1. Create a new TodoList
2. Select an existing TodoList
3. Display all TodoLists
4. Manage selected TodoList
0. Exit
Choose an option: 
```
- Enter `1` to create a new list.
- Enter `2` to select an existing list.
- Enter `4` to **manage** tasks inside the active list.

### **Managing a Todo List**
```
Managing TodoList: Work
1. Add Activity
2. Remove Activity
3. Edit Activity
4. Mark Activity as Completed
5. Display Activities
6. Show Activity Counts
7. Find Activities by Name
8. Find Activities by Due Date
9. Save to File
10. Load from File
11. Rename TodoList
0. Back
Choose an option:
```

---

## Example Interaction

### **Adding a new activity**
```
Choose an option: 1
Enter activity description: Complete the C++ project
Enter due date (YYYY-MM-DD HH:MM): 2025-04-10 15:00

Todo List Updated:
--- Todo List: Work ---
1. Complete the C++ project [Not Done] (Due: Thu Apr 10 15:00:00 2025)
```

### **Marking an activity as completed**
```
Choose an option: 4
Enter activity number or name to mark as completed: 1

Todo List Updated:
--- Todo List: Work ---
1. Complete the C++ project [Done] (Due: Thu Apr 10 15:00:00 2025)
```

### **Editing an activity**
```
Choose an option: 3
Enter activity number or name to edit: 1
Editing Activity: Complete the C++ project
Enter new description (or press ENTER to keep current): Finalize C++ Report
Is the activity completed? (y/n, press ENTER to keep current): 
Enter new due date (YYYY-MM-DD HH:MM, press ENTER to keep current): 2025-04-15 18:00

Todo List Updated:
--- Todo List: Work ---
1. Finalize C++ Report [Done] (Due: Tue Apr 15 18:00:00 2025)
```

### **Saving and Loading**
```
Choose an option: 9
Enter filename: tasks.txt
```
```
Choose an option: 10
Enter filename: tasks.txt
Todo List Updated!
```

---

## Edge Cases Tested
**Empty Inputs:** Pressing Enter without entering data keeps values unchanged.  
**Invalid Dates:** Shows an error if the date format is incorrect.  
**Editing with Duplicate Names:** If multiple tasks have the same name, the user selects which one to edit.  
**Loading Invalid Files:** Handles file errors gracefully.

---

## Author
This project was created by **Lorenzo Fedi**.

## License
This project is open-source and available under the **MIT License**.