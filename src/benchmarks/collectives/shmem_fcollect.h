/**
  @file shmem_fcollect.h
  @brief Header file for shmem_fcollect benchmarks.
  @author Michael Beebe (Texas Tech University)
 */

#ifndef SHMEM_FCOLLECT_H
#define SHMEM_FCOLLECT_H

#include <shmem.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_fcollect
  @param min_msg_size Minimum message size for the test in bytes
  @param max_msg_size Maximum message size for the test in bytes
  @param ntimes Number of times to run the benchmark
 */
void bench_shmem_fcollect_bw(options * opts);

#endif /* SHMEM_FCOLLECT_H */
