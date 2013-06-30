/*
 * Just verify temperature conversion function.
 * 
*/

#include <float.h>
#include <limits.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <strings.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>

static double convertKlnTemp(uint8_t temp)
{
	return (double)1/((double)1/(25+273.15) + log((double)temp*1000/(256-temp)/2200)/3987) - 273.15;
}

void main()
{
	int n;
	
	for(n = 33; n < 175; n++)
		printf("\nKtemp %d = degC %3.0f", n, convertKlnTemp(n));
	printf("\n");	
}
