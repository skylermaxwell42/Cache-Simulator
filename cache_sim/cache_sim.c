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

  // Allocating space for memory trace data
  uint8_t data[NUM_MEM_REFS][NUM_BYTES_PER_REF];
  // Parsing memory trace file into data[][] as uint8_t bytes
  parse_trace(trace_path, data);

  // Logging stats to console
  printf("Loaded [%lu bytes] into memory\n", sizeof(data));
  printf("First Memory Ref: 0x%02x%02x%02x\n", data[0][2], data[0][1], data[0][0]);

  SimulationResult sim_results[NUM_SIMS_PER_TYPE*NUM_SIM_TYPES];
  for (int sim_idx = 0; sim_idx < NUM_SIMS_PER_TYPE*NUM_SIM_TYPES; sim_idx++) {
    Simulation sim = sims[sim_idx];
    printf("---------------------------------------------------\n");
    printf("Running Simulation #%02d:\n", sim_idx+1);
    printf("Simulation Type: %s\n", (sim.sim_type==SIM_TYPE_LRU)?"LRU":"FIFO");
    printf("Cache Size: %d bytes\nKN: %03d  K: %03d  N%03d\n\n", sim.cache_size_bytes, sim.n*sim.k, sim.k, sim.n);
    clock_t toc = clock();
    run_simulation(sim, &sim_results[sim_idx], data);
    clock_t tic = clock();
    double miss_rate = (double) sim_results[sim_idx].num_misses/sim_results[sim_idx].num_refernces;
    double run_time = (double) (((tic - toc)*1000) / CLOCKS_PER_SEC);
    printf("Simulation Results:\nMiss Rate:    %f\nRun Time:    %02.2f ms\n", miss_rate, run_time);
  }

  return 0;
}
