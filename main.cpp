#include "TodoList.h"
#include "ConsoleDisplay.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <exception> // Needed for handling exceptions

int main() {
    TodoList todoList;
    ConsoleDisplay display(todoList); // Attaching the observer

    std::string defaultFilename = "tasks.txt";

    // Try loading tasks from the default file
    try {
        todoList.loadFromFile(defaultFilename);
        std::cout << "Loaded tasks from " << defaultFilename << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error loading tasks: " << e.what() << std::endl;
    }

    int choice;
    do {
        std::cout << "\nTodo List\n";
        std::cout << "1. Add Activity\n";
        std::cout << "2. Remove Activity\n";
        std::cout << "3. Display Activities\n"; // No need to manually call it
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
                std::cout << "Activities are already displayed automatically.\n";
                break; // No need to call todoList.displayActivities()
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

                // Handle file loading exceptions
                try {
                    todoList.loadFromFile(filename);
                } catch (const std::exception& e) {
                    std::cerr << "Error loading file: " << e.what() << std::endl;
                }
                break;
            }
            case 6: {
                size_t index;
                std::cout << "Enter activity number to mark as completed: ";
                std::cin >> index;
                todoList.markActivityAsCompleted(index - 1);
                break;
            }
            case 0: {
                char confirmExit;
                std::cout << "Are you sure you want to exit? (y/n): ";
                std::cin >> confirmExit;
                if (confirmExit != 'y' && confirmExit != 'Y') {
                    choice = -1; // Cancel exit
                }
                break;
            }
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    std::cout << "Exiting...\n";
    return 0;
}
