#ifndef TIMING_H_
#define TIMING_H_

#include <time.h>

#if defined(__cplusplus)
extern "C" {
#endif

#ifdef USE_CLOCK

typedef clock_t timing_t;
#define get_time(tref)        ((*tref) = clock())
#define timespec_diff(t1,t2)  ((double) (t2-t1)/CLOCKS_PER_SEC)

#else

typedef struct timespec timing_t;
long double timespec_to_dbl (struct timespec x);
long double timespec_diff (struct timespec start, struct timespec finish);

long double timer_resolution (void);
void get_time (struct timespec*);
#endif

#if defined(__cplusplus)
}
#endif

#endif /* TIMING_H_ */
