#pragma once

#include <list>

class Observer
{
public:
    virtual void update(uint8_t pParameter) = 0;
};

class Subject
{
private:
    std::list<Observer *> observers;

public:
    void attach(Observer *pObserver)
    {
        observers.push_back(pObserver);
    }

    void detach(Observer *pObserver)
    {
        observers.remove(pObserver);
    }

    void notify(uint8_t pParameter)
    {
        for (Observer *observer : observers)
        {
            observer->update(pParameter);
        }
    }
};
