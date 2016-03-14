#include <iostream>
#include <thread>
#include <atomic>

#include <cuda.h>
#include <curand.h>

#include <boost/lockfree/spsc_queue.hpp>

#include "rnd_generator.h"


#define CUDA_CALL(x) do { if((x)!=cudaSuccess) { \
    printf("Error at %s:%d\n",__FILE__,__LINE__);\
    return EXIT_FAILURE;}} while(0)
#define CURAND_CALL(x) do { if((x)!=CURAND_STATUS_SUCCESS) { \
    printf("Error at %s:%d\n",__FILE__,__LINE__);\
    return EXIT_FAILURE;}} while(0)


#define RNG_QUEUE_SIZE 100000000
#define RNG_ARRAY_SIZE 10000000


using namespace std;

boost::lockfree::spsc_queue<float, boost::lockfree::capacity<RNG_QUEUE_SIZE> > spsc_queue;


curandGenerator_t gen;
float *devData;
std::atomic<bool> rng_producer_done (false);

thread rng_producer_thread;


void rng_init()
{
    // int device;
    // struct cudaDeviceProp prop;
    // cudaGetDevice( &device );
    // cudaGetDeviceProperties ( &prop, device );

    // std::cout  << prop.totalGlobalMem / sizeof(float) << std::endl;
    // const int n = prop.totalGlobalMem / 2 / sizeof(float);

    /* Allocate n floats on device */
    cudaMalloc((void **)&devData, RNG_ARRAY_SIZE*sizeof(float));

    /* Create pseudo-random number generator */
    curandCreateGenerator(&gen, CURAND_RNG_PSEUDO_DEFAULT);
    
    /* Set seed */
    curandSetPseudoRandomGeneratorSeed(gen, 1234ULL);

    rng_producer_thread = thread(rng_producer);
}


void rng_finilize()
{
    rng_producer_done = true;
    rng_producer_thread.join();

    /* Cleanup */
    curandDestroyGenerator(gen);
    cudaFree(devData);
}


void rng_producer(void)
{
    float *arr = new float[RNG_ARRAY_SIZE];
    int produced, producer_count;

	while (!rng_producer_done)
	{
        producer_count = 0;

        /* Generate n floats on device */
        curandGenerateNormal(gen, devData, RNG_ARRAY_SIZE, 0.0, 1.0);
        /* Copy device memory to host */
        cudaMemcpy(arr, devData, RNG_ARRAY_SIZE * sizeof(float), cudaMemcpyDeviceToHost);
        
        while (producer_count < RNG_ARRAY_SIZE && !rng_producer_done)
            while ( produced = spsc_queue.push(&arr[producer_count], RNG_ARRAY_SIZE -producer_count) )
                producer_count = producer_count + produced; 
	}
    delete(arr);
}


void randn(float *array, int n)
{
    int consumed, consumer_count;
    consumer_count = 0;
    while (consumer_count < n)
        while ( consumed = spsc_queue.pop(&array[consumer_count], n-consumer_count) )
            consumer_count = consumer_count + consumed;
}


// void consumer(void)
// {
//     int consumed, consumer_count;
//     while (!consumer_done) 
//     {
//         consumer_count = 0;
//         while ( consumed = spsc_queue.pop(&arr_cons[consumer_count], 1000-consumer_count) && consumer_count < 1000)
//     	   consumer_count = consumer_count + consumed;
//     }

// }
