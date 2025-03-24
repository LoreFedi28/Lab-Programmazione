#include "TodoList.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <iomanip>

// Default constructor
TodoList::TodoList() : name("UnnamedList") {}

// Constructor with name
TodoList::TodoList(const std::string& listName) : name(listName) {}

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

// Removes an activity by index (if numeric) or by name and notifies observers
void TodoList::removeActivity(const std::string& identifier, bool skipConfirmation) {
    size_t index = activities.size(); // Initialize with an out-of-range value

    // Check if the input is a number (index) or a string (activity name)
    try {
        index = std::stoul(identifier); // Try converting to a number
        if (index >= activities.size()) {
            throw std::out_of_range("Error: Activity index is out of range!");
        }
    } catch (const std::invalid_argument&) {
        // If conversion fails, search for an activity by name
        auto it = std::find_if(activities.begin(), activities.end(), [&](const Activity& a) {
            return a.getDescription() == identifier;
        });

        if (it == activities.end()) {
            std::cerr << "Error: Activity not found!\n";
            return;
        }

        index = std::distance(activities.begin(), it);
    }

    // Ask for confirmation before removing
    if (!skipConfirmation) {
        std::cout << "Are you sure you want to delete '" << activities[index].getDescription() << "'? (y/n): ";
        char confirm;
        std::cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            std::cout << "Deletion canceled.\n";
            return;
        }
    }

    // Remove the activity
    activities.erase(activities.begin() + index);
    notifyObservers(); // Notify observers about the change
}


// Marks an activity as completed and notifies observers
void TodoList::markActivityAsCompleted(size_t index) {
    if (index >= activities.size()) {
        std::cerr << "Error: Invalid index!\n";
        return;
    }

    activities[index].setCompleted(true);
    notifyObservers(); // Notify observers when an activity is marked as completed
}

// Edits an existing activity (description, completion status, due date)
void TodoList::editActivity(size_t index) {
    if (index >= activities.size()) {
        std::cerr << "Error: Invalid index!\n";
        return;
    }

    Activity& activity = activities[index];

    std::cout << "Editing Activity: " << activity.getDescription() << std::endl;

    // Modify description
    std::cout << "Enter new description (or press ENTER to keep current): ";
    std::string newDescription;
    std::getline(std::cin >> std::ws, newDescription);
    if (!newDescription.empty()) {
        activity.setDescription(newDescription);
    }

    // Modify completion status
    std::cout << "Is the activity completed? (y/n, press ENTER to keep current): ";
    std::string completedInput;
    std::getline(std::cin >> std::ws, completedInput);
    if (!completedInput.empty()) {
        if (completedInput == "y" || completedInput == "Y") {
            activity.setCompleted(true);
        } else if (completedInput == "n" || completedInput == "N") {
            activity.setCompleted(false);
        }
    }

    // Modify due date
    std::cout << "Enter new due date (YYYY-MM-DD HH:MM, press ENTER to keep current): ";
    std::string dueDateStr;
    std::getline(std::cin >> std::ws, dueDateStr);
    if (!dueDateStr.empty()) {
        std::tm tm = {};
        std::istringstream ss(dueDateStr);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
        std::time_t dueDate = std::mktime(&tm);
        activity.setDueDate(dueDate);
    }

    notifyObservers(); // Notify observers about the change
    std::cout << "Activity updated successfully!\n";
}

// Displays all activities, sorted by due date
void TodoList::displayActivities() const {
    std::cout << "\n--- Todo List: " << name << " ---\n";

    if (activities.empty()) {
        std::cout << "No activities to display.\n";
        return;
    }

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