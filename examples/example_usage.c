#include <stdio.h>
#include "cvector.h"

int main(void) {
  printf("Hello, World!\n");

  int *v = VECTOR(int, 0);

  if (vector_push_back(v, (int []){1}, 1) == VECTOR_FAILURE) {
    printf("Failed to push back element\n");
    return 1;
  }

  printf("Size: %zu\n", vector_size(v));

  printf("First element: %d\n", *vector_front(v));
  printf("Last element: %d\n", *vector_back(v));

  return 0;
}
