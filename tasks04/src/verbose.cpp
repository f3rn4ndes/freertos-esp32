// Includes
#include "verbose.h"

// Objects
VerboseTask verbose;

// Functions

void verboseSetup(void)
{
    Verbose_t _verboseFifo;

    _verboseFifo.enabled = true;
    _verboseFifo.maxLength = VERBOSE_MAX_MESSAGE_LENGTH;

    verbose.setup(_verboseFifo);
}

void verboseInit(void)
{
    verbose.createTask(
        "VERBOSE",
        VERBOSE_TASK_STACK_SIZE,
        VERBOSE_TASK_PRIORITY,
        VERBOSE_TASK_CORE,
        SYSTEM_TASK_LOOP,
        VERBOSE_TASK_DELAY_MS);
}

void verboseEnable(uint8_t pStatus)
{
    verbose.enabled(pStatus);
}

void verboseInsert(String pMessage, uint8_t pSession)
{
    VerboseItem_t _item;
    if (pSession)
    {
        _item.message = pMessage;
        verbose.push(_item);
    }
}
