/**
  @file shmem_collect.h
  @brief Header file for shmem_collect benchmarks.
  @author Michael Beebe (Texas Tech University)
 */

#ifndef SHMEM_COLLECT_H
#define SHMEM_COLLECT_H

#include <shmem.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_collect
  @param opts Benchmark options given by the user 
 */
void bench_shmem_collect_bw(options * opts);

#endif /* SHMEM_COLLECT_H */
