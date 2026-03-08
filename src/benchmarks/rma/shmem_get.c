/**
  @file shmem_get.c
  @author Michael Beebe (Texas Tech University)
*/

#include "shmem_get.h"

/**
  @brief Run the bandwidth benchmark for shmem_get
  @param opts benchmark options given by user 
 */
void bench_shmem_get_bw(options * opts) {
  /* Check the number of PEs before doing anything */
  if (!check_if_exactly_2_pes()) {
    return;
  }

  int mype = shmem_my_pe();

  /* Stuff that will be used throughout the benchmark */
  int *msg_sizes;
  double *times, *bandwidths;
  int num_sizes = 0;

  /* Setup the benchmark */
  setup_bench(opts->min_msg_size, opts->max_msg_size, &num_sizes, &msg_sizes, &times,
              &bandwidths);

  /* Run the benchmark */
  for (int i = 0, size = opts->min_msg_size; size <= opts->max_msg_size; size *= 2, i++) {
    /* Validate and adjust the message size to be compatible with long type */
    int valid_size = validate_typed_size(size, sizeof(long), "long");
    msg_sizes[i] = valid_size;

    /* Calculate number of elements based on validated size */
    int elem_count = calculate_elem_count(valid_size, sizeof(long));

    /* Source and destination arrays for the shmem_get */
    long *source = (long *)shmem_malloc(elem_count * sizeof(long));
    long *dest = (long *)shmem_malloc(elem_count * sizeof(long));

    /* Initialize source buffer */
    for (int j = 0; j < elem_count; j++) {
      source[j] = j;
    }

    /* Initialize start and end time */
    double start_time, end_time;

    /* Sync PEs */
    shmem_barrier_all();

    /* Do warmup rounds */
    if (mype == 0) {
      for (int j = 0; j < opts->warmups; j++) {
#if defined(USE_14) || defined(USE_15)
        shmem_get(dest, source, elem_count, 1);
#endif
      }
    }

    /* Start timer */
    start_time = mysecond();

    /* Perform ntimes shmem_gets with P0 */
    if (mype == 0) {
      /* Perform ntimes shmem_gets */
      for (int j = 0; j < opts->ntimes; j++) {
#if defined(USE_14) || defined(USE_15)
        shmem_get(dest, source, elem_count, 1);
#endif
      }
    }
    
    /* Stop timer */
    end_time = mysecond();

    /* Calculate average time per operation in useconds */
    times[i] = (end_time - start_time) * 1e6 / opts->ntimes;

    /* Calculate bandwidth using actual bytes transferred */
    bandwidths[i] = calculate_bw(valid_size, times[i]);

    /* Sync PEs */
    shmem_barrier_all();

    /* Free the buffers */
    shmem_free(source);
    shmem_free(dest);
  }

  /* Display results */
  shmem_barrier_all();
  if (mype == 0) {
    display_results(times, msg_sizes, bandwidths, "bw", num_sizes);
  }
  shmem_barrier_all();

  /* Free memory */
  free(msg_sizes);
  free(times);
  free(bandwidths);
}

/*************************************************************
  @brief Run the bidirectional bandwidth benchmark for shmem_get
  @param opts benchmark options given by user 
 *************************************************************/
