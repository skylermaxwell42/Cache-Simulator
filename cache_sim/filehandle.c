/** Cache Simulator [filehandle.c] **/
#include "filehandle.h"
#include "cache_sim.h"

void parse_trace(char* trace_path, uint8_t data[][NUM_BYTES_PER_REF]) {
  FILE *file;
  file = fopen(trace_path, "r");
  if (!file) {
    printf("Could not load file from: %s\n", trace_path);
    printf("Use './cache_sim' for usage . . .\n");
    exit(0);
  }

  int ref_count = 0;
  while (!feof(file) && (ref_count < NUM_MEM_REFS)) {
    for (int i = 0; i < NUM_BYTES_PER_REF; i++) {
      // Loading 1-byte into buffer at a time
      fscanf(file, "%c", &data[ref_count][i]);
    }
    ref_count++;
  }
  fclose(file);
  return;
}
