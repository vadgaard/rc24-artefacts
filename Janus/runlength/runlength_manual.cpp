#include <stdio.h>      /* printf */
#include <stdlib.h>     /* atoi */
#include <time.h>       /* time */

void encode(unsigned int* text, unsigned int* arc) {
  int i = 0, j = 0;
  while (text[i] != 0) {
    arc[j] = text[i];
    arc[j + 1]++;
    i++;
    while (arc[j] == text[i]) {
      arc[j + 1]++;
      i++;
    }
    j += 2;
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("An unsigned integer should be provided.\n");
    return 1;
  }

  unsigned int n, *text, *arc;

  n = (unsigned int) atoi(argv[1]);

  text = (unsigned int*) calloc(  n, sizeof(unsigned int));
  arc  = (unsigned int*) calloc(2*n, sizeof(unsigned int));

  srand(time(NULL));

  // initialize text
  for (int i = 0; i < n-1; i++) {
    text[i] = rand() % 5 + 1;
  }

  // encode
  encode(text, arc);

  free(text); free(arc);

  return 1;
}

