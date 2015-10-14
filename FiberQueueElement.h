#pragma once
#include "./Fiber.h"

class CFiberQueueElement : public CFiber
{
    public:
        CFiberQueueElement(LPFIBER_START_ROUTINE l_pFiberFunction, unsigned int l_StackSize = 0, LPVOID l_pData = 0) : CFiber(l_pFiberFunction, l_StackSize, l_pData), m_NextElement(NULL)
        {
        }

        CFiberQueueElement(void) : CFiber()
        {
        }

        ~CFiberQueueElement(void)
        {
        }

        CFiberQueueElement *m_NextElement;
};