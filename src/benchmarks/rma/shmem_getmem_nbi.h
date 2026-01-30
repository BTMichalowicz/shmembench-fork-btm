/**
  @file shmem_getmem_nbi.h
  @author Michael Beebe (Texas Tech University)
*/

#ifndef SHMEM_GETMEM_NBI_H
#define SHMEM_GETMEM_NBI_H

#include <shmem.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_getmem_nbi
  @param opts Benchmark options given by the user 
 */
void bench_shmem_getmem_nbi_bw(options * opts);

/**
  @brief Run the bidirectional bandwidth benchmark for shmem_getmem_nbi
  @param opts Benchmark options given by the user 
 */
void bench_shmem_getmem_nbi_bibw(options * opts);

#endif /* SHMEM_GETMEM_NBI_H */
