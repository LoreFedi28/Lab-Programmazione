#ifndef TODOLIST_H
#define TODOLIST_H

#include "Activity.h"
#include <vector>
#include <string>

class TodoList {
private:
    std::vector<Activity> activities;

public:
    // Methods to manage activities
    void addActivity(const Activity& activity);
    void removeActivity(size_t index);
    void markActivityAsCompleted(size_t index);
    void displayActivities() const;

    // File operations
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    const std::vector<Activity>& getActivities() const { return activities; }
};

#endif