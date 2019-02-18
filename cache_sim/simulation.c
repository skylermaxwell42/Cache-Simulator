#include "cache_sim.h"
#include "simulation.h"
#include "cache.h"

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

        init_simulation(&sims[i], k, n, sim_types[sim_idx]);

        // DEBUG START
        //printf("Sim Type: %d k: %02d n: %03d I: %02d\n", sims[i].cache.sim_type, sims[i].k, sims[i].n, i);
        // DEBUG END
        i++;
      }
    }
  }
  return;
}

void run_simulation(Simulation sim, SimulationResult* sim_result, uint8_t data[][NUM_BYTES_PER_REF]) {
  sim_result->num_misses = 0;
  sim_result->num_refernces = 0;
  for (int data_idx = 0; data_idx < NUM_MEM_REFS; data_idx++) {
    int addr = 0;
    for (int i = 0; i < NUM_BYTES_PER_REF; i++) {
      addr |= (data[data_idx][i]<<(8*i));
    }
    if (!access(&sim.cache, addr)) {
        sim_result->num_misses++;
    }
    sim_result->num_refernces++;
  }
}

void init_simulation(Simulation* sim, int k, int n, int sim_type) {
  sim->l = NUM_BYTES_PER_LINES;
  sim->k = k;
  sim->n = n;
  init_cache(&sim->cache, sim_type, n, k);
  sim->cache_size_bytes = NUM_BYTES_PER_LINES * k * n;
}
