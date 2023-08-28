#pragma once

// Includes
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "systemtasks.h"
#include "rtostasktemplate.h"

// Defines
#define VERBOSE_OFF 0
#define VERBOSE_ON 1

#define VERBOSE_MAX_MESSAGE_LENGTH 50
#define VERBOSE_FIFO_SIZE 30

#define VERBOSE_SYSTEM VERBOSE_ON

#define VERBOSE_MODULE_APP VERBOSE_ON
#define VERBOSE_MODULE_LED VERBOSE_ON
#define VERBOSE_MODULE_BUTTON VERBOSE_ON
#define VERBOSE_MODULE_SYSCLOCK VERBOSE_ON

#define VERBOSE_TASK_APP VERBOSE_ON
#define VERBOSE_TASK_LED VERBOSE_ON
#define VERBOSE_TASK_BUTTON VERBOSE_ON

#define VERBOSE(M, S) verbose.insert(M, S)

// Data Types - typedefs, structs, unions and/or enumerated
typedef struct
{
    boolean enabled;
    uint8_t maxLength;
} Verbose_t;

typedef struct
{
    String message;
} VerboseItem_t;

// Classes
class VerboseTask : public RTOSTaskTemplate<Verbose_t>
{
public:
    void setup(Verbose_t &pParameters) override
    {
        mEnabled = pParameters.enabled;
        mMaxLength = pParameters.maxLength;
    }

    void enabled(uint8_t pStatus)
    {
        mEnabled = pStatus;
    }

    void insert(String pMessage, uint8_t pSession)
    {
        VerboseItem_t _item;
        if (pSession && VERBOSE_SYSTEM && mEnabled)
        {
            _item.message = pMessage;
            enqueue(_item);
        }
    }

private:
    uint8_t mEnabled;
    uint8_t mMaxLength;
    uint8_t mHead = 0;
    uint8_t mTail = 0;
    boolean mBusy = false;
    VerboseItem_t mVerboseFifo[VERBOSE_FIFO_SIZE];

    void enqueue(VerboseItem_t pFifoItem)
    {
        if (!mBusy)
        {
            mBusy = true;
            if (pFifoItem.message.length() > mMaxLength)
            {
                pFifoItem.message = pFifoItem.message.substring(0, mMaxLength); // Truncate the message
            }

            mVerboseFifo[mHead] = pFifoItem;

            // Set new head
            if (mHead < (VERBOSE_FIFO_SIZE - 1))
            {
                mHead++;
            }
            else
            {
                mHead = 0;
            }

            // Check Buffer Overlaping
            if (mHead == mTail)
            {
                if (mTail < (VERBOSE_FIFO_SIZE - 1))
                {
                    mTail++;
                }
                else
                {
                    mTail = 0;
                }
            }

            mBusy = false;
        }
    }

protected:
    void execute() override
    {
        if (!isEmpty() && mEnabled && !mBusy)
        {
            mBusy = true;
            Serial.println(mVerboseFifo[mTail].message);

            // Uptade Tail
            if (mTail < (VERBOSE_FIFO_SIZE - 1))
            {
                mTail++;
            }
            else
            {
                mTail = 0;
            }
            mBusy = false;
        }
    }

    boolean isEmpty()
    {
        return (mHead == mTail);
    }
};

// Public Functions
void verboseSetup(void);
void verboseInit(void);
