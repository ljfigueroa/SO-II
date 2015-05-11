// porttest.cc
//    Simple test case for the ports assignment.

#include "port.h"
#include "thread.h"
#include "system.h"

static Port port("test port");

static void
PongThread(void* name)
{
    int num;
    const char* threadname = currentThread->getName();

    printf("%s: waiting\n",threadname);
    port.Receive(&num);
    printf("%s: Got a %d\n",threadname,num);

    printf("%s: Sending a 3\n",threadname);
    port.Send(3);
    printf("%s: Sending finished\n",threadname);
}

void
PortTest()
{
    int num;

    Thread* newThread = new Thread ("Pong");
    newThread->Fork(PongThread, NULL);

    currentThread->Yield();

    printf("Ping: Sending a 5\n");
    port.Send(5);
    printf("Ping: Sending finished\n");

    currentThread->Yield();
  
    printf("Ping: waiting\n");
    port.Receive(&num);
    printf("Ping: Got a %d\n", num);
}

