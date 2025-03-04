#include "Activity.h"
#include <sstream>
#include <ctime>

Activity::Activity(const std::string& desc, bool comp, time_t date) : description(desc), completed(comp), dueDate(date) {}

std::string Activity::getDescription() const {
    return description;
}

bool Activity::isCompleted() const {
    return completed;
}

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

std::string Activity::serialize() const {
    return description + ";" + (completed ? "1" : "0") + ";" + std::to_string(dueDate);
}

Activity Activity::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string desc, comp, dateStr;
    std::getline(iss, desc, ';');
    std::getline(iss, comp, ';');
    std::getline(iss, dateStr);
    return Activity(desc, comp == "1", std::stoll(dateStr));
}