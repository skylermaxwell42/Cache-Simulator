#include "cache_sim.h"

#ifndef CACHE_H
#define CACHE_H
  typedef struct CacheSetNode {
    int tag;
    struct CacheSetNode* next;
    struct CacheSetNode* prev;
  } CacheSetNode;

  typedef void (*ReplacementFn)(CacheSetNode*, int, int);

  typedef struct {
    int sim_type;           // Simulation type mapped to LRU or FIFO replacement policies
    int tag_mask;
    int idx_mask;
    int num_sets;
    int num_lines_per_set;
    ReplacementFn rp_fn;
    CacheSetNode* cache_sets;
  } Cache;

  int access(Cache* cache, int addr);
  int find_index(CacheSetNode* cache_set, int length);
  void replace_LRU(CacheSetNode* cache_set);
  void replace_FIFO(CacheSetNode* cache_set);
  void init_cache(Cache* rp, int sim_type, int num_sets, int num_lines_per_set);
  void init_cache_set(CacheSetNode* cache_set, int tag);
  void append(CacheSetNode* node, int tag);
  int find_length(CacheSetNode node);
  void print_cache_set(CacheSetNode cache_set);


#endif
