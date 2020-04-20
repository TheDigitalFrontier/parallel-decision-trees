#include "timing.h"

#if defined(CLOCK_HIGHRES)
#  define CLOCK CLOCK_HIGHRES
#elif defined(CLOCK_REALTIME)
#  define CLOCK CLOCK_REALTIME
#elif defined(USE_CLOCK)
/* Nothing */
#else
#  error No suitable clock found.  Check docs for clock_gettime.
#endif

#ifndef USE_CLOCK

long double timespec_to_ldbl(struct timespec x)
{
    return x.tv_sec + 1.0E-9 * x.tv_nsec;
}

long double timespec_diff(struct timespec start, struct timespec finish)
{
    long double out;
    out = finish.tv_nsec - (double) start.tv_nsec;
    out *= 1.0E-9L;
    out += finish.tv_sec - (double) start.tv_sec;
    return out;
}

long double timer_resolution()
{
    struct timespec x;
    clock_getres(CLOCK, &x);
    return timespec_to_ldbl(x);
}

void get_time(struct timespec* x)
{
    clock_gettime(CLOCK, x);
}

#endif
