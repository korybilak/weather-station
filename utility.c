#include "utility.h"
// This function displays all of the data we receive.
void display(sharedmem_struct* shms, arc_struct tempavgs)
{
    
	struct tm *timeinfo;            //Time structure pointer, included in .h
	int loc = shms->lastUsedIndex;    //get the last used index
	char buffer[80];
    /*convert times from tm struct*/
    /*extract the reading_time from shared memory structure*/
	timeinfo = localtime (&shms->archive[loc].reading_time);
	strftime(buffer,80, "%A - %B %d, %Y", timeinfo); // sets up the date display
	int hr = timeinfo->tm_hour;
	int mn = timeinfo->tm_min;
	int sc = timeinfo->tm_sec;
	
    /*pointer to shared memory structure, index returned from search func*/
	arc_struct cur = shms->archive[loc - 1];
	
	printf("==================================\n");										 
	printf("Welcome to the CALU weather center\n");
	printf("==================================\n\n");
	printf("\tWeather conditions as of %s at %02d:%02d:%02d\n", buffer, hr, mn, sc); // displays date and time
	printf("\t\tTemperature      	%4.2f F", cur.outside_temp);
	printf(" (%4.2f C)\n", (cur.outside_temp-32)*5/9); //converts the data into celsius
	printf("\t\t Wind Speed		%4.2f Mph (%4.2f Knots)\n",(float)cur.wind_speed,(float)cur.wind_speed*.87);
	printf("\t\t Wind Chill		%4.2f F (%4.2f C)\n", cur.wind_chill, (cur.wind_chill-32)*5/9);
	printf("\t\t  Barometer		%4.2f inHg\n", (float)cur.barometer);
	printf("\t\t   Humidity		%4.2f% \n", cur.outside_humidity);
	printf("\t\t  Dew Point		%4.2f \n", cur.dewpoint);
	printf("\t\t Total Rain		%4.2f inches\n\n", cur.total_rain); 
    
	printf("\tRyker Inside Conditions:      \n");
	printf("\t\tTemperature		%4.2f F",cur.inside_temp);
	printf(" (%4.2f C)\n",(cur.inside_temp-32)*5/9); //converts the data into celsius
	printf("\t\t   Humidity		%4.2f% \n\n",cur.inside_humidity);
	
	printf("\tDaily Highs: 	   \n");
	printf("\t\tOutside Temperature 	%4.2f F (%4.2f C)\n ", shms->daily_high.outside_temp, (shms->daily_high.outside_temp-32)*5/9);
	printf("\t\t Inside Temperature  	%4.2f F (%4.2f C)\n\n ", shms->daily_high.inside_temp, (shms->daily_high.inside_temp-32)*5/9);
	
	printf("\tDaily Lows:       \n");
	printf("\t\tOutside Temperature 	%4.2f F (%4.2f C)\n ", shms->daily_low.outside_temp, (shms->daily_low.outside_temp-32)*5/9);
	printf("\t\t Inside Temperature  	%4.2f F (%4.2f C)\n\n ", shms->daily_low.inside_temp, (shms->daily_low.inside_temp-32)*5/9);

	printf("\tAverage Temperatures:       \n");
	printf("\t    24H Averages:\n");
	printf("\t\tOutside Temperature 	%4.2f F (%4.2f C)\n ", tempavgs.outside_temp, (tempavgs.outside_temp-32)*5/9);
	printf("\t\t Inside Temperature	%4.2f F (%4.2f C)\n ", tempavgs.inside_temp, (tempavgs.inside_temp-32)*5/9);
	//TODO: print out monthly averages when we have access to them
}

// This function converts the rain from drops to inches.
float cvt_rain(int rain)
{
    unsigned mask = (1 << 4) - 1;
    unsigned clicks = rain  & 0xFF;
    unsigned size = rain & mask;
    unsigned scale = 0;
    unsigned result  = 0;
    switch(size)
    {
        case 0:
            scale = 0.1;
            break;
        case 1:
            scale = 0.01;
            break;
        case 2:
            scale = 0.2;
            break;
        case 3:
            scale = 1.0;
            break;
        case 4:
            scale = size;
            break;
        case 5:
            scale = size;
            break;
    }
    result = scale*clicks;
    return result;
}

const char* cvt_direction(int direction)
{
    /*Data is stored as an encoded direction, so the array will store the string descriptions*/
    char * const dirs[16] = {"N","NNE","NE","ENE","E", "ESE","SE","SSE","S","SSW","SW","WSW","W","WNW","NW","NNW"};
	if(direction == 255)
		return "NO WIND";
	
	return dirs[(int)(direction/22.5)];
}
// this takes the encoded data and coverts it average temperatures and returns the data as a float
arc_struct get_avgs(sharedmem_struct* shms)
{
	arc_struct avgs;
        int i;

	avgs.outside_temp = 0;
	avgs.inside_temp = 0;


	for(i = 0; i < shms->lastUsedIndex; i++)
	{
		avgs.outside_temp += shms->archive[i].outside_temp;
		avgs.inside_temp += shms->archive[i].inside_temp;
	}

	avgs.outside_temp /= (float)shms->lastUsedIndex;
	avgs.inside_temp /= (float)shms->lastUsedIndex;
	
	return avgs;
}
