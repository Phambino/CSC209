#ifndef __JOB_PROTOCOL_H__
#define __JOB_PROTOCOL_H__

#ifndef PORT
  #define PORT 50000
#endif

#ifndef MAX_JOBS
    #define MAX_JOBS 32
#endif

// No paths or lines may be larger than the BUFSIZE below
#define BUFSIZE 256

// TODO: Add any extern variable declarations or struct declarations needed.
int commands_check(char job[BUFSIZE]);
int getjob(int job[MAX_JOBS]);
#endif
