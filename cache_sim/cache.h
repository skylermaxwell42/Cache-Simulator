#include "cache_sim.h"

#ifndef CACHE_H
#define CACHE_H
  typedef struct CacheSetNode {
    int tag;
    struct CacheSetNode* next;
    struct CacheSetNode* prev;
  } CacheSetNode;

  typedef void (*ReplacementFn)(CacheSetNode* cache_set, int hit_index, int num_lines_per_set, int tag);

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
  void init_cache(Cache* rp, int sim_type, int num_sets, int num_lines_per_set);
  void append(CacheSetNode* node, int tag);
  void prepend(CacheSetNode* cache_set, int tag);
  void delete(CacheSetNode* cache_set, int index);
  CacheSetNode* get_node(CacheSetNode* cache_set, int index);
  int find_length(CacheSetNode node);
  void print_cache_set(CacheSetNode cache_set);
  void replace_LRU(CacheSetNode* cache_set, int hit_index, int n_lines, int tag);
  void replace_FIFO(CacheSetNode* cache_set, int hit_index, int n_lines, int tag);
#endif
