#ifndef mathtool_h
#define mathtool_h

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "data_structure.h"

double information_entropy_by_counter(ClassCounter *counter);
double information_entropy(unsigned long *array, size_t size);
double info_entropy_discrete_prop(unsigned long *Y_arr, unsigned long *prop_arr, size_t size);
unsigned int *random_array_int(unsigned int min, unsigned int max, size_t size, unsigned int seed);


#endif	/* mathtool_h */
