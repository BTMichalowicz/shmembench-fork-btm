/**
  @file shmem_iget.h
  @author Michael Beebe (Texas Tech University)
*/

#ifndef SHMEM_IGET_H
#define SHMEM_IGET_H

#include <shmem.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_iget
  @param opts Benchmark options given by the user 
 */
void bench_shmem_iget_bw(options * opts);

/**
  @brief Run the bidirectional bandwidth benchmark for shmem_iget
  @param opts Benchmark options given by the user 
 */
void bench_shmem_iget_bibw(options * opts);

#endif /* SHMEM_IGET_H */
