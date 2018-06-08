#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <sys/types.h>

typedef struct arc_struct {
		 u_char start_block;
     	 float inside_temp;
     	 float outside_temp;
     	   int wind_speed;
     	   int wind_dir;
     	   int barometer;
     	 float inside_humidity;
     	 float outside_humidity;
     	 float total_rain;
     	 float dewpoint;
     	 float wind_chill;
    	time_t reading_time;
 } arc_struct;

typedef struct daily {
    	float inside_temp;
    	float outside_temp;
    	  int wind_speed;
    	  int barometer;
    	float inside_humidity;
    	float outside_humidity;
    	float total_rain;
        float dewpoint;
  	float wind_chill;
} daily;

typedef struct hourly_avg {
		float inside_temp;
		float outside_temp;
		float wind_speed;
		float barometer;
		float inside_humidity;
		float outside_humidity;
		float total_rain;
		float dewpoint;
		float wind_chill;
} hourly_avg;

typedef struct sharedmem_struct {
		     short lastUsedIndex;
		arc_struct archive[1440];       // archive structure type array
		hourly_avg hourly_average;      // hourly collected data for weather station
		     daily daily_high;
		     daily daily_low;
} sharedmem_struct;

#endif
