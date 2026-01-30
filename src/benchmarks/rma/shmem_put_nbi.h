/**
  @file shmem_put_nbi.h
  @author Michael Beebe (Texas Tech University)
*/

#ifndef SHMEM_PUT_NBI_H
#define SHMEM_PUT_NBI_H

#include <shmem.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_put_nbi
  @param min_msg_size Minimum message size for test in bytes
  @param max_msg_size Maximum message size for test in bytes
  @param ntimes Number of repetitions to get the avgs from
 */
void bench_shmem_put_nbi_bw(options * opts);

/**
  @brief Run the bidirectional bandwidth benchmark for shmem_put_nbi
  @param min_msg_size Minimum message size for test in bytes
  @param max_msg_size Maximum message size for test in bytes
  @param ntimes Number of repetitions to get the avgs from
 */
void bench_shmem_put_nbi_bibw(options * opts);

#endif /* SHMEM_PUT_NBI_H */
