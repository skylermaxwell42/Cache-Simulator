#include "cache_sim.h"

// Simulation Configuration typedef
typedef struct {
  int l;                  // Number of bytes per line of cache memory
  int k;                  // Number of lines per set
  int n;                  // Number of sets
  int num_misses;         // Number of misses per simulation
  int sim_type;           // Simulation type mapped to LRU or FIFO replacement policies
  int cache_size_bytes;
} Simulation;

// Function prototypes
void configure_simulations(Simulation sims[]);
void init_simulation(Simulation* sim, int k, int n, int sim_type);
