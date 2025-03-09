#ifndef TODOLIST_H
#define TODOLIST_H

#include "Activity.h"
#include "Observer.h"
#include <vector>
#include <string>

// The TodoList class manages a list of activities and notifies observers of any changes.
class TodoList {
private:
    std::vector<Activity> activities; // Stores the list of activities
    std::vector<Observer*> observers; // Stores a list of registered observers

    void notifyObservers(); // Notifies all registered observers when a change occurs

public:
    // Adds an observer to be notified of changes
    void addObserver(Observer* observer);
    // Removes an observer from the notification list
    void removeObserver(Observer* observer);

    // Adds a new activity to the list and notifies observers
    void addActivity(const Activity& activity);

    // Removes an activity by index and notifies observers
    void removeActivity(size_t index, bool skipConfirmation = false);

    // Marks an activity as completed and notifies observers
    void markActivityAsCompleted(size_t index);

    // Displays all activities sorted by due date
    void displayActivities() const;

    // Saves the list of activities to a file
    void saveToFile(const std::string& filename) const;

    // Loads activities from a file and notifies observers
    void loadFromFile(const std::string& filename);

    // Returns a reference to the activity list (marked [[nodiscard]] to prevent ignored return values)
    [[nodiscard]] std::vector<Activity> getActivities() const { return activities; }
};

#endif