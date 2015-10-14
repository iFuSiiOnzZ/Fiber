#pragma once
#include <Windows.h>

class CFiber
{
    protected:
        LPVOID m_pFiber;

    public:
        CFiber(LPFIBER_START_ROUTINE l_pFiberFunction, unsigned int l_StackSize = 0, LPVOID l_pData = 0)
        {
            m_pFiber = ::CreateFiber(l_StackSize, l_pFiberFunction, l_pData);
        }

        CFiber(void)
        {
            m_pFiber = NULL;
        }

        virtual ~CFiber()
        {
            ::DeleteFiber(m_pFiber);
        }

        bool Create(PFIBER_START_ROUTINE l_pFiberFunction, unsigned int l_StackSize = 0)
        {
            if(m_pFiber != NULL)
            {
                return false;
            }

            m_pFiber = ::CreateFiber(l_StackSize, l_pFiberFunction, this);
            return m_pFiber != NULL;
        }

        bool ConvertThreadToFiber(void)
        {
            if(m_pFiber != NULL)
            {
                return false;
            }

            m_pFiber = ::ConvertThreadToFiber(this);
            return m_pFiber != NULL;
        }

        void Execute(void)
        {
            ::SwitchToFiber(m_pFiber);
        }
};