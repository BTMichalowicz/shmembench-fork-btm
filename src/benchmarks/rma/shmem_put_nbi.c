/**
  @file shmem_put_nbi.c
  @author Michael Beebe (Texas Tech University)
*/

#include "shmem_put_nbi.h"

/**
  @brief Run the bandwidth benchmark for shmem_put_nbi
  @param opts Benchmarks options given by the user 
 */
void bench_shmem_put_nbi_bw(options * opts) {
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
    /* Validate the message size for the long datatype */
    int valid_size = validate_typed_size(size, sizeof(long), "long");
    msg_sizes[i] = valid_size;

    /* Calculate the number of elements based on the validated size */
    int elem_count = calculate_elem_count(valid_size, sizeof(long));

    /* Source and destination arrays for the shmem_put_nbi */
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

    /* Do warmup runs */
    if (mype == 0) {
      for (int j = 0; j < opts->warmups; j++) {
#if defined(USE_14) || defined(USE_15)
        shmem_put_nbi(dest, source, elem_count, 1);
        shmem_quiet();
#endif
      }
    }

    shmem_barrier_all();

    /* Start timer */
    start_time = mysecond();

    /* Perform opts->ntimes shmem_put_nbis */
    if (mype == 0) {
      for (int j = 0; j < opts->ntimes; j++) {
#if defined(USE_14) || defined(USE_15)
        shmem_put_nbi(dest, source, elem_count, 1);
        shmem_quiet();
#endif
      }
    }

    /* Stop timer */
    end_time = mysecond();

    /* Calculate average time per operation in useconds */
    times[i] = (end_time - start_time) * 1e6 / opts->ntimes;

    /* Calculate bandwidth using valid size */
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

/**
  @brief Run the bidirectional bandwidth benchmark for shmem_put_nbi
  @param opts Benchmarks options given by the user 
 */
void bench_shmem_put_nbi_bibw(options * opts) {
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
    /* Validate the message size for the long datatype */
    int valid_size = validate_typed_size(size, sizeof(long), "long");
    msg_sizes[i] = valid_size;

    /* Calculate the number of elements based on the validated size */
    int elem_count = calculate_elem_count(valid_size, sizeof(long));

    /* Source and destination arrays for the shmem_put_nbi */
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

    /* Do warmup runs */
    for (int j = 0; j < opts->warmups; j++) {
#if defined(USE_14) || defined(USE_15)
      shmem_put_nbi(dest, source, elem_count, peer); 
      shmem_quiet();
#endif
    }
 
    shmem_barrier_all();

    /* Start timer */
    start_time = mysecond();

    /* Perform opts->ntimes bidirectional shmem_put_nbis */
    for (int j = 0; j < opts->ntimes; j++) {
#if defined(USE_14) || defined(USE_15)
      shmem_put_nbi(dest, source, elem_count, peer); /* each PE sends to other PE */
      shmem_quiet();
#endif
    }

    /* Stop timer */
    end_time = mysecond();

    /* Calculate average time per operation in useconds */
    times[i] = (end_time - start_time) * 1e6 / (opts->ntimes);

    /* Calculate bidirectional bandwidth using valid size */
    bandwidths[i] = calculate_bibw(valid_size, times[i]);

    /* Sync PEs */
    shmem_barrier_all();

    /* Free the buffers */
    shmem_free(source);
    shmem_free(dest);
  }

  /* Display results */
  shmem_barrier_all();
  if (mype == 0) {
    display_results(times, msg_sizes, bandwidths, "bibw", num_sizes);
  }
  shmem_barrier_all();

  /* Free memory */
  free(msg_sizes);
  free(times);
  free(bandwidths);
}

/*************************************************************
  @brief Run the latency benchmark for shmem_put_nbi
  @param opts Benchmarks options given by the user 
 *************************************************************/
void bench_shmem_put_nbi_latency(options * opts) {
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
    /* Validate the message size for the long datatype */
    int valid_size = validate_typed_size(size, sizeof(long), "long");
    msg_sizes[i] = valid_size;
    
    /* Calculate the number of elements based on the validated size */
    int elem_count = calculate_elem_count(valid_size, sizeof(long));

    /* Source and destination arrays for the shmem_put_nbi */
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

    /* Do warmup runs */
    if (mype == 0) {
      for (int j = 0; j < opts->warmups; j++) {
#if defined(USE_14) || defined(USE_15)
        shmem_put_nbi(dest, source, elem_count, 1);
        shmem_quiet();
#endif
      }
    }

    shmem_barrier_all();

    /* Perform opts->ntimes shmem_put_nbis and accumulate total time */
    if (mype == 0) {
      for (int j = 0; j < opts->ntimes; j++) {
        double start_time = mysecond();
#if defined(USE_14) || defined(USE_15)
        shmem_put_nbi(dest, source, elem_count, 1);
        shmem_quiet();
#endif
        double end_time = mysecond();
        total_time += (end_time - start_time) * 1e6;
      }
    }

    /* Sync PEs */
    shmem_barrier_all();

    /* Calculate average latency per operation in microseconds */
    times[i] = total_time / opts->ntimes;

    /* Record latency */
    latencies[i] = times[i];

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
