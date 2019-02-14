#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define NUM_ARGS              3
#define NUM_BYTES_PER_LINES   8
#define NUM_BYTES_PER_REF     3
#define NUM_MEM_REFERENCES    60000
#define NUM_SIM_TYPES         2
#define NUM_SIMS_PER_TYPE     16

#define SIM_TYPE_LRU          0
#define SIM_TYPE_FIFO         1
