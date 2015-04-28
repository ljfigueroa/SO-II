// locktest.cc
//	Simple test case for the lock assignment.

#include "system.h"
#include "synch.h"

static unsigned int count;
static Lock lock("counter lock");

void
SimpleCounter(void* name)
{
	for (int i = 0; i < 10000; ++i) {
		lock.Acquire();
		++count;
		lock.Release();
	}

	lock.Acquire();
	printf("Counter thread finished after %d loops\n", count);
	lock.Release();

}

#define THREAD_NUM 5

void
LockTest()
{
	DEBUG('t', "Entering LockTest");

	for (int i = 1; i < THREAD_NUM; ++i)
	{
		Thread* newThread = new Thread ("Counter");
		newThread->Fork (SimpleCounter, NULL);
	}

	SimpleCounter((void*)"Counter");
}
