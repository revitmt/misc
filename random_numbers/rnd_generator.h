#ifndef RND_GENERATOR_H
#define RND_GENERATOR_H


extern "C"  // make visible to Fortran
{
	void rng_init(void);
	void rng_finilize(void);
	void rng_producer(void);
	void randn(float *array, int n);
}

#endif
