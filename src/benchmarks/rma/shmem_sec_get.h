/**
  @file shmem_get.h
  @author Michael Beebe (Texas Tech University)
  @author Benjamin Michalowicz (Ohio State University)
*/

#ifndef _SHMEM_SEC_GET_H_
#define _SHMEM_SEC_GET_H_

#include "shmembench.h"

/**
  @brief Run the bandwidth benchmark for shmem_get
  @param min_msg_size Minimum message size for test in bytes
  @param max_msg_size Maximum message size for test in bytes
  @param ntimes Number of repetitions to get the avgs from
 */
void bench_shmem_sec_get_bw(int min_msg_size, int max_msg_size, int ntimes);

/**
  @brief Run the bidirectional bandwidth benchmark for shmem_get
  @param min_msg_size Minimum message size for test in bytes
  @param max_msg_size Maximum message size for test in bytes
  @param ntimes Number of repetitions to get the avgs from
 */
void bench_shmem_sec_get_bibw(int min_msg_size, int max_msg_size, int ntimes);

/**
  @brief Run the latency benchmark for shmem_get
  @param min_msg_size Minimum message size for test in bytes
  @param max_msg_size Maximum message size for test in bytes
  @param ntimes Number of repetitions to get the avgs from
 */
void bench_shmem_sec_get_latency(int min_msg_size, int max_msg_size, int ntimes);

#endif /* _SHMEM_SEC_GET_H_ */
