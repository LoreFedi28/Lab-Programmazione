#include "TodoList.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <utility>

// Default constructor
TodoList::TodoList() : name("UnnamedList") {}

// Constructor with name
TodoList::TodoList(std::string  listName) : name(std::move(listName)) {}

// Get the name of the list
std::string TodoList::getName() const {
    return name;
}

// Set a new name for the list
void TodoList::setName(const std::string& newName) {
    name = newName;
    notifyObservers();
}

// Getter for the activities list
std::vector<Activity> TodoList::getActivities() const {
    return activities;
}

// Get total number of activities
size_t TodoList::getTotalActivities() const {
    return activities.size();
}

// Get number of pending activities
size_t TodoList::getPendingActivities() const {
    return std::count_if(activities.begin(), activities.end(), [](const Activity& a) {
        return !a.isCompleted();
    });
}

// Finds all activities that match the given name
std::vector<Activity> TodoList::findActivitiesByName(const std::string& name) const {
    std::vector<Activity> result;
    for (const auto& activity : activities) {
        if (activity.getDescription() == name) {
            result.push_back(activity);
        }
    }
    return result;
}

// Finds all activities with the same due date
std::vector<Activity> TodoList::findActivitiesByDueDate(std::time_t dueDate) const {
    std::vector<Activity> result;
    for (const auto& activity : activities) {
        if (activity.getDueDate() == dueDate) {
            result.push_back(activity);
        }
    }
    return result;
}

// Adds an observer to the list (if not already present)
void TodoList::addObserver(Observer* observer) {
    if (std::find(observers.begin(), observers.end(), observer) == observers.end()) {
        observers.push_back(observer);
    }
}

// Removes an observer from the list
void TodoList::removeObserver(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

// Notifies all observers when a change occurs
void TodoList::notifyObservers() const {
    for (Observer* observer : observers) {
        observer->update(); // Calls update() on each observer
    }
}

// Adds a new activity and notifies observers
void TodoList::addActivity(const Activity& activity) {
    activities.push_back(activity);
    notifyObservers(); // Notify observers when a new activity is added
}

void TodoList::removeActivity(const std::string& identifier, bool skipConfirmation) {
    if (identifier.empty()) {
        throw std::invalid_argument("Invalid input: identifier is empty.");
    }

    if (bool isNumber = std::all_of(identifier.begin(), identifier.end(), ::isdigit)) {
        size_t index = std::stoul(identifier);
        if (index == 0 || index > activities.size()) {
            throw std::out_of_range("Activity index is out of range!");
        }
        index--;

        if (!skipConfirmation) {
            std::cout << "Are you sure you want to delete '"
                      << activities[index].getDescription()
                      << "'? (y/n): ";
            char confirm;
            std::cin >> confirm;
            if (confirm != 'y' && confirm != 'Y') {
                std::cout << "Deletion canceled.\n";
                return;
            }
        }

        activities.erase(activities.begin() + index);
        notifyObservers();
        return;
    }

    // Search by name
    std::vector<size_t> matchingIndexes;
    for (size_t i = 0; i < activities.size(); ++i) {
        if (activities[i].getDescription() == identifier) {
            matchingIndexes.push_back(i);
        }
    }

    if (matchingIndexes.empty()) {
        throw std::out_of_range("No activity found with name '" + identifier + "'!");
    }

    size_t indexToRemove = matchingIndexes[0];

    if (matchingIndexes.size() > 1) {
        std::cout << "Multiple activities found with name '" << identifier << "'. Choose which one to remove:\n";
        for (size_t i = 0; i < matchingIndexes.size(); ++i) {
            std::cout << i + 1 << ". " << activities[matchingIndexes[i]].getDescription() << "\n";
        }
        size_t choice;
        std::cout << "Enter the number: ";
        std::cin >> choice;
        if (choice == 0 || choice > matchingIndexes.size()) {
            throw std::invalid_argument("Invalid choice. Operation canceled.");
        }
        indexToRemove = matchingIndexes[choice - 1];
    }

    if (!skipConfirmation) {
        std::cout << "Are you sure you want to delete '" << activities[indexToRemove].getDescription() << "'? (y/n): ";
        char confirm;
        std::cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            std::cout << "Deletion canceled.\n";
            return;
        }
    }

    activities.erase(activities.begin() + indexToRemove);
    notifyObservers();
}

