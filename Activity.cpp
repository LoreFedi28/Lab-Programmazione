#include "Activity.h"
#include <sstream>

Activity::Activity(const std::string& desc, bool comp) : description(desc), completed(comp) {}

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

std::string Activity::serialize() const {
    return description + ";" + (completed ? "1" : "0");
}

Activity Activity::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string desc;
    std::getline(iss, desc, ';');
    std::string comp;
    std::getline(iss, comp);
    return Activity(desc, comp == "1");
}