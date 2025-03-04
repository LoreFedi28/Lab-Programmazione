#include "TodoList.h"
#include <iostream>
#include <limits>

int main() {
    TodoList todoList;
    int choice;

    do {
        std::cout << "\nTodo List\n";
        std::cout << "1. Add Activity\n";
        std::cout << "2. Remove Activity\n";
        std::cout << "3. Display Activities\n";
        std::cout << "4. Save to File\n";
        std::cout << "5. Load from File\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";
        if (!(std::cin >> choice)) {
            std::cin.clear(); // Resetta lo stato di errore
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Pulisce il buffer
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }


        switch (choice) {
            case 1: {
                std::cin.ignore(); // Clear input buffer
                std::string description;
                std::cout << "Enter activity description: ";
                std::getline(std::cin, description);
                todoList.addActivity(Activity(description));
                break;
            }
            case 2: {
                size_t index;
                std::cout << "Enter activity number to remove: ";
                std::cin >> index;
                todoList.removeActivity(index - 1);
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
            case 0:
                std::cout << "Exiting...\n";
            break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
