#include <tools/time.h>

uint64_t timeStamp(){
  uint64_t time;
  struct timespec ttime;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ttime);
  time = ttime.tv_sec * 1000000000 + ttime.tv_nsec;
  return time;
}
