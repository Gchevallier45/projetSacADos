#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void timeFile(double temps, int noInstance);
time_t timer_start();
double timer_getTime(time_t timer);


#endif // TIMER_H_INCLUDED
