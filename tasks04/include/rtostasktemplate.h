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

    String taskName;

    // Static function that acts as the task entry point
    static void taskEntryPoint(void *objPtr)
    {
        RTOSTaskTemplate *obj = static_cast<RTOSTaskTemplate *>(objPtr);
        obj->execute(); // Call the overridden run method of derived class
    }

public:
    // Default Constructor
    RTOSTaskTemplate() {}

    void create(const char *_taskName, uint16_t _stackSize,
                UBaseType_t _priority, UBaseType_t _core,
                boolean _waitForNotification, uint16_t _taskDelay)
    {
        this->waitForNotification = _waitForNotification;
        this->taskDelay = _taskDelay;
        this->taskName = String(_taskName);

        BaseType_t rc;
        rc = xTaskCreatePinnedToCore(
            taskEntryPoint,
            _taskName,
            _stackSize,
            this,
            _priority,
            &taskHandle,
            _core);
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

    String getTaskName() const
    {
        return taskName;
    }

    // Ensure the task is deleted when object is destroyed
    virtual ~RTOSTaskTemplate()
    {
        deleteTask();
    }
};