void TodoList::markActivityAsCompleted(const std::string& identifier) {
    if (identifier.empty()) {
        throw std::invalid_argument("Invalid input: identifier is empty.");
    }

    if (bool isNumber = std::all_of(identifier.begin(), identifier.end(), ::isdigit)) {
        size_t index = std::stoul(identifier);
        if (index == 0 || index > activities.size()) {
            throw std::out_of_range("Activity index is out of range!");
        }
        index--;

        activities[index].setCompleted(true);
        notifyObservers();
        return;
    }

    std::vector<size_t> matchingIndexes;
    for (size_t i = 0; i < activities.size(); ++i) {
        if (activities[i].getDescription() == identifier) {
            matchingIndexes.push_back(i);
        }
    }

    if (matchingIndexes.empty()) {
        throw std::out_of_range("No activity found with name '" + identifier + "'!");
    }

    size_t indexToMark = matchingIndexes[0];

    if (matchingIndexes.size() > 1) {
        std::cout << "Multiple activities found with name '" << identifier << "'. Choose which one to mark as completed:\n";
        for (size_t i = 0; i < matchingIndexes.size(); ++i) {
            std::cout << i + 1 << ". " << activities[matchingIndexes[i]].getDescription() << "\n";
        }
        size_t choice;
        std::cout << "Enter the number: ";
        std::cin >> choice;
        if (choice == 0 || choice > matchingIndexes.size()) {
            throw std::invalid_argument("Invalid choice. Operation canceled.");
        }
        indexToMark = matchingIndexes[choice - 1];
    }

    activities[indexToMark].setCompleted(true);
    notifyObservers();
}

// Edits an existing activity (description, completion status, due date)
bool TodoList::editActivity(const std::string& identifier, const std::string& newDescription, bool changeCompletionStatus, bool newCompleted, bool changeDueDate, std::time_t newDueDate) {
    if (identifier.empty()) return false;

    bool isNumber = std::all_of(identifier.begin(), identifier.end(), ::isdigit);
    size_t index = std::string::npos;

    if (isNumber) {
        index = std::stoul(identifier);
        if (index == 0 || index > activities.size()) return false;
        index--;
    } else {
        auto it = std::find_if(activities.begin(), activities.end(),
                               [&](const Activity& a) { return a.getDescription() == identifier; });

        if (it == activities.end()) return false;
        index = std::distance(activities.begin(), it);
    }

    Activity& activity = activities[index];

    if (!newDescription.empty()) {
        activity.setDescription(newDescription);
    }

    if (changeCompletionStatus) {
        activity.setCompleted(newCompleted);
    }

    if (changeDueDate) {
        activity.setDueDate(newDueDate);
    }

    notifyObservers();
    return true;
}

std::string TodoList::toString() const {
    std::ostringstream output;
    output << "--- Todo List: " << name << " ---\n";

    if (activities.empty()) {
        output << "No activities to display.\n";
        return output.str();
    }

    std::vector<Activity> sortedActivities = activities;
    std::sort(sortedActivities.begin(), sortedActivities.end(),
        [](const Activity& a, const Activity& b) {
            return a.getDueDate() < b.getDueDate();
        }
    );

    for (size_t i = 0; i < sortedActivities.size(); ++i) {
        std::time_t dueDate = sortedActivities[i].getDueDate();
        std::string dueDateStr = std::ctime(&dueDate);
        dueDateStr.erase(dueDateStr.find_last_not_of('\n') + 1);

        output << i + 1 << ". " << sortedActivities[i].getDescription()
               << " [" << (sortedActivities[i].isCompleted() ? "Done" : "Not Done") << "]"
               << " (Due: " << dueDateStr << ")\n";
    }
    return output.str();
}

// Saves the activities to a file
void TodoList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) { // File opening check
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& activity : activities) {
        file << activity.serialize() << "\n";
    }
}

// Loads activities from a file and notifies observers
void TodoList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    activities.clear();
    std::string line;
    while (std::getline(file, line)) {
        activities.push_back(Activity::deserialize(line));
    }
    notifyObservers(); // Notify observers after loading new activities
}