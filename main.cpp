#include "TodoList.h"
#include "ConsoleDisplay.h"
#include <iostream>
#include <map>
#include <sstream>
#include <exception>
#include <iomanip>

int main() {
    std::map<std::string, TodoList> todoLists;
    std::string activeListName;

    std::cout << "Welcome to Todo List Manager!\n";

    while (activeListName.empty()) {
        std::cout << "Enter a name for your first TodoList: ";
        std::getline(std::cin, activeListName);

        if (activeListName.empty()) {
            std::cout << "TodoList name cannot be empty!\n";
        } else {
            todoLists.emplace(activeListName, TodoList(activeListName));
            std::cout << "TodoList '" << activeListName << "' created and selected.\n";
        }
    }

    while (true) {
        std::cout << "\nTodo List Manager\n";
        std::cout << "1. Create a new TodoList\n";
        std::cout << "2. Select an existing TodoList\n";
        std::cout << "3. Display all TodoLists\n";
        std::cout << "4. Manage selected TodoList\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                std::cout << "Enter a name for the new TodoList: ";
                std::string listName;
                std::getline(std::cin, listName);

                if (todoLists.find(listName) != todoLists.end()) {
                    std::cout << "TodoList with this name already exists!\n";
                } else {
                    todoLists.emplace(listName, TodoList(listName));
                    std::cout << "TodoList '" << listName << "' created.\n";
                }
                break;
            }
            case 2: {
                std::cout << "Enter the name of the TodoList to select: ";
                std::string listName;
                std::getline(std::cin, listName);

                if (todoLists.find(listName) == todoLists.end()) {
                    std::cout << "TodoList not found!\n";
                } else {
                    activeListName = listName;
                    std::cout << "TodoList '" << activeListName << "' selected.\n";
                }
                break;
            }
            case 3: {
                std::cout << "\nAvailable TodoLists:\n";
                for (const auto& pair : todoLists) {
                    std::cout << "- " << pair.first << (pair.first == activeListName ? " (active)" : "") << std::endl;
                }
                break;
            }
            case 4: {
                if (todoLists.find(activeListName) == todoLists.end()) {
                    std::cout << "No active TodoList selected. Please select one first.\n";
                    break;
                }

                TodoList& todoList = todoLists[activeListName];
                ConsoleDisplay display(todoList); // Attaching the observer

                int subChoice;
                do {
                    std::cout << "\nManaging TodoList: " << activeListName << "\n";
                    std::cout << "1. Add Activity\n";
                    std::cout << "2. Remove Activity\n";
                    std::cout << "3. Edit Activity\n";
                    std::cout << "4. Mark Activity as Completed\n";
                    std::cout << "5. Display Activities\n";
                    std::cout << "6. Show Activity Counts\n";
                    std::cout << "7. Find Activities by Name\n";
                    std::cout << "8. Find Activities by Due Date\n";
                    std::cout << "9. Save to File\n";
                    std::cout << "10. Load from File\n";
                    std::cout << "11. Rename TodoList\n";
                    std::cout << "0. Back\n";
                    std::cout << "Choose an option: ";
                    std::cin >> subChoice;
                    std::cin.ignore();

                    std::string identifier;

                    switch (subChoice) {
                        case 1: {
                            std::string description;
                            std::cout << "Enter activity description: ";
                            std::getline(std::cin, description);

                            if (description.empty()) {
                                std::cerr << "Error: Activity description cannot be empty!\n";
                                break;
                            }

                            std::string dueDateStr;
                            std::time_t dueDate;
                            bool validDate = false;

                            while (!validDate) {
                                std::cout << "Enter due date (YYYY-MM-DD HH:MM): ";
                                std::getline(std::cin, dueDateStr);

                                std::tm tm = {};
                                std::istringstream ss(dueDateStr);
                                if (ss >> std::get_time(&tm, "%Y-%m-%d %H:%M")) {
                                    tm.tm_isdst = -1;
                                    dueDate = std::mktime(&tm);

                                    if (dueDate != -1) {
                                        validDate = true;
                                    } else {
                                        std::cerr << "Error: Invalid date value!\n";
                                    }
                                } else {
                                    std::cerr << "Error: Invalid date format! Please use YYYY-MM-DD HH:MM.\n";
                                }
                            }

                            Activity newActivity(description, dueDate);
                            todoList.addActivity(newActivity);
                            std::cout << "Activity added: " << description << " (Due: " << std::ctime(&dueDate) << ")";
                            break;
                        }
                        case 2: {
                            std::cout << "Enter activity number or name to remove: ";
                            std::getline(std::cin, identifier);

                            try {
                                todoList.removeActivity(identifier);
                            } catch (const std::exception& e) {
                                std::cerr << "Error: " << e.what() << std::endl;
                            }
                            break;
                        }
                        case 3: {
                            bool validInput = false;

                            while (!validInput) {
                                std::cout << "Enter activity number or name to edit: ";
                                std::getline(std::cin, identifier);

                                try {
                                    todoList.editActivity(identifier);
                                    validInput = true;
                                } catch (const std::exception& e) {
                                    std::cerr << "Error: " << e.what() << "\nPlease try again.\n";
                                }
                            }
                            break;
                        }
                        case 4: {
                            std::cout << "Enter activity number or name to mark as completed: ";
                            std::getline(std::cin, identifier);
                            todoList.markActivityAsCompleted(identifier);
                            break;
                        }
                        case 5: {
                            std::cout << todoList.toString();
                            break;
                        }
                        case 6: {
                            std::cout << "Total activities: " << todoList.getTotalActivities() << std::endl;
                            std::cout << "Pending activities: " << todoList.getPendingActivities() << std::endl;
                            break;
                        }
                        case 7: {
                            std::string name;
                            std::cout << "Enter activity name: ";
                            std::getline(std::cin, name);

                            auto results = todoList.findActivitiesByName(name);
                            if (results.empty()) {
                                std::cout << "No activities found with that name.\n";
                            } else {
                                std::cout << "Found " << results.size() << " activity/activities:\n";
                                for (const auto& activity : results) {
                                    std::cout << "- " << activity.getDescription() << " ["
                                              << (activity.isCompleted() ? "Done" : "Not Done") << "]\n";
                                }
                            }
                            break;
                        }
                        case 8: {
                            std::string dueDateStr;
                            std::time_t dueDate;
                            bool validDate = false;

                            while (!validDate) {
                                std::cout << "Enter due date (YYYY-MM-DD HH:MM): ";
                                std::getline(std::cin, dueDateStr);

                                std::tm tm = {};
                                std::istringstream ss(dueDateStr);
                                if (ss >> std::get_time(&tm, "%Y-%m-%d %H:%M")) {
                                    dueDate = std::mktime(&tm);
                                    validDate = true;
                                } else {
                                    std::cerr << "Error: Invalid date format! Please use YYYY-MM-DD HH:MM.\n";
                                }
                            }

                            auto results = todoList.findActivitiesByDueDate(dueDate);
                            if (results.empty()) {
                                std::cout << "No activities found with that due date.\n";
                            } else {
                                std::cout << "Found " << results.size() << " activity/activities:\n";
                                for (const auto& activity : results) {
                                    std::cout << "- " << activity.getDescription() << " ["
                                              << (activity.isCompleted() ? "Done" : "Not Done") << "] (Due: "
                                              << std::ctime(&dueDate) << ")\n";
                                }
                            }
                            break;
                        }
                        case 9: {
                            std::string filename;
                            std::cout << "Enter filename: ";
                            std::getline(std::cin, filename);
                            todoList.saveToFile(filename);
                            break;
                        }
                        case 10: {
                            std::string filename;
                            std::cout << "Enter filename: ";
                            std::getline(std::cin, filename);

                            try {
                                todoList.loadFromFile(filename);
                            } catch (const std::exception& e) {
                                std::cerr << "Error loading file: " << e.what() << std::endl;
                            }
                            break;
                        }
                        case 11: {
                            std::cout << "Enter new name for this TodoList: ";
                            std::string newName;
                            std::getline(std::cin, newName);

                            if (todoLists.find(newName) != todoLists.end()) {
                                std::cout << "A TodoList with this name already exists!\n";
                            } else {
                                todoLists.emplace(newName, std::move(todoLists[activeListName]));
                                todoLists.erase(activeListName);
                                activeListName = newName;
                                std::cout << "TodoList renamed to '" << newName << "'.\n";
                            }
                            break;
                        }
                        case 0: // Back
                            break;

                        default:
                            std::cout << "Invalid choice. Please try again.\n";
                        break;
                    }
                } while (subChoice != 0);
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    std::cout << "Exiting...\n";
    return 0;
}