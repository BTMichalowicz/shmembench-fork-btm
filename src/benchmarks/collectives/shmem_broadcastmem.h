/**
  @file shmem_broadcastmem.h
  @brief Header file for shmem_broadcastmem benchmarks.
  @author Michael Beebe (Texas Tech University)
 */

#ifndef SHMEM_BROADCASTMEM_H
#define SHMEM_BROADCASTMEM_H

#include <shmem.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_broadcastmem
  @param opts Benchmark options given by the user 
 */
void bench_shmem_broadcastmem_bw(options * opts);

#endif /* SHMEM_BROADCASTMEM_H */
