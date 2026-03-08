/**
  @file shmem_alltoallsmem.h
  @brief Header file for shmem_alltoallsmem benchmarks
  @author Michael Beebe (Texas Tech University)
*/

#ifndef SHMEM_ALLTOALLSMEM_H
#define SHMEM_ALLTOALLSMEM_H

#include <shmem.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_alltoallsmem
  @param opts Benchmark options given by the user 
 */
void bench_shmem_alltoallsmem_bw(options * opts);

#endif /* SHMEM_ALLTOALLSMEM_H */
