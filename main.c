#include <stdio.h>
#include <errno.h>	            /* for error handling on system calls */
#include "shmmgr.h"
#include "utility.h"

int main()
{
	int SHMKEY = 0x00087001 + 1;

	if(attach(SHMKEY) == -1)
	{
		printf("Error attaching to shared memory; Exiting...\n");
		return 1;
	}

	if(getmemstruct() == (void*) -1)
	{
		printf("Error getting shared memory structure; Exiting...\n");
		return 1;
	}

	display(shmemstruct, get_avgs(shmemstruct));

	if(detach() == -1)
	{
		printf("Error detaching from shared memory (how?); Exiting...\n");
		return 1;
	}

    	return 0;
}


