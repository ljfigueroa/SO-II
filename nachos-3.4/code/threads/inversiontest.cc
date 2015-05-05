// inversiontest.cc
//	Simple test case for priority inversion.

#include "system.h"
#include "synch.h"
#include "unistd.h"

static Lock lock("lock");

static void
HighPriority(void *)
{
	printf("High priority: running\n");
	printf("High priority: getting lock\n");
	lock.Acquire();
	printf("High priority: got lock\n");
	lock.Release();
	printf("High priority: released lock\n");
}

static void
MediumPriority(void *)
{
	int i = 5;
	printf("Medium priority: running\n");

	char *threadname = new char[128];
	strcpy(threadname, "High");
	Thread* newThread = new Thread(threadname);
	newThread->setPriority(2);
	newThread->Fork(HighPriority, NULL);

	/* Let it run */
	currentThread->Yield();

	while(--i) {
		sleep(1);
		printf("Medium priority: running\n");
	}
}

void
InversionTest()
{
	int i = 5;

	printf("Low priority: running\n");

	char *threadname = new char[128];
	strcpy(threadname, "Medium");

	lock.Acquire();
	printf("Low priority: got lock\n");

	Thread* newThread = new Thread(threadname);
	newThread->setPriority(1);
	newThread->Fork(MediumPriority, (void*)threadname);

	/* Let it run */
	currentThread->Yield();

	/* Medium and high priority will run after the yield; if we don't
	 * have a solution for priority inversion we will never get here */

	lock.Release();

	while(--i) {
		sleep(1);
		printf("Low priority: running\n");
		/* Yield so other higher priority threads get a chance to run */
		currentThread->Yield();
	}
}
