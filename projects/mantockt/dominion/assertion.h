#include <stdio.h>
#include <stdlib.h>

int equals(int a, int b);
int greater_than(int, int);
void assert_that(int, char *name, char *description);
int array_copy(int *A, int size_a, int *B, int size_b);
int deep_equals(int *A, int size_a, int *B, int size_b);