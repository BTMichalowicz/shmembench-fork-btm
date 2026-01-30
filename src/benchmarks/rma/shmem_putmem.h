/**
  @file shmem_putmem.h
  @author Michael Beebe (Texas Tech University)
*/

#ifndef SHMEM_PUTMEM_H
#define SHMEM_PUTMEM_H

#include <shmem.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_putmem
  @param opts Benchmark options given by the user 
 */
void bench_shmem_putmem_bw(options * opts);

/**
  @brief Run the bidirectional bandwidth benchmark for shmem_putmem
  @param opts Benchmark options given by the user 
 */
void bench_shmem_putmem_bibw(options * opts);

#endif /* SHMEM_PUTMEM_H */
