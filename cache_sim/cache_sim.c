#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "filehandle.h"
#include "cache_sim.h"

int main(int argc, char* argv[]) {

  if ((argc != (NUM_ARGS+1)) || !(argc))  {
    printf( "Usage:\n \
            ./cach_sim $PATH_TO_TRACE #K #N\n \
            Where #K is the number of lines per set and\n \
            #N is the number of sets in the caching scheme\n\n \
            Example Usage:\n \
            ./cache_sim ../data/trace1.dat 16 2\n");
    return -1;
  }

  char trace_path[100] = "";
  sscanf(argv[1], "%s", trace_path);

  uint8_t data[NUM_MEM_REFERENCES][NUM_BYTES_PER_REF];
  parse_trace(trace_path, data);
  printf("Loaded [%lu bytes] into memory\n", sizeof(data));
  printf("First Memory Ref:\n0x%02x%02x%02x\n", data[0][0], data[0][1], data[0][2]);
  return 0;
}
