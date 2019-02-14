#include "cache_sim.h"
#include "simulation.h"

void configure_simulations(Simulation sims[]) {


  for (int i = 0; i < NUM_SIMS_PER_TYPE*NUM_SIM_TYPES; i++) {
    int k = 8;
    int n = 8;
    int sim_type = (i%(NUM_SIMS_PER_TYPE/NUM_SIM_TYPES)==0) ? SIM_TYPE_LRU : SIM_TYPE_FIFO;

    init_simulation(&sims[i], k, n, sim_type);

    // DEBUG START
    //printf("SIM: %d\n", sims[i].sim_type);
    // DEBUG END
  }
  return;
}

void init_simulation(Simulation* sim, int k, int n, int sim_type) {
  sim->l = NUM_BYTES_PER_LINES;
  sim->k = k;
  sim->n = n;
  sim->num_misses = 0;
  sim->sim_type = sim_type;
  sim->cache_size_bytes = NUM_BYTES_PER_LINES * k * n;
}
