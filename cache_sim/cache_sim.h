#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define NUM_ARGS              1
#define NUM_BITS_PER_ADDR     24
#define NUM_BYTES_PER_LINES   8
#define NUM_BYTES_PER_REF     3
#define NUM_MEM_REFS          60000
#define NUM_SIM_TYPES         2
#define NUM_SIMS_PER_TYPE     8

#define SIM_TYPE_LRU          0
#define SIM_TYPE_FIFO         1

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
