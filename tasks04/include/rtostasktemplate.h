/*
  Copyright (c), 2023
  All rights reserved.
*/
#pragma once

// Includes
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Classes
class RTOSTaskTemplate
{
protected:
    virtual void execute() = 0; // The function that derived classes need to implement

    virtual void setup() = 0; // The function that derived classes need to implement

private:
    TaskHandle_t taskHandle = nullptr;

    boolean waitForNotification = false; // false = loop task, true = task run under notifications

    uint16_t taskDelay;

    // Static function that acts as the task entry point
    static void taskEntryPoint(void *objPtr)
    {
        RTOSTaskTemplate *obj = static_cast<RTOSTaskTemplate *>(objPtr);
        obj->execute(); // Call the overridden run method of derived class
    }

public:
    // Default Constructor
    RTOSTaskTemplate() {}

    void create(const char *taskName, uint16_t stackSize, UBaseType_t priority, UBaseType_t core, boolean notification, uint16_t delay)
    {
        this->waitForNotification = notification;
        this->taskDelay = delay;

        BaseType_t rc;
        rc = xTaskCreatePinnedToCore(
            taskEntryPoint,
            taskName,
            stackSize,
            this,
            priority,
            &taskHandle,
            core);
        assert(rc == pdPASS);
    }

    void deleteTask()
    {
        if (taskHandle)
        {
            vTaskDelete(taskHandle);
            taskHandle = nullptr;
        }
    }

    TaskHandle_t getTaskHandle() const
    {
        return taskHandle;
    }

    boolean getNotification() const
    {
        return waitForNotification;
    }

    uint16_t getTaskDelay() const
    {
        return taskDelay;
    }

    // Ensure the task is deleted when object is destroyed
    virtual ~RTOSTaskTemplate()
    {
        deleteTask();
    }
};
