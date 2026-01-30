/**
  @file shmem_alltoalls.h
  @brief Header file for shmem_alltoalls benchmarks
  @author Michael Beebe (Texas Tech University)
*/

#ifndef SHMEM_ALLTOALLS_H
#define SHMEM_ALLTOALLS_H

#include <shmem.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_alltoalls
  @param min_msg_size Minimum message size for test in bytes
  @param max_msg_size Maximum message size for test in bytes
  @param ntimes Number of times the benchmark should run
 */
void bench_shmem_alltoalls_bw(options * opts);

#endif /* SHMEM_ALLTOALLS_H */
