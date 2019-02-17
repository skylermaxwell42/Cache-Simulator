#include "filehandle.h"
#include "simulation.h"
#include "cache_sim.h"

int main(int argc, char* argv[]) {

  // Handling incorroect user arguments
  if ((argc != (NUM_ARGS+1)) || !(argc))  {
    printf( "Usage:\n \
            ./cach_sim $PATH_TO_TRACE\n\n \
            Example Usage:\n \
            ./cache_sim ../data/TRACE1.dat\n");
    return -1;
  }

  // Parsing user arguments
  char trace_path[100] = "";
  sscanf(argv[1], "%s", trace_path);

  // Configuring simulation settings, each simulation has the following parameters,
  //  - l:          (int) Number of lines in caching scheme
  //  - k:          (int) Number of
  //  - n:          (int) Number of
  //  - num_misses  (int) Number of misses during simulation
  //  - sim_type    (int) Mapped integer to simualtion type (LRU or FIFO) replacement policies
  Simulation sims[NUM_SIMS_PER_TYPE*NUM_SIM_TYPES];
  configure_simulations(sims);
  
  // DEBUG BEGIN
  /**
  for (int i=0;i<16;i++) {
    Simulation s = sims[i];
    printf("SIM: %d - K: %02d - KN:%03d - Cache Size: %04d bytes\n",s.sim_type, s.k, s.k*s.n, s.cache_size_bytes);
  }
  **/
  // DEBUG END

  // Allocating space for memory trace data
  uint8_t data[NUM_MEM_REFS][NUM_BYTES_PER_REF];
  // Parsing memory trace file into data[][] as uint8_t bytes
  parse_trace(trace_path, data);

  // Logging stats to console
  printf("Loaded [%lu bytes] into memory\n", sizeof(data));
  printf("First Memory Ref: 0x%02x%02x%02x\n", data[0][2], data[0][1], data[0][0]);

  SimulationResult sim_results[NUM_SIMS_PER_TYPE*NUM_SIM_TYPES];
  for (int sim_idx = 0; sim_idx < NUM_SIMS_PER_TYPE*NUM_SIM_TYPES; sim_idx++) {
    run_simulation(sims[sim_idx], &sim_results[sim_idx], data);
  }
  // DEBUG START
  /**
  for (int i=0; i<0; i++) {
    printf("0x%02x%02x%02x\n", data[i][0], data[i][1], data[i][2]);
  }
  **/
  // DEBUG END

  return 0;
}
