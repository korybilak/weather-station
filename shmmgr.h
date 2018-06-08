#ifndef SHMMGR_H
#define SHMMGR_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include "structures.h"

/* Functions */
int attach(int shmkey);
void* getmemstruct();
int detach();

/* Variables */
extern               int shm_id;
extern sharedmem_struct* shmemstruct; 

#endif
