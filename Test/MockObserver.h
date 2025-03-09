#ifndef MOCK_OBSERVER_H
#define MOCK_OBSERVER_H

#include "../Observer.h"

class MockObserver : public Observer {
public:
    bool updated = false; // Flag to check if update() was called

    void update() override {
        updated = true; // Mark that update() was triggered
    }
};

#endif
