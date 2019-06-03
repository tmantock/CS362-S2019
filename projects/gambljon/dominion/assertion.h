#include <stdio.h>
#include <stdlib.h>

#ifndef PRINT_TESTS
#define PRINT_TESTS 1
#endif

int equals(int a, int b);
int not_equals(int a, int b);
int greater_than(int, int);
int assert_that(int, char *name, char *description);
int array_copy(int *A, int size_a, int *B, int size_b);
int deep_equals(int *A, int size_a, int *B, int size_b);
int not_in_array(int *A, int size_a, int value);