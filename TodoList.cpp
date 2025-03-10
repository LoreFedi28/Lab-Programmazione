#include "TodoList.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>

// Adds an observer to the list
void TodoList::addObserver(Observer* observer) {
    observers.push_back(observer);
}

// Removes an observer from the list
void TodoList::removeObserver(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

// Notifies all observers when a change occurs
void TodoList::notifyObservers() {
    for (Observer* observer : observers) {
        observer->update(); // Calls update() on each observer
    }
}

// Adds a new activity and notifies observers
void TodoList::addActivity(const Activity& activity) {
    activities.push_back(activity);
    notifyObservers(); // Notify observers when a new activity is added
}

// Removes an activity and notifies observers
void TodoList::removeActivity(size_t index, bool skipConfirmation) {
    if (index < activities.size()) {
        if (!skipConfirmation) { // If not skipping confirmation, ask the user
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
        notifyObservers(); // Notify observers after removal
    } else {
        std::cerr << "Invalid index!\n";
    }
}

// Marks an activity as completed and notifies observers
void TodoList::markActivityAsCompleted(size_t index) {
    if (index < activities.size()) {
        activities[index].setCompleted(true);
        notifyObservers(); // Notify observers when an activity is marked as completed
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

        // Convert time to string and remove the newline at the end
        std::string dueDateStr = std::ctime(&dueDate);
        dueDateStr.erase(dueDateStr.find_last_not_of('\n') + 1);  // Remove trailing newline

        std::cout << i + 1 << ". " << sortedActivities[i].getDescription()
                  << " [" << (sortedActivities[i].isCompleted() ? "Done" : "Not Done") << "]"
                  << " (Due: " << dueDateStr << ")\n"; // Corrected: no unwanted line break
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