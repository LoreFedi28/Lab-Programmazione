#ifndef TODOLIST_H
#define TODOLIST_H

#include "Activity.h"
#include <vector>
#include <string>

class TodoList {
private:
    std::vector<Activity> activities; // Stores all the activities in the to-do list

public:
    // Adds a new activity to the list
    void addActivity(const Activity& activity);

    // Removes an activity by index, with an optional confirmation
    void removeActivity(size_t index, bool skipConfirmation = false);

    // Marks an activity as completed based on its index
    void markActivityAsCompleted(size_t index);

    // Displays all activities, sorted by due date
    void displayActivities() const;

    // Saves the list of activities to a file
    void saveToFile(const std::string& filename) const;

    // Loads activities from a file
    void loadFromFile(const std::string& filename);

    // Returns a reference to the vector of activities
    const std::vector<Activity>& getActivities() const { return activities; }
};

#endif