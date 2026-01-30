/**
  @file shmem_broadcast.h
  @brief Header file for shmem_broadcast benchmarks.
  @author Michael Beebe (Texas Tech University)
 */

#ifndef SHMEM_BROADCAST_H
#define SHMEM_BROADCAST_H

#include <shmem.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_broadcast
  @param opts Benchmark options given by the user 
 */
void bench_shmem_broadcast_bw(options * opts);

#endif /* SHMEM_BROADCAST_H */
