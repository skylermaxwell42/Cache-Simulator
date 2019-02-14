#include "filehandle.h"
#include "cache_sim.h"

void parse_trace(char* trace_path, uint8_t data[][NUM_BYTES_PER_REF]) {
  //uint8_t data[NUM_MEM_REFERENCES][NUM_BYTES_PER_REF];

  FILE *file;
  file = fopen(trace_path, "r");
  if (!file) {
    printf("Could not load file from: %s\n", trace_path);
    return;
  }

  int ref_count = 0;
  while (!feof(file) && (ref_count < NUM_MEM_REFERENCES)) {
    // Re-ordering from big to little endian for ease of use
    for (int i=(NUM_BYTES_PER_REF-1); i >= 0; i--) {
      // Loading 1-byte into buffer at a time
      fscanf(file, "%c", &data[ref_count][i]);
    }
    ref_count++;
  }
  fclose(file);
  return;
}
