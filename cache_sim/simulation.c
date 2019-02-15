#include "cache_sim.h"
#include "simulation.h"

#define NUM_K_OPTS    4
#define NUM_KN_OPTS   2
#define NUM_SIM_TYPES 2

void configure_simulations(Simulation sims[]) {

  const int sim_types[NUM_SIM_TYPES] = {SIM_TYPE_LRU, SIM_TYPE_FIFO};
  const int k_opts[NUM_K_OPTS] = {2, 4, 8, 16};
  const int kn_opts[NUM_KN_OPTS] = {64, 256};
  int i = 0;
  for (int sim_idx = 0; sim_idx < NUM_SIM_TYPES; sim_idx++) {
    for (int kn_idx = 0; kn_idx < NUM_KN_OPTS; kn_idx++) {
      for (int k_idx = 0; k_idx < NUM_K_OPTS; k_idx++) {
        int k = k_opts[k_idx];
        int kn = kn_opts[kn_idx];
        int n = kn / k;
        // DEBUG START
        //printf("Sim Type: %d k: %d kn: %d I: %d\n", sim_types[sim_idx], k, kn, i);
        // DEBUG END

        init_simulation(&sims[i], k, n, sim_types[sim_idx]);

        // DEBUG START
        //printf("Sim Type: %d k: %d kn: %d I: %d\n", sims[i].sim_type, sims[i].k, sims[i].n*sims[i].k, i);
        // DEBUG END
        i++;
      }
    }
  }
  return;
}

void run_simulation(Simulation sim, SimulationResult* sim_result) {
  sim_result->num_misses = 0;
  sim_result->num_refernces = 0;
}

void init_simulation(Simulation* sim, int k, int n, int sim_type) {
  sim->l = NUM_BYTES_PER_LINES;
  sim->k = k;
  sim->n = n;
  sim->sim_type = sim_type;
  sim->cache_size_bytes = NUM_BYTES_PER_LINES * k * n;
}