void bench_shmem_get_bibw(options *opts) {
  /* Check the number of PEs before doing anything */
  if (!check_if_exactly_2_pes()) {
    return;
  }

  int mype = shmem_my_pe();
  int peer = (mype == 0) ? 1 : 0;

  /* Stuff that will be used throughout the benchmark */
  int *msg_sizes;
  double *times, *bandwidths;
  int num_sizes = 0;

  /* Setup the benchmark */
  setup_bench(opts->min_msg_size, opts->max_msg_size, &num_sizes, &msg_sizes, &times,
              &bandwidths);

  /* Run the benchmark */
  for (int i = 0, size = opts->min_msg_size; size <= opts->max_msg_size; size *= 2, i++) {
    /* Validate and adjust the message size to be compatible with long type */
    int valid_size = validate_typed_size(size, sizeof(long), "long");
    msg_sizes[i] = valid_size;

    /* Calculate number of elements based on validated size */
    int elem_count = calculate_elem_count(valid_size, sizeof(long));

    /* Source and destination arrays for the shmem_get */
    long *source = (long *)shmem_malloc(elem_count * sizeof(long));
    long *dest = (long *)shmem_malloc(elem_count * sizeof(long));

    /* Initialize source buffer */
    for (int j = 0; j < elem_count; j++) {
      source[j] = j;
    }

    /* Initialize start and end time */
    double start_time, end_time;

    /* Sync PEs */
    shmem_barrier_all();

    /* Start timer */
    start_time = mysecond();

    /* Perform ntimes bidirectional shmem_gets */
    for (int j = 0; j < opts->ntimes; j++) {
#if defined(USE_14) || defined(USE_15)
      shmem_get(dest, source, elem_count, peer); /* each PE gets from other PE */
#endif
    }

    /* Stop timer */
    end_time = mysecond();

    /* Calculate average time per operation in useconds */
    times[i] = (end_time - start_time) * 1e6 / (opts->ntimes);
    /* Calculate bidirectional bandwidth using actual bytes transferred */
    bandwidths[i] = calculate_bibw(valid_size, times[i]);

    /* Sync PEs */
    shmem_barrier_all();

    /* Free the buffers */
    shmem_free(source);
    shmem_free(dest);
  }

  /* Display results */
  shmem_barrier_all();
  if (shmem_my_pe() == 0) {
    display_results(times, msg_sizes, bandwidths, "bibw", num_sizes);
  }
  shmem_barrier_all();

  /* Free memory */
  free(msg_sizes);
  free(times);
  free(bandwidths);
}

/*************************************************************
  @brief Run the latency benchmark for shmem_get
 @param opts benchmark options given by user 
 *************************************************************/
void bench_shmem_get_latency(options * opts) {
  /* Check the number of PEs before doing anything */
  if (!check_if_exactly_2_pes()) {
    return;
  }

  int mype = shmem_my_pe();

  /* Stuff that will be used throughout the benchmark */
  int *msg_sizes;
  double *times, *latencies;
  int num_sizes = 0;

  /* Setup the benchmark */
  setup_bench(opts->min_msg_size, opts->max_msg_size, &num_sizes, &msg_sizes, &times,
              &latencies);

  /* Run the benchmark */
  for (int i = 0, size = opts->min_msg_size; size <= opts->max_msg_size; size *= 2, i++) {
    /* Validate and adjust the message size to be compatible with long type */
    int valid_size = validate_typed_size(size, sizeof(long), "long");
    msg_sizes[i] = valid_size;
    
    /* Calculate number of elements based on validated size */
    int elem_count = calculate_elem_count(valid_size, sizeof(long));

    /* Source and destination arrays for the shmem_get */
    long *source = (long *)shmem_malloc(elem_count * sizeof(long));
    long *dest = (long *)shmem_malloc(elem_count * sizeof(long));

    /* Initialize source buffer */
    for (int j = 0; j < elem_count; j++) {
      source[j] = j;
    }

    /* Initialize total time */
    double total_time = 0.0;

    /* Sync PEs */
    shmem_barrier_all();

    /* Perform ntimes shmem_gets and accumulate total time */
    if (mype == 0) {
      for (int j = 0; j < opts->ntimes; j++) {
        double start_time = mysecond();
#if defined(USE_14) || defined(USE_15)
        shmem_get(dest, source, elem_count, 1);
#endif
        double end_time = mysecond();
        total_time += (end_time - start_time) * 1e6;
      }
    }

    /* Calculate average latency per operation in microseconds */
    times[i] = total_time / opts->ntimes;

    /* Record latency */
    latencies[i] = times[i];

    /* Sync PEs */
    shmem_barrier_all();

    /* Free the buffers */
    shmem_free(source);
    shmem_free(dest);
  }

  /* Display results */
  shmem_barrier_all();
  if (mype == 0) {
    display_results(times, msg_sizes, latencies, "latency", num_sizes);
  }
  shmem_barrier_all();

  /* Free memory */
  free(msg_sizes);
  free(times);
  free(latencies);
}
