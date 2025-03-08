#include "TodoList.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>

// Adds a new activity to the list
void TodoList::addActivity(const Activity& activity) {
    activities.push_back(activity);
}

// Removes an activity by index, with an optional confirmation
void TodoList::removeActivity(size_t index, bool skipConfirmation) {
    if (index < activities.size()) {
        if (!skipConfirmation) {  // If we are in a test, we skip the confirmation
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
        std::cout << "Activity deleted.\n";
    } else {
        std::cerr << "Invalid index!\n";
    }
}

// Marks an activity as completed
void TodoList::markActivityAsCompleted(size_t index) {
    if (index < activities.size()) {
        activities[index].setCompleted(true);
    } else {
        std::cerr << "Invalid index!\n";
    }
}

// Displays all activities, sorted by due date
void TodoList::displayActivities() const {
    std::vector<Activity> sortedActivities = activities;
    std::sort(sortedActivities.begin(), sortedActivities.end(),
        [](const Activity& a, const Activity& b) {
            return a.getDueDate() < b.getDueDate();
        }
    );

    for (size_t i = 0; i < sortedActivities.size(); ++i) {
        std::time_t dueDate = sortedActivities[i].getDueDate();
        std::cout << i + 1 << ". " << sortedActivities[i].getDescription()
                  << " [" << (sortedActivities[i].isCompleted() ? "Done" : "Not Done") << "]"
                  << " (Due: " << std::ctime(&dueDate) << ")\n";
    }
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

// Loads activities from a file
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
}