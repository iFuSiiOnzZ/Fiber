#pragma once
#include "./FiberQueueElement.h"

class CFiberQueue
{
    private:
        CFiberQueueElement *m_Head, *m_Tail;
        CFiberQueueElement *m_MainFiber;

    public:
        CFiberQueue(void) : m_Head(NULL), m_Tail(NULL), m_MainFiber(NULL)
        {
        }

        virtual ~CFiberQueue(void)
        {
            m_Head = NULL;
            m_Tail = NULL;
        }

        void SetMainFiber(CFiberQueueElement *l_pFiber)
        {
            m_MainFiber = l_pFiber;
        }

        void Push(CFiberQueueElement *l_pFiber)
        {
            if(m_Head == NULL)
            {
                m_Head = m_Tail = l_pFiber;
                m_Tail->m_NextElement = NULL;
            }
            else
            {
                m_Tail->m_NextElement = l_pFiber;
                m_Tail = l_pFiber;
            }
        }

        CFiberQueueElement *Pop(void)
        {
            if(m_Head == NULL)
            {
                return NULL;
            }

            CFiberQueueElement *l_Head = m_Head;
            m_Head = m_Head->m_NextElement;

            l_Head->m_NextElement = NULL;
            return l_Head;
        }

        void Next(void)
        {
            CFiberQueueElement *l_ToExecute = Pop();

            if(l_ToExecute != NULL) l_ToExecute->Execute();
            else m_MainFiber->Execute();
        }
};
