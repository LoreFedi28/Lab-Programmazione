#include "TodoList.h"
#include <iostream>
#include <iomanip>
#include <limits>

int main() {
    TodoList todoList;
    std::string defaultFilename = "tasks.txt";
    todoList.loadFromFile(defaultFilename); // Load tasks from file at startup
    std::cout << "Loaded tasks from " << defaultFilename << std::endl;

    int choice;

    do {
        std::cout << "\nTodo List\n";
        std::cout << "1. Add Activity\n";
        std::cout << "2. Remove Activity\n";
        std::cout << "3. Display Activities\n";
        std::cout << "4. Save to File\n";
        std::cout << "5. Load from File\n";
        std::cout << "6. Mark Activity as Completed\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";
        if (!(std::cin >> choice)) {
            std::cin.clear(); // Reset error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }


        switch (choice) {
            case 1: {
                std::cin.ignore(); // Clear input buffer
                std::string description;
                std::cout << "Enter activity description: ";
                std::getline(std::cin, description);

                std::cout << "Enter due date (YYYY-MM-DD HH:MM): ";
                std::string dueDateStr;
                std::getline(std::cin, dueDateStr);

                std::tm tm = {};
                std::istringstream ss(dueDateStr);
                ss >> std::get_time(&tm, "%Y-%m-%d %H:%M"); // Convert string to time structure
                std::time_t dueDate = std::mktime(&tm); // Convert to timestamp

                todoList.addActivity(Activity(description, false, dueDate));
                break;
            }
            case 2: {
                size_t index;
                std::cout << "Enter activity number to remove: ";
                std::cin >> index;
                todoList.removeActivity(index - 1);  // We don't pass true, so it asks for confirmation
                break;
            }
            case 3:
                todoList.displayActivities();
            break;
            case 4: {
                std::string filename;
                std::cout << "Enter filename: ";
                std::cin >> filename;
                todoList.saveToFile(filename);
                break;
            }
            case 5: {
                std::string filename;
                std::cout << "Enter filename: ";
                std::cin >> filename;
                todoList.loadFromFile(filename);
                break;
            }
            case 6: {
                size_t index;
                std::cout << "Enter activity number to mark as completed: ";
                std::cin >> index;
                todoList.markActivityAsCompleted(index - 1);
                break;
            }
            case 0:
                std::cout << "Exiting...\n";
            break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
