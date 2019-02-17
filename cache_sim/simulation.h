#include "cache_sim.h"
#include "cache.h"

#ifndef SIMULATION_H
#define SIMULATION_H

  // Simulation Configuration typedef
  typedef struct {
    int l;                  // Number of bytes per line of cache memory
    int k;                  // Number of lines per set
    int n;                  // Number of sets
    int cache_size_bytes;
    int idx_mask;
    int tag_mask;
    Cache cache;
  } Simulation;

  // Simulation Result typedef
  typedef struct {
    int sim_type;
    int num_misses;         // Number of misses per simulation
    int num_refernces;
  } SimulationResult;

  // Function prototypes
  void configure_simulations(Simulation sims[]);
  void init_simulation(Simulation* sim, int k, int n, int sim_type);
  void run_simulation(Simulation sim, SimulationResult* sim_result, uint8_t data[][NUM_BYTES_PER_REF]);

#endif
