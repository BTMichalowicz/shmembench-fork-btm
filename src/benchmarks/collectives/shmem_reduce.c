/**
  @file shmem_collect.c
  @brief Implementation of the shmem_reduce benchmarks.
  @author Michael Beebe (Texas Tech University)
  @author Benjamin Michalowicz (Ohio State University)
 */

#include "shmem_reduce.h"

/**
  @brief Run the bandwidth benchmark for shmem_collect
  @param min_msg_size Minimum message size for the test in bytes
  @param max_msg_size Maximum message size for the test in bytes
  @param ntimes Number of times to run the benchmark
 */
void bench_shmem_reduce_bw(int min_msg_size, int max_msg_size, int ntimes) {
  /* Ensure there are at least 2 PEs available to run the benchmark */
  if (!check_if_atleast_2_pes()) {
    return;
  }

  /* Variables for message sizes, times, and bandwidths */
  int *msg_sizes;
  double *times, *bandwidths;
  int num_sizes = 0;

  char *env = getenv("SHMEMBENCH_REDUCE_OP");
//  if (env != NULL){
//      fprintf(stdout, "Using the following op: %*s\n", 4, env);
//  }


  /* Setup benchmark */
  setup_bench(min_msg_size, max_msg_size, &num_sizes, &msg_sizes, &times,
              &bandwidths);

#if defined(USE_14)
  /* Setup pSync array */
  long *pSync = (long *)shmem_malloc(SHMEM_COLLECT_SYNC_SIZE * sizeof(long));
  for (int i = 0; i < SHMEM_COLLECT_SYNC_SIZE; i++) {
    pSync[i] = SHMEM_SYNC_VALUE;
  }
  shmem_barrier_all();
#endif

  /* Run the benchmark */
  for (int i = 0, size = min_msg_size; size <= max_msg_size; size *= 2, i++) {
    /* Validate the message size for the long datatype */
    int valid_size = validate_typed_size(size, sizeof(unsigned long), "unsigned long");
    msg_sizes[i] = valid_size;

    /* Calculate the number of elements based on the validated size */
    int elem_count = calculate_elem_count(valid_size, sizeof(unsigned long));

    /* Allocate memory for source and destination arrays */
    unsigned long *source = (unsigned long *)shmem_malloc(elem_count * sizeof(unsigned long));
    unsigned long *dest = (unsigned long *)shmem_malloc(elem_count * sizeof(unsigned long));

    /* Initialize the source buffer with data */
    for (int j = 0; j < elem_count; j++) {
      source[j] = j;
      dest[i] = 0;
    }

//  if (shmem_my_pe() == 0){
//        fprintf(stdout, "src Buffer contents:\n");
//        for (int j = 0; j < elem_count; j++){
//            fprintf(stdout, "%ld ", source[j]);
//        }
//        fprintf(stdout, "\n");
//    }



    double start_time, end_time;

    /* Sync PEs */
    shmem_barrier_all();

    /* Start timer */
    start_time = mysecond();

    /* Perform the shmem_collect operation for the specified number of times */
    for (int j = 0; j < ntimes; j++) {
        memset(dest, 0, elem_count*sizeof(unsigned long));

        if (env == NULL || strcmp(env, "sum") == 0){
#if defined(USE_14)
            shmem_ulong_sum_to_all(dest, source, elem_count, 0, 0, npes, pSync);
#elif defined(USE_15)
            shmem_ulong_sum_reduce(SHMEM_TEAM_WORLD, dest, source, elem_count);
#endif
        }else if (strcmp(env, "prod") == 0){
#if defined(USE_14)
            shmem_ulong_prod_to_all(dest, source, elem_count, 0, 0, npes, pSync);
#elif defined(USE_15)
            shmem_ulong_prod_reduce(SHMEM_TEAM_WORLD, dest, source, elem_count);
#endif
        }else if (strcmp(env, "max") == 0){
#if defined(USE_14)
            shmem_ulong_max_to_all(dest, source, elem_count, 0, 0, npes, pSync);
#elif defined(USE_15)
            shmem_ulong_max_reduce(SHMEM_TEAM_WORLD, dest, source, elem_count);
#endif
        }else if (strcmp(env, "min") == 0){
#if defined(USE_14)
            shmem_ulong_min_to_all(dest, source, elem_count, 0, 0, npes, pSync);
#elif defined(USE_15)
            shmem_ulong_min_reduce(SHMEM_TEAM_WORLD, dest, source, elem_count);
#endif
        }else if (strcmp(env, "and") == 0){
#if defined(USE_14)
            shmem_ulong_and_to_all(dest, source, elem_count, 0, 0, npes, pSync);
#elif defined(USE_15)
            shmem_ulong_and_reduce(SHMEM_TEAM_WORLD, dest, source, elem_count);
#endif
        }else if (strcmp(env, "or") == 0){
#if defined(USE_14)
            shmem_ulong_or_to_all(dest, source, elem_count, 0, 0, npes, pSync);
#elif defined(USE_15)
            shmem_ulong_or_reduce(SHMEM_TEAM_WORLD, dest, source, elem_count);
#endif

        }else if (strcmp(env, "xor") == 0){
#if defined(USE_14)
            shmem_ulong_xor_to_all(dest, source, elem_count, 0, 0, npes, pSync);
#elif defined(USE_15)
            shmem_ulong_xor_reduce(SHMEM_TEAM_WORLD, dest, source, elem_count);
#endif
        }
    }
    shmem_quiet();
    
    /* Stop timer */
    end_time = mysecond();

    /* Calculate average time per operation in useconds */
    times[i] = (end_time - start_time) * 1e6 / ntimes;
//    if (shmem_my_pe() == 0){
//        fprintf(stdout, "Dest Buffer contents:\n");
//        for (int j = 0; j < elem_count; j++){
//            fprintf(stdout, "%ld ", dest[j]);
//        }
//        fprintf(stdout, "\n");
//    }


    /* Calculate bandwidth*/
    bandwidths[i] = calculate_bw(valid_size, times[i]);

    /* Free the allocated memory for source and destination arrays */
    shmem_free(source);
    shmem_free(dest);
  }

  /* Display results */
  shmem_barrier_all();
  if (shmem_my_pe() == 0) {
    display_results(times, msg_sizes, bandwidths, "bw", num_sizes);
  }
  shmem_barrier_all();

#if defined(USE_14)
  /* Free pSync allocated for OpenSHMEM 1.4 path */
  shmem_free(pSync);
#endif

  /* Free the memory allocated for message sizes, times, and bandwidths */
  free(msg_sizes);
  free(times);
  free(bandwidths);
}
