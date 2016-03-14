#include <iostream>

#include "rnd_generator.h"

using namespace std;


#define CONSUMER_SIZE 500000

float *arr_cons = new float[CONSUMER_SIZE];


int main(int argc, char* argv[])
{
    rng_init();

    randn(arr_cons, CONSUMER_SIZE/2);
    randn(&arr_cons[CONSUMER_SIZE/2], CONSUMER_SIZE/2);

    rng_finilize();


	printf("\n");
    for ( int i = 0; i < 1000; i++ ) 
    {
        printf("%1.4f ", arr_cons[i]);
    }
    printf("\n");

}