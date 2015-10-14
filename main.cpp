#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include <Windows.h>

#include "FiberQueue.h"

typedef struct SFIBER_DATA
{
    CFiberQueue *FiberQueue;
    LPVOID FiberData;
} SFIBER_DATA;

VOID __stdcall fiber_test1(LPVOID lpParameter)
{
    printf("Fiber Test 1\n");

    SFIBER_DATA *l_FiberData = (SFIBER_DATA *) lpParameter;
    l_FiberData->FiberQueue->Next();
}

VOID __stdcall fiber_test2(LPVOID lpParameter)
{
    printf("Fiber Test 2\n");

    SFIBER_DATA *l_FiberData = (SFIBER_DATA *) lpParameter;
    l_FiberData->FiberQueue->Next();
}

int main(int argc, char *argv[])
{
    CFiberQueueElement m1;
    CFiberQueue q1;

    SFIBER_DATA FiberData = { &q1, NULL };

    CFiberQueueElement t1(fiber_test1, 0, &FiberData);
    CFiberQueueElement t2(fiber_test2, 0, &FiberData);

    q1.Push(&t1);
    q1.Push(&t2);

    m1.ConvertThreadToFiber();
    q1.SetMainFiber(&m1);
    q1.Next();

    printf("Hola Mundo\n"); getchar();
    return EXIT_SUCCESS;
}