/**
  @file shmem_getmem.h
  @author Michael Beebe (Texas Tech University)
*/

#ifndef _SHMEM_GETMEM_H_
#define _SHMEM_GETMEM_H_

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_getmem
  @param opts Benchmark options given by the user 
 */
void bench_shmem_getmem_bw(options * opts);

/**
  @brief Run the bidirectional bandwidth benchmark for shmem_getmem
  @param opts Benchmark options given by the user 
 */
void bench_shmem_getmem_bibw(options * opts);

#endif /* _SHMEM_GETMEM_H_ */
