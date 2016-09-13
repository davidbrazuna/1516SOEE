// TestJoin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Include/UThread.h"

VOID Thread1(UT_ARGUMENT arg) {
	printf("Thread %p start!\n", UtSelf());

	
	for (int i = 0; i < 1000; ++i) {
		putchar('T');
		UtYield();
	}
		

	printf("Thread %p end!\n", UtSelf());

}

VOID Thread2(UT_ARGUMENT arg) {
	HANDLE t = (HANDLE)arg;
	printf("Thread %p wait for thread %p termination\n",
		UtSelf(), t);
	UtJoin(t);
	printf("Thread %p resume!\n", UtSelf());
}


VOID UtJoinTest() {
	HANDLE t1Handle = UtCreate(Thread1, NULL);
	UtCreate(Thread2, t1Handle);
	UtCreate(Thread2, t1Handle);

	UtRun();
}


int _tmain(int argc, _TCHAR* argv[])
{
	UtInit();

	UtJoinTest();

	UtEnd();
	return 0;
}

