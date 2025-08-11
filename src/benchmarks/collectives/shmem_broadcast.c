/**
  @file shmem_broadcast.c
  @brief Implementation of the shmem_broadcast benchmarks.
  @author Michael Beebe (Texas Tech University)
*/

#include "shmem_broadcast.h"

/*************************************************************
  @brief Run the bandwidth benchmark for shmem_broadcast
  @param min_msg_size Minimum message size for the test in bytes
  @param max_msg_size Maximum message size for the test in bytes
  @param ntimes Number of times to run the benchmark
 *************************************************************/
void bench_shmem_broadcast_bw(int min_msg_size, int max_msg_size, int ntimes) {
  /* Ensure there are at least 2 PEs available to run the benchmark */
  if (!check_if_atleast_2_pes()) {
    return;
  }

  /* Variables for message sizes, times, and bandwidths */
  int *msg_sizes;
  double *times, *bandwidths;
  int num_sizes = 0;

  /* Initialize the benchmark setup, including message sizes, times, and
   * bandwidths */
  setup_bench(min_msg_size, max_msg_size, &num_sizes, &msg_sizes, &times,
              &bandwidths);

#if defined(USE_14)
  /* Setup pSync array */
  long *pSync = (long *)shmem_malloc(SHMEM_BCAST_SYNC_SIZE * sizeof(long));
  for (int i = 0; i < SHMEM_BCAST_SYNC_SIZE; i++) {
    pSync[i] = SHMEM_SYNC_VALUE;
  }
  shmem_barrier_all();
  
  /* Get the number of processing elements (PEs) - needed for USE_14 */
  int npes = shmem_n_pes();
#endif

 /* Allocate memory for source and destination arrays */
    long *source = (long *)shmem_malloc(max_msg_size);
    long *dest = (long *)shmem_malloc(max_msg_size);

  /* Loop through each message size, doubling the size at each iteration */
  for (int i = 0, size = min_msg_size; size <= max_msg_size; size *= 2, i++) {
      memset(source, 1234, max_msg_size);
      memset(dest, 0, max_msg_size);
    /* Validate the message size for the long datatype */
    int valid_size = validate_typed_size(size, sizeof(long), "long");
    msg_sizes[i] = valid_size;
    
    /* Calculate the number of elements based on the validated size */
    int elem_count = calculate_elem_count(valid_size, sizeof(long));

   
    /* Initialize the source buffer with data */
    for (int j = 0; j < elem_count; j++) {
      source[j] = j;
    }

    double start_time, end_time;

    /* Synchronize all PEs before starting the benchmark */
    shmem_barrier_all();
    start_time = mysecond(); /* Record the start time */

    /* Perform the shmem_broadcast operation for the specified number of times
     */
    for (int j = 0; j < ntimes; j++) {
#if defined(USE_14)
      shmem_broadcast64(dest, source, elem_count, 0, 0, 0, npes, pSync);
#elif defined(USE_15)
      shmem_broadcast(SHMEM_TEAM_WORLD, dest, source, elem_count, 0);
#endif
    }
    shmem_quiet();
    end_time = mysecond(); /* Record the end time */

    /* Calculate the average time per operation and bandwidth */
    times[i] = (end_time - start_time) * 1e6 / ntimes;
    bandwidths[i] = calculate_bw(valid_size, times[i]);

    /* Free the allocated memory for source and destination arrays */
  //  shmem_free(source);
  //  shmem_free(dest);
  }

  /* Synchronize all PEs before displaying the results */
  shmem_barrier_all();
  if (shmem_my_pe() == 0) {
    /* Display the benchmark results */
    display_results(times, msg_sizes, bandwidths, "bw", num_sizes);
  }
  shmem_barrier_all();

  /* Free the memory allocated for message sizes, times, and bandwidths */
  free(msg_sizes);
  free(times);
  free(bandwidths);
  shmem_free (source);
  shmem_free (dest);
}

/*************************************************************
  @brief Run the latency benchmark for shmem_broadcast
  @param min_msg_size Minimum message size for the test in bytes
  @param max_msg_size Maximum message size for the test in bytes
  @param ntimes Number of times to run the benchmark
 *************************************************************/
void bench_shmem_broadcast_latency(int min_msg_size, int max_msg_size,
                                   int ntimes) {
  /* Ensure there are at least 2 PEs available to run the benchmark */
  if (!check_if_atleast_2_pes()) {
    return;
  }

  /* Variables for message sizes, times, and latencies */
  int *msg_sizes;
  double *times, *latencies;
  int num_sizes = 0;

  /* Initialize the benchmark setup, including message sizes, times, and
   * latencies */
  setup_bench(min_msg_size, max_msg_size, &num_sizes, &msg_sizes, &times,
              &latencies);

#if defined(USE_14)
  /* Setup pSync array */
  long *pSync = (long *)shmem_malloc(SHMEM_BCAST_SYNC_SIZE * sizeof(long));
  for (int i = 0; i < SHMEM_BCAST_SYNC_SIZE; i++) {
    pSync[i] = SHMEM_SYNC_VALUE;
  }
  shmem_barrier_all();
  
  /* Get the number of processing elements (PEs) - needed for USE_14 */
  int npes = shmem_n_pes();
#endif

  /* Loop through each message size, doubling the size at each iteration */
  for (int i = 0, size = min_msg_size; size <= max_msg_size; size *= 2, i++) {
    /* Validate the message size for the long datatype */
    int valid_size = validate_typed_size(size, sizeof(long), "long");
    msg_sizes[i] = valid_size;
    
    /* Calculate the number of elements based on the validated size */
    int elem_count = calculate_elem_count(valid_size, sizeof(long));

    /* Source and destination arrays for shmem_broadcast */
    long *source = (long *)shmem_malloc(elem_count * sizeof(long));
    long *dest = (long *)shmem_malloc(elem_count * sizeof(long));

    /* Initialize the source buffer with data */
    for (int j = 0; j < elem_count; j++) {
      source[j] = j;
    }

    double start_time, end_time;

    /* Synchronize all PEs before starting the benchmark */
    shmem_barrier_all();
    start_time = mysecond(); /* Record the start time */

    /* Perform the shmem_broadcast operation for the specified number of times
     */
    for (int j = 0; j < ntimes; j++) {
#if defined(USE_14)
      shmem_broadcast64(dest, source, elem_count, 0, 0, 0, npes, pSync);
#elif defined(USE_15)
      shmem_broadcast(SHMEM_TEAM_WORLD, dest, source, elem_count, 0);
#endif
    }
    shmem_quiet();

    end_time = mysecond(); /* Record the end time */

    /* Calculate the average time per operation and record latency */
    times[i] = (end_time - start_time) * 1e6 / ntimes;
    latencies[i] = calculate_latency(times[i]);

    /* Free the allocated memory for source and destination arrays */
    shmem_free(source);
    shmem_free(dest);
  }

  /* Synchronize all PEs before displaying the results */
  shmem_barrier_all();
  if (shmem_my_pe() == 0) {
    /* Display the benchmark results */
    display_results(times, msg_sizes, latencies, "latency", num_sizes);
  }
  shmem_barrier_all();

  /* Free the memory allocated for message sizes, times, and latencies */
  free(msg_sizes);
  free(times);
  free(latencies);
}
