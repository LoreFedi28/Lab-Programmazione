#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
#include <ctime>

class Activity {
private:
    std::string description;
    bool completed;
    time_t dueDate;

public:
    // Constructor with default parameters
    explicit Activity(const std::string& desc, bool comp = false, time_t date = 0);

    // Getters for retrieving activity details
    [[nodiscard]] std::string getDescription() const;
    [[nodiscard]] bool isCompleted() const;

    // Setters for modifying activity details
    void setDescription(const std::string& desc);
    void setCompleted(bool comp);
    void setDueDate(time_t date);
    [[nodiscard]] time_t getDueDate() const;

    // Methods for saving and loading activities as strings
    [[nodiscard]] std::string serialize() const;
    static Activity deserialize(const std::string& data);
};

#endif