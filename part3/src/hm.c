/** @brief Hashmap implementation
 *  Hashmap implementation for the part 3 of the project.
*/
  #include <stdlib.h>
  #include <stdio.h>
  #include "../include/hm.h"
  #include "../include/list.h"
  #include <string.h>
  #define SZ 4096


/**
 * @brief hashing function
 * hashing function to get the bucket index of the key 
 * @param[in]      str1       the key const char* (The string whose hash value is to be calculated)
 * @return         ans        the index of the key in the hashmap
 */
  int helper(const char* str1){
      int size = strlen(str1);
      int ans=0;
      for(int i=0;i<size;i++)
      {
          ans = ans*31 + (str1[i]);
          ans=ans%4096;
      }
      ans=ans%4096;
      return ans;
    }


/**
 * @brief Creates a empty hashmap
 * @param[in]      out_hashmap      struct hashmap_s *const element
 * creating a hashmap with 4096 buckets and initializing the locks and linked lists
 * @return         0        
 */
  int hashmap_create(struct hashmap_s *const out_hashmap){
    for(int i=0;i<SZ;i++){
      out_hashmap->table[i] = list_new();
      out_hashmap->lk[i] = lock_new();
    }
    return 0;
  }


/**
 * @brief puts entry/update entry in hashmap
 * @param[in] hashmap struct hashmap_s *const hashmap (hashmap whose entries are to be updated)
 * @param[in] key  const char* key (key of the entry to be added/increased)
 * @param[in] data void* data (data of the entry to be added/increased)
 * Find searches the key in the corresponding bucket and if found updates the data else creates a new entry
 * @return int 0
 */

  int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data) {
      int value = helper(key);
      struct listentry* e = hashmap->table[value]->head;
      while(e != NULL){
        struct hashmap_element_s* h = (struct hashmap_element_s*) e->data;
        if (strcmp(h->key, key) == 0) {
              h->data = data;
              return 0;
      }
      e = e->next;
      }
      struct hashmap_element_s* h2 = malloc(sizeof(struct hashmap_element_s));
      h2->key = strdup(key);
      h2->data = data;
      list_add(hashmap->table[value], h2);
      return 0;
  
  }

/**
 * @brief obtains the data (no of times a word repeats) from the hashmap
 * @param hashmap struct hashmap_s const* hashmap(hashmap from which the data is to be obtained)
 * @param key const char* key (key of the entry whose data is to be obtained)
 * uses while loopn to iterate through the linked list and returns the data if found else returns NULL
 * @return void* 
 */
  void* hashmap_get(struct hashmap_s const* hashmap, const char* key) {
      int value = helper(key);
      struct listentry* e = hashmap->table[value]->head;
      while(e != NULL){
        struct hashmap_element_s* h = (struct hashmap_element_s*) e->data;
        if (strcmp(h->key, key) == 0) {
              return h->data;
      }
      e = e->next;
      }
      return NULL;
  }

/**
 * @brief iterates through the hashmap and calls the function f on each element
 * @param[in] hashmap struct hashmap_s* const hashmap (hashmap whose entries are to be iterated)
 * @param[in] f int (*f)(struct hashmap_element_s *const (function pointer to the function to be called on each element)
 * We choose f as pointer to Readfile function which is called on each element of the hashmap
 * Iterate through the linked list corresponding to each bucket and call f on each element
 * @return void
 */
  void hashmap_iterator(struct hashmap_s* const hashmap, int (*f)(struct hashmap_element_s *const)){
    for(int i = 0; i < SZ; i++){
      struct list* l = hashmap->table[i];
      struct listentry* current = l->head;
      while(current != NULL){
        f((struct hashmap_element_s*) current->data);
        current = current->next;
      }
    }
  }



/**
 * @brief acquires the lock of the bucket corresponding to the key
 * Calls lock_acquire on the lock corresponding to the bucket
 * @param[in] hashmap struct hashmap_s *const hashmap (hashmap whose lock is to be acquired)
 * @param[in] key const char* key (key of the entry whose lock is to be acquired)
 * @return * int 
 */
  int acquire_bucket(struct hashmap_s *const hashmap, const char* key){
      int value = helper(key);
      lock_acquire(hashmap->lk[value]);
  }

/**
 * @brief releases the lock of the bucket corresponding to the key
 * Calls lock_release on the lock corresponding to the bucket
 * @param hashmap[in] struct hashmap_s *const hashmap (hashmap whose lock is to be released)
 * @param key[in] const char* key (key of the entry whose lock is to be released)
 * @return * int
 */

  int release_bucket(struct hashmap_s *const hashmap, const char* key){
      int value = helper(key);
      lock_release(hashmap->lk[value]);
  }