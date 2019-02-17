#include "cache.h"

int access(Cache* cache, int addr) {
  int idx_bits = log2(cache->num_sets);
  int tag = (addr & cache->tag_mask) >> (int) (idx_bits + log2(NUM_BYTES_PER_LINES));
  int idx = (addr & cache->idx_mask) >> (int) log2(NUM_BYTES_PER_LINES);
  printf("Addr: %06x Tag: %04x Idx: %04x IDX: %d\n", addr, tag, idx, idx);

  // Search for tag in cache set
  CacheSetNode* cache_set = &cache->cache_sets[idx];

  //printf("MEM LOC of CACHESET: %d\n", cache_set);

  if (find_length(*cache_set) == 0) {
    printf("Initializing Cache Set: %d with tag: %d\n", idx, tag);
    append(cache_set, tag);
  } else {
    int hit_index = find_index(cache_set, tag);
    if (hit_index < 0) {
      // Replace
      append(cache_set, tag);
      printf("Adding tag: %d to cache set: %d, now len: %d\n", tag, idx, find_length(*cache_set));
      print_cache_set(*cache_set);
    } else {
      printf("Got a hit\n");
      print_cache_set(*cache_set);
    }
  }
  //CacheSetNode cache_set = cache->cache_sets[idx]; // Work this as linked list
  //printf("TEST1: %04d\n", cache->cache_sets);
  return 0;
}

int find_index(CacheSetNode* node, int tag) {
  int count = 0;
  if ((node->tag == -1) && (node->next == NULL)) {return -1;}
  CacheSetNode* cur_node = node;
  while (cur_node != NULL) {
    // DEBUG BEGIN
    //printf("CurNodeTag: %d  Tag %d\n", cur_node->tag, tag);
    // DEBUG END
    if (cur_node->tag == -1) {
      cur_node = cur_node->next;
      continue;
    } else if (cur_node->tag == tag) {
      return count;
    } else {
      cur_node = cur_node->next;
      count++;
    }
  }
  return -1;
}

void replace_LRU(CacheSetNode* cache_set) {
  return;
}

void repalce_FIFO(CacheSetNode* cache_set) {
  return;
}

void append(CacheSetNode* node, int tag) {
  CacheSetNode* cur_node = node;
  while (cur_node->next != NULL) {
    //printf("TAG: %d\n", cur_node->tag);
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

void init_cache(Cache* cache, int sim_type, int num_sets, int num_lines_per_set) {
  int idx_bits = log2(num_sets);
  int tag_bits = NUM_BITS_PER_ADDR - log2(NUM_BYTES_PER_LINES) - idx_bits;

  cache->sim_type = sim_type;
  cache->tag_mask = (0xFFFFFF << (NUM_BITS_PER_ADDR - tag_bits)) & 0xFFFFF8;
  cache->idx_mask = (0xFFFFFF << (NUM_BITS_PER_ADDR - idx_bits - tag_bits)) & ~cache->tag_mask & 0xFFFFF8;
  cache->num_sets = num_sets;
  cache->num_lines_per_set = num_lines_per_set;
  cache->cache_sets = malloc(sizeof(CacheSetNode) * num_sets);
  if (cache->cache_sets == NULL) {
    printf("Error: Couldn't allocate memory during Cache initialization");
    exit(0);
  }
  for (int i = 0; i < num_sets; i++) {
    init_cache_set(&cache->cache_sets[i], -1);
  }
  // DEBUG BEGIN
  //append(&cache->cache_sets[0], 15);
  //append(&cache->cache_sets[0], 72);
  //append(&cache->cache_sets[0], 42);
  //append(&cache->cache_sets[0], 100);
  //append(&cache->cache_sets[0], 101);
  //append(&cache->cache_sets[0], 102);
  //append(&cache->cache_sets[0], 103);
  //print_cache_set(cache->cache_sets[0]);

  //printf("NUMSETS: %04d  LEN: %d  IDX: %d\n", 100, find_length(cache->cache_sets[0]), find_index(&cache->cache_sets[0], 103));
  // DEBUG END
  // DEBUG START
  //printf("tag_bits %06x\n", cache->tag_mask);
  //printf("idx_bits %06x\n", cache->idx_mask);
  //printf("Num Sets: %d\n", num_sets);
  // DEBUG END
  return;
}

void init_cache_set(CacheSetNode* node, int tag) {
  node->prev = NULL;
  node->next = NULL;
  node->tag = tag;
  //printf("TAGFORREALfjdshfjkds: %d\n", node->tag);
  return;
}
