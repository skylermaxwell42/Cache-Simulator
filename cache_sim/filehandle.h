/** Cache Simulator [filehandle.h] **/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "cache_sim.h"

#ifndef FILEHANDLE_H
#define FILEHANDLE_H
  void parse_trace(char* trace_path, uint8_t data[][NUM_BYTES_PER_REF]);
#endif
