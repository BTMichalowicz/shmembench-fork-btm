/**
  @file shmem_alltoall.h
  @author Michael Beebe (Texas Tech University)
*/

#ifndef SHMEM_ALLTOALL_H
#define SHMEM_ALLTOALL_H

#include <shmem.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_alltoall
  @param opts Benchmark options given by the user 
 */
void bench_shmem_alltoall_bw(options * opts);

#endif /* SHMEM_ALLTOALL_H */
