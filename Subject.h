#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"

class Subject {
public:
    virtual ~Subject() = default; // Virtual destructor for proper cleanup

    // Adds an observer to the list
    virtual void addObserver(Observer* observer) = 0;

    // Removes an observer from the list
    virtual void removeObserver(Observer* observer) = 0;

    // Notifies all registered observers
    virtual void notifyObservers() const = 0;
};

#endif