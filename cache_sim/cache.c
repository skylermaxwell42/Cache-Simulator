/** Cache Simulator [cache.c] **/
#include "cache.h"
#include "simulation.h"

int access(Cache* cache, int addr) {
  int idx_bits = log2(cache->num_sets);
  int tag = (addr & cache->tag_mask) >> (int) (idx_bits + log2(NUM_BYTES_PER_LINES));
  int idx = (addr & cache->idx_mask) >> (int) log2(NUM_BYTES_PER_LINES);

  // Search for tag in cache set
  CacheSetNode* cache_set = &cache->cache_sets[idx];
  int hit_index = find_index(cache_set, tag);
  cache->rp_fn(cache_set, hit_index, cache->num_lines_per_set, tag);
  return (hit_index != -1) ? 1 : 0;
}

int find_index(CacheSetNode* node, int tag) {
  int count = 0;
  if ((node->tag == -1) && (node->next == NULL)) {return -1;}
  CacheSetNode* cur_node = node;
  while (cur_node != NULL) {
    if (cur_node->tag == -1) {
      cur_node = cur_node->next;
      continue;
    }
    else if (cur_node->tag == tag) {
      return count;
    }
    else {
      cur_node = cur_node->next;
      count++;
    }
  }
  return -1;
}

void append(CacheSetNode* node, int tag) {
  CacheSetNode* cur_node = node;
  while (cur_node->next != NULL) {
    cur_node = cur_node->next;
  }
  cur_node->next = malloc(sizeof(CacheSetNode));
  if (cur_node->next == NULL) {
    printf("Could not allocate space when appending . . .\n");
    exit(0);
  }
  cur_node->next->tag = tag;
  cur_node->next->prev = cur_node;
  cur_node->next->next = NULL;
  return;
}

void prepend(CacheSetNode* cache_set, int tag) {
  CacheSetNode* new_node = malloc(sizeof(CacheSetNode));
  new_node->tag = tag;
  new_node->prev = cache_set;
  new_node->next = cache_set->next;
  cache_set->next = new_node;
}

void delete(CacheSetNode* cache_set, int index) {
  CacheSetNode* node = get_node(cache_set, index);
  if (node->next == NULL) {
    node->prev->next = NULL;
  }
  else {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }
  free(node);
}

CacheSetNode* get_node(CacheSetNode* cache_set, int index) {
  CacheSetNode* cur_node = cache_set->next;
  int count = 0;
  while (cur_node->next != NULL) {
    if (count == index) {
      return cur_node;
    }
    cur_node = cur_node->next;
    count++;
  }
  return cur_node;
}

int find_length(CacheSetNode node) {
  int count = 0;
  CacheSetNode cur_node = node;
  while (cur_node.next != NULL) {
    cur_node = *cur_node.next;
    count++;
  }
  return count;
}

void print_cache_set(CacheSetNode cache_set) {
  CacheSetNode cur_node = cache_set;
  printf("CacheSet:    ");
  while (cur_node.next != NULL) {
    printf("%d -> ", cur_node.tag);
    cur_node = *cur_node.next;
  }
  printf("%d\n", cur_node.tag);
  return;
}

void replace_LRU(CacheSetNode* cache_set, int hit_index, int n_lines, int tag) {
  int set_size = find_length(*cache_set);
  if (hit_index != -1) {
    delete(cache_set, hit_index);
    append(cache_set, tag);
  }
  else {
    if (set_size <= n_lines) {
      prepend(cache_set, tag);
    }
    else {
      delete(cache_set, 1);
      append(cache_set, tag);
    }
  }
}

void replace_FIFO(CacheSetNode* cache_set, int hit_index, int n_lines, int tag) {
  int set_size = find_length(*cache_set);
  if (set_size <= n_lines) {
    prepend(cache_set, tag);
  }
  else {
    delete(cache_set, 1);
    append(cache_set, tag);
  }
}

void init_cache(Cache* cache, int sim_type, int num_sets, int num_lines_per_set) {
  int idx_bits = log2(num_sets);
  int tag_bits = NUM_BITS_PER_ADDR - log2(NUM_BYTES_PER_LINES) - idx_bits;

  cache->sim_type = sim_type;
  cache->tag_mask = (0xFFFFFF << (NUM_BITS_PER_ADDR - tag_bits)) & 0xFFFFF8;
  cache->idx_mask = (0xFFFFFF << (NUM_BITS_PER_ADDR - idx_bits - tag_bits)) & ~cache->tag_mask & 0xFFFFF8;
  cache->num_sets = num_sets;
  cache->num_lines_per_set = num_lines_per_set;
  cache->rp_fn = (sim_type==SIM_TYPE_LRU)   ?   replace_LRU :
                 (sim_type==SIM_TYPE_FIFO)  ?   replace_FIFO : NULL;
  cache->cache_sets = malloc(sizeof(CacheSetNode) * num_sets);
  if (cache->cache_sets == NULL) {
    printf("Error: Couldn't allocate memory during Cache initialization");
    exit(0);
  }
  else if (cache->rp_fn == NULL){
    printf("Error: Couldn't find replacement policy for sim type\n");
    exit(0);
  }
  for (int i = 0; i < num_sets; i++) {
    cache->cache_sets[i].prev = NULL;
    cache->cache_sets[i].next = NULL;
    cache->cache_sets[i].tag = -1;
  }
  // DEBUG BEGIN
  //append(&cache->cache_sets[0], 15);
  //append(&cache->cache_sets[0], 72);
  //append(&cache->cache_sets[0], 42);
  //append(&cache->cache_sets[0], 100);
  //append(&cache->cache_sets[0], 101);
  //append(&cache->cache_sets[0], 102);
  //append(&cache->cache_sets[0], 103);
  //prepend(&cache->cache_sets[0], 199);
  //delete(&cache->cache_sets[0], 6);
  //print_cache_set(cache->cache_sets[0]);
  //replace_FIFO(&cache->cache_sets[0], 4, num_lines_per_set, 101);
  //print_cache_set(cache->cache_sets[0]);

  //printf("NUMSETS: %04d  LEN: %d  IDX: %d\n", 100, find_length(cache->cache_sets[0]), find_index(&cache->cache_sets[0], 103));

  //printf("tag_bits %06x\n", cache->tag_mask);
  //printf("idx_bits %06x\n", cache->idx_mask);
  //printf("Num Sets: %d\n", num_sets);
  // DEBUG END
  return;
}
