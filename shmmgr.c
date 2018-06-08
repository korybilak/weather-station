// --------
// shmmgr.h
// --------
//

#include "shmmgr.h"

/* Variables */

              int shm_id;
sharedmem_struct* shmemstruct;

/* Functions */

// attach(int shmkey)
//	Used in:
//	Purpose:
//	 Return:
int attach(int shmkey) {
	shm_id = shmget(shmkey, sizeof(shmemstruct), 0);
	return shm_id;
}

// detach()
//	Used in:
//	Purpose:
//	 Return:
int detach() {
	return shmdt((void*) shmemstruct);
}

// getmemstruct()
// 	Used in:
//	Purpose:
//	 Return:
void* getmemstruct() {
	shmemstruct = (sharedmem_struct*)shmat(shm_id, 0, SHM_RDONLY);
	return (void*) shmemstruct;
}

