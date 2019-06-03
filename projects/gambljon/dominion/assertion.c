#include "assertion.h"

int assert_compare(const void *a, const void *b)
{
  if (*(int *)a > *(int *)b)
    return 1;
  if (*(int *)a < *(int *)b)
    return -1;
  return 0;
}

int equals(int a, int b)
{
  return a == b;
}

int not_equals(int a, int b)
{
  return !equals(a, b);
}

int greater_than(int a, int b)
{
  return a > b;
}

int deep_equals(int *A, int size_a, int *B, int size_b)
{
  if (size_a != size_b)
  {
    return 0;
  }

  qsort((void *)(A), size_a, sizeof(int), assert_compare);
  qsort((void *)(B), size_b, sizeof(int), assert_compare);

  for (int i = 0; i < size_a; i++)
  {
    if (A[i] != B[i])
    {
      return 0;
    }
  }

  return 1;
}

int array_copy(int *A, int size_a, int *B, int size_b)
{
  if (size_b < size_a)
  {
    return -1;
  }

  for (int i = 0; i < size_a; i++)
  {
    B[i] = A[i];
  }

  return 0;
}

int assert_that(int result, char *name, char *description)
{
  if (result == 0)
  {
    printf("%s: FAIL: %s | Expected truthy value, but received false.\n", name, description);
  }
  else if (result == 1)
  {
    printf("%s: PASS: %s\n", name, description);
  }

  return result == 1;
}

int not_in_array(int *A, int size_a, int value)
{
  for (int i = 0; i < size_a; i++)
  {
    if (A[i] == value)
      return 0;
  }
  return 1;
}