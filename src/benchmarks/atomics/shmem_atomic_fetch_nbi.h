/**
  @file shmem_atomic_fetch_nbi.h
  @brief Header file for shmem_atomic_fetch_nbi latency benchmark with support
  for OpenSHMEM 1.4 and 1.5
*/

#ifndef SHMEM_ATOMIC_FETCH_NBI_H
#define SHMEM_ATOMIC_FETCH_NBI_H

#include <shmem.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the latency benchmark for shmem_atomic_fetch_nbi
  @param opts Benchmark options given by the user 
 */
void bench_shmem_atomic_fetch_nbi_latency(options * opts);

#endif /* SHMEM_ATOMIC_FETCH_NBI_H */
