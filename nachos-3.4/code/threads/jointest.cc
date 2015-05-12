// jointest.cc
//	Simple test case for the join functionality

#include <unistd.h>

#include "system.h"

static void
Snorlax(void *name)
{
	sleep(1);
	printf("ZzZzZ...\n");
	sleep(1);
	printf("ZzZzZ...\n");
	sleep(1);
	printf("ZzZzZ...\n");
	sleep(1);
	printf("Yawn \\o/\n");
}

void
JoinTest()
{
	DEBUG('t', "Entering JoinTest");

	Thread* newThread = new Thread ("Snorlax", 1);
	newThread->Fork (Snorlax, NULL);
	printf("Join: calling Snorlax\n");
	newThread->Join();
	printf("Join: he disappeared!\n");
}
