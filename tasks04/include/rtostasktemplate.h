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
template <typename T>
class RTOSTaskTemplate
{
public:
    RTOSTaskTemplate() {}

    void create(const char *pTaskName, uint16_t pStackSize,
                UBaseType_t pPriority, UBaseType_t pCore,
                boolean pWaitForNotification, uint16_t pTaskDelay)
    {
        mTaskName = String(pTaskName);
        mWaitForNotification = pWaitForNotification;
        mTaskDelay = pTaskDelay;

        BaseType_t rc;
        rc = xTaskCreatePinnedToCore(
            taskRunner,
            pTaskName,
            pStackSize,
            this,
            pPriority,
            &mTaskHandle,
            pCore);
        assert(rc == pdPASS);
    }

    void notify()
    {
        xTaskNotifyGive(mTaskHandle);
    }

    void deleteTask()
    {
        if (mTaskHandle)
        {
            vTaskDelete(mTaskHandle);
            mTaskHandle = nullptr;
        }
    }

    TaskHandle_t getTaskHandle() const
    {
        return mTaskHandle;
    }

    boolean getNotification() const
    {
        return mWaitForNotification;
    }

    uint16_t getTaskDelay() const
    {
        return mTaskDelay;
    }

    String getTaskName() const
    {
        return mTaskName;
    }

    // Ensure the task is deleted when object is destroyed
    virtual ~RTOSTaskTemplate()
    {
        deleteTask();
    }

    virtual void setup(T &pParameters){}; // The function that derived classes dont need to implement

    virtual void init(){}; // The function that derived classes dont need to implement

private:
    TaskHandle_t mTaskHandle = nullptr;

    boolean mWaitForNotification = false; // false = loop task, true = task run under notifications

    uint16_t mTaskDelay;

    String mTaskName;

    // Static function that acts as the task entry point
    static void taskRunner(void *pvParameters)
    {
        RTOSTaskTemplate *instance = static_cast<RTOSTaskTemplate *>(pvParameters);
        for (;;)
        {
            if (instance->mWaitForNotification)
            {
                ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait indefinitely for a notification
            }
            instance->execute(); // Call the overridden run method of derived class
            if (!instance->mWaitForNotification)
            {
                vTaskDelay(instance->mTaskDelay / portTICK_PERIOD_MS);
            }
        }
    }

protected:
    virtual void execute() = 0; // The function that derived classes need to implement
};
