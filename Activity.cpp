#include "Activity.h"
#include <algorithm>
#include <sstream>
#include <ctime>
#include <utility>

// Constructor that initializes activity attributes
Activity::Activity(std::string  desc, bool comp, time_t date) : description(std::move(desc)), completed(comp), dueDate(date) {}

// Getters: Retrieve the values of private attributes
std::string Activity::getDescription() const {
    return description;
}

bool Activity::isCompleted() const {
    return completed;
}

// Setters: Modify private attributes
void Activity::setDescription(const std::string& desc) {
    description = desc;
}

void Activity::setCompleted(bool comp) {
    completed = comp;
}

void Activity::setDueDate(time_t date) {
    dueDate = date;
}

time_t Activity::getDueDate() const {
    return dueDate;
}

// Serializes the activity into a string format: "description;1;1678902345"
std::string Activity::serialize() const {
    return description + ";" + (completed ? "1" : "0") + ";" + std::to_string(dueDate);
}

// Deserializes a string back into an Activity object
Activity Activity::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string desc, comp, dateStr;

    if (!(std::getline(iss, desc, ';') &&
          std::getline(iss, comp, ';') &&
          std::getline(iss, dateStr))) {
        throw std::invalid_argument("Error: Malformed serialized string");
          }

    bool completed = (comp == "1");

    if (dateStr.empty() || !std::all_of(dateStr.begin(), dateStr.end(), ::isdigit)) {
        throw std::invalid_argument("Error: Invalid due date in serialized string");
    }

    std::time_t dueDate = std::stoll(dateStr);
    return Activity(desc, completed, dueDate);
}