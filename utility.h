#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <time.h>   // This is used in the utlitity.c for tm*
#include "structures.h"

/* Functions */

        void display(sharedmem_struct* shms, arc_struct tempavgs);
        const char* cvt_direction(int direction);
        float cvt_rain(int rain);
        arc_struct get_avgs(sharedmem_struct* shms); 
/* Variables */

#endif
