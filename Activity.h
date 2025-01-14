#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>

class Activity {
private:
    std::string description;
    bool completed;

public:
    // Constructor
    Activity(const std::string& desc, bool comp = false);

    // Getters
    std::string getDescription() const;
    bool isCompleted() const;

    // Setters
    void setDescription(const std::string& desc);
    void setCompleted(bool comp);

    // Serialization
    std::string serialize() const;
    static Activity deserialize(const std::string& data);
};

#endif