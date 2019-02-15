#include "cache_sim.h"

// Simulation Configuration typedef
typedef struct {
  int l;                  // Number of bytes per line of cache memory
  int k;                  // Number of lines per set
  int n;                  // Number of sets
  int sim_type;           // Simulation type mapped to LRU or FIFO replacement policies
  int cache_size_bytes;
} Simulation;

// Simulation Result typedef
typedef struct {
  int num_misses;         // Number of misses per simulation
  int num_refernces;
} SimulationResult;

// Function prototypes
void configure_simulations(Simulation sims[]);
void init_simulation(Simulation* sim, int k, int n, int sim_type);
void run_simulation(Simulation sim, SimulationResult* sim_result);
