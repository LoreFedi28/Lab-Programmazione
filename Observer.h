#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual void update() = 0; // This method will be called when TodoList changes
    virtual ~Observer() = default; // Virtual destructor for safety
};

#endif
