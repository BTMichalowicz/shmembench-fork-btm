/**
  @file shmem_put.h
  @author Michael Beebe (Texas Tech University)
*/

#ifndef SHMEM_PUT_H
#define SHMEM_PUT_H

#include <shmem.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_put
  @param min_msg_size Minimum message size for test in bytes
  @param max_msg_size Maximum message size for test in bytes
 */
void bench_shmem_put_bw(options * opts);

/**
  @brief Run the bidirectional bandwidth benchmark for shmem_put
  @param min_msg_size Minimum message size for test in bytes
  @param max_msg_size Maximum message size for test in bytes
 */
void bench_shmem_put_bibw(options * opts);

#endif /* SHMEM_PUT_H */
