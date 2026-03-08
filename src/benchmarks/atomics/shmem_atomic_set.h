/**
  @file shmem_atomic_set.h
  @brief Header file for shmem_atomic_set latency benchmark with support for
  OpenSHMEM 1.4 and 1.5
*/

#ifndef SHMEM_ATOMIC_SET_H
#define SHMEM_ATOMIC_SET_H

#include <shmem.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the latency benchmark for shmem_atomic_set
  @param opts Benchmark options given by the user 
 */
void bench_shmem_atomic_set_latency(options * opts);

#endif /* SHMEM_ATOMIC_SET_H */
