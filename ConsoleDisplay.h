#ifndef CONSOLEDISPLAY_H
#define CONSOLEDISPLAY_H

#include "Observer.h"
#include "TodoList.h"
#include <iostream>

class ConsoleDisplay : public Observer {
private:
    TodoList& todoList; // Reference to TodoList

public:
    explicit ConsoleDisplay(TodoList& list) : todoList(list) {
        todoList.addObserver(this); // Register this class as an observer
    }

    ~ConsoleDisplay() override {
        todoList.removeObserver(this); // Unregister observer when destroyed
    }

    void update() override {
        std::cout << "\nTodo List Updated:\n";
        todoList.displayActivities();
    }
};

#endif
