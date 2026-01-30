/**
  @file shmem_get.h
  @author Michael Beebe (Texas Tech University)
*/

#ifndef _SHMEM_GET_H_
#define _SHMEM_GET_H_

#include "shmembench.h"
#include "parse_opts.h"

/**
  @brief Run the bandwidth benchmark for shmem_get
  @param min_msg_size Minimum message size for test in bytes
  @param max_msg_size Maximum message size for test in bytes
  @param ntimes Number of repetitions to get the avgs from
 */
void bench_shmem_get_bw(options * opts);

/**
  @brief Run the bidirectional bandwidth benchmark for shmem_get
  @param min_msg_size Minimum message size for test in bytes
  @param max_msg_size Maximum message size for test in bytes
  @param ntimes Number of repetitions to get the avgs from
 */
void bench_shmem_get_bibw(options * opts);

#endif /* _SHMEM_GET_H_ */
