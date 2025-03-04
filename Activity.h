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
    // Constructor
    Activity(const std::string& desc, bool comp = false, time_t date = 0);

    // Getters
    std::string getDescription() const;
    bool isCompleted() const;

    // Setters
    void setDescription(const std::string& desc);
    void setCompleted(bool comp);

    void setDueDate(time_t date);
    time_t getDueDate() const;

    // Serialization
    std::string serialize() const;
    static Activity deserialize(const std::string& data);
};

#endif