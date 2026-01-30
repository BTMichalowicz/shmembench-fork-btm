/**
  @file shmem_alltoallmem.h
  @author Michael Beebe (Texas Tech University)
*/

#ifndef SHMEM_ALLTOALLMEM_H
#define SHMEM_ALLTOALLMEM_H

#include <shmem.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_alltoallmem
  @param opts Benchmark options given by the user 
 */
void bench_shmem_alltoallmem_bw(options * opts);

#endif /* SHMEM_ALLTOALLMEM_H */
