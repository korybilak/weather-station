/*
 *  shm2.c - demo program to show use of Unix shared memory facility
 *	   - DATA "CONSUMER" AGENT
 *  10-Oct-94 :jss
 */

#include <stdio.h>		// for standard system I/O stuff
#include <errno.h>		// for error handling on system calls
#include <sys/types.h>		// for system defined types
#include <sys/ipc.h>		// for IPC permission structure
#include <sys/shm.h>		// for shared memory facility defines

#define SHMKEY 0x77000 + 01
struct sm_struct
{
    int   id;
    float average;
    char name[20];
};


main()
{
    int shm_id, i;		
	struct sm_struct *z;// z will point to shared memory array

//  --------------------------------------------------------------------
//  call system library function to get pre-existing shared memory
//  --------------------------------------------------------------------
    shm_id = shmget( SHMKEY, 0, 0 );

    if ( shm_id == -1 )		// check shmget() return value
    {
	printf( "\nError: shmget() failed, errno = %i\n", errno );
	perror( "shmget()" );
	exit( -1 );
    }
    else
	printf( "\nshmget() successful, shm_id = %i\n", shm_id );

//  --------------------------------------------------------------------
//  attach variable z to shared memory segment
//  --------------------------------------------------------------------
    z = (struct sm_struct *) shmat( shm_id, 0, SHM_RDONLY );
    if ( (int) z == -1 )
    {
	printf( "Error: shmat() failed, errno = %i\n", errno );
	perror( "shmat()" );
	exit( -1 );
    }

//  access data from shared memory region
    printf( "Ready to get the element of the struct from shared memory:\n" );
	printf("id=%i ", z->id);
	printf("average=%f ", z->average);
	printf("name=%s ", z->name);	
    putchar( '\n' );

//  --------------------------------------------------------------------
//  done with shared memory, detach from it
//  --------------------------------------------------------------------
    shmdt( (void *) z );

    return( 0 );
}
