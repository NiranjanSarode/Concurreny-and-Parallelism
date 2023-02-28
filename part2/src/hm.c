  #include <stdlib.h>
  #include <stdio.h>
  #include "../include/hm.h"
  #include "../include/list.h"
  #include <string.h>
  #define SZ 4096

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

  int hashmap_create(struct hashmap_s *const out_hashmap){
    for(int i=0;i<SZ;i++){
      out_hashmap->table[i] = list_new();
      out_hashmap->lk[i] = lock_new();
    }
    return 0;
  }

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



                          
  int acquire_bucket(struct hashmap_s *const hashmap, const char* key){
      int value = helper(key);
      lock_acquire(hashmap->lk[value]);
  }

  int release_bucket(struct hashmap_s *const hashmap, const char* key){
      int value = helper(key);
      lock_release(hashmap->lk[value]);
  }