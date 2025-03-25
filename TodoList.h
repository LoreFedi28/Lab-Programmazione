#ifndef TODOLIST_H
#define TODOLIST_H

#include "Activity.h"
#include "Subject.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

// The TodoList class manages a list of activities and notifies observers of any changes.
class TodoList : public Subject { // Inherit from Subject
private:
    std::string name;
    std::vector<Activity> activities; // Stores the list of activities
    std::vector<Observer*> observers; // Stores a list of registered observers

public:
    // Default constructor (needed for std::map)
    TodoList();
    // Modify constructor to accept a name
    explicit TodoList(std::string  listName);

    // Getter for the TodoList name
    [[nodiscard]] std::string getName() const;
    // Setter to rename the list
    void setName(const std::string& newName);

    // Adds an observer to be notified of changes
    void addObserver(Observer* observer) override;
    // Removes an observer from the notification list
    void removeObserver(Observer* observer) override;
    void notifyObservers() const override;

    // Adds a new activity to the list and notifies observers
    void addActivity(const Activity& activity);
    // Removes an activity by index (if numeric) or by name and notifies observers
    void removeActivity(const std::string& identifier, bool skipConfirmation = false);
    // Marks an activity as completed by index or name and notifies observers
    void markActivityAsCompleted(const std::string& identifier);
    // Edits an activity's details (description, completion status, due date)
    void editActivity(const std::string& identifier);
    // Converts the TodoList activities to a formatted string
    [[nodiscard]] std::string toString() const;

    // Saves the list of activities to a file
    void saveToFile(const std::string& filename) const;
    // Loads activities from a file and notifies observers
    void loadFromFile(const std::string& filename);

    // Returns a reference to the activity list (marked [[nodiscard]] to prevent ignored return values)
    [[nodiscard]] std::vector<Activity> getActivities() const;

    // Returns the total number of activities
    [[nodiscard]] size_t getTotalActivities() const;
    // Returns the number of pending (not completed) activities
    [[nodiscard]] size_t getPendingActivities() const;

    // Finds all activities with a given name
    [[nodiscard]] std::vector<Activity> findActivitiesByName(const std::string& name) const;
    // Finds all activities with a given due date
    [[nodiscard]] std::vector<Activity> findActivitiesByDueDate(std::time_t dueDate) const;
};

#endif