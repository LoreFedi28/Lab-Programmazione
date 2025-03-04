#include "TodoList.h"
#include <iostream>
#include <fstream>

void TodoList::addActivity(const Activity& activity) {
    activities.push_back(activity);
}

void TodoList::removeActivity(size_t index) {
    if (index < activities.size()) {
        activities.erase(activities.begin() + index);
    }
}

void TodoList::displayActivities() const {
    for (size_t i = 0; i < activities.size(); ++i) {
        std::cout << i + 1 << ". " << activities[i].getDescription()
                  << " [" << (activities[i].isCompleted() ? "Done" : "Not Done") << "]\n";
    }
}

void TodoList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) { // Controllo apertura file
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& activity : activities) {
        file << activity.serialize() << "\n";
    }
}

void TodoList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) { // Controllo apertura file
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    activities.clear();
    std::string line;
    while (std::getline(file, line)) {
        activities.push_back(Activity::deserialize(line));
    }
}