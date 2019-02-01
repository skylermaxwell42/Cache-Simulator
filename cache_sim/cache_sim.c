#include <stdio.h>

#define NUM_ARGS 1

int main(int argc, char* argv[]) {

  int a;
  if (1) { // Usage check here
    printf( "Usage:\n \
            ./cach_sim $PATH_TO_TRACE #K #N\n \
            Where #K is the number of lines per set and\n \
            #N is the number of sets in the caching scheme\n\n \
            Example Usage:\n \
            ./cache_sim ../data/trace1.dat 16 2\n");
  }

  if (argc != (NUM_ARGS+1)) {
    printf("Incorrect argument formatting, %d args given ... exiting\n", argc);
    return -1;
  }

  sscanf(argv[1], "%d", &a);
  printf("%d\n", a);

  return 0;
}
