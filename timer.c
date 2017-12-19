#include "timer.h"

time_t timer_start(){
    return clock();
}

double timer_getTime(time_t timer){
    double timeElapsed;
    timeElapsed = (clock()-timer)/(double)CLOCKS_PER_SEC;
    return timeElapsed;
}
