/**
  @file shmem_iput.h
  @author Michael Beebe (Texas Tech University)
*/

#ifndef SHMEM_IPUT_H
#define SHMEM_IPUT_H

#include <shmem.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_iput
  @param opts Benchmark options given by the user 
 */
void bench_shmem_iput_bw(options * opts);

/**
  @brief Run the bidirectional bandwidth benchmark for shmem_iput
  @param opts Benchmark options given by the user 
 */
void bench_shmem_iput_bibw(options * opts);

#endif /* SHMEM_IPUT_H */
