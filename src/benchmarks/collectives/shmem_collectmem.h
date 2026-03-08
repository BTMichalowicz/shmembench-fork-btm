/**
  @file shmem_collectmem.h
  @brief Header file for shmem_collectmem benchmarks.
  @author Michael Beebe (Texas Tech University)
 */

#ifndef SHMEM_COLLECTMEM_H
#define SHMEM_COLLECTMEM_H

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
void bench_shmem_collectmem_bw(options * opts);

#endif /* SHMEM_COLLECTMEM_H */
