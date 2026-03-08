/**
  @file shmem_atomic_compare_swap.h
  @brief Header file for shmem_atomic_compare_swap latency benchmark with
  improvements
*/

#ifndef SHMEM_ATOMIC_COMPARE_SWAP_H
#define SHMEM_ATOMIC_COMPARE_SWAP_H

#include <shmem.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the latency benchmark for shmem_atomic_compare_swap
  @param opts Benchmark options given by the user 
 */
void bench_shmem_atomic_compare_swap_latency(options * opts);

#endif /* SHMEM_ATOMIC_COMPARE_SWAP_H */
