// Data structures
#ifndef DS_H
#define DS_H

#include "ds_types.h"

// arrays
array_t* arr_new();
void     arr_push(array_t* arr, void* item);
void*    arr_pop(array_t* arr);
void*    arr_get(array_t* arr, int index);
void     arr_set(array_t* arr, int index, void* item);
void     arr_insert(array_t* arr, int index, void* item);
void     arr_remove(array_t* arr, int index);
int      arr_len(array_t* arr);
void     arr_free(array_t* arr);
// linkedlists
llist_t* ll_new();
void     ll_push(llist_t* ll, void* item);
void     ll_prepend(llist_t* ll, void* item);
void*    ll_pop(llist_t* ll);
void*    ll_shift(llist_t* ll);
void*    ll_get(llist_t* ll, int index);
void     ll_insert(llist_t* ll, int index, void* item);
void     ll_remove(llist_t* ll, int index);
int      ll_len(llist_t* ll);
void     ll_free(llist_t* ll);
// hashmaps
map_t*   map_new();
void     map_set(map_t* map, char* key, void* value);
void*    map_get(map_t* map, char* key);
void     map_del(map_t* map, char* key);
int      map_has(map_t* map, char* key);
char**   map_keys(map_t* map);
int      map_len(map_t* map);
void     map_free(map_t* map);
// hashset
set_t*   set_new();
void     set_add(set_t* set, char* item);
void     set_remove(set_t* set, char* item);
int      set_has(set_t* set, char* item);
char**   set_items(set_t* set);
int      set_len(set_t* set);
void     set_free(set_t* set);
// stack
stk_t*   stk_new();
void     stk_push(stk_t* stk, void* item);
void*    stk_pop(stk_t* stk);
void*    stk_peek(stk_t* stk);
int      stk_len(stk_t* stk);
void     stk_free(stk_t* stk);
// queue
q_t*     q_new();
void     q_enqueue(q_t* q, void* item);
void*    q_dequeue(q_t* q);
void*    q_peek(q_t* q);
int      q_len(q_t* q);
void     q_free(q_t* q);
// tensors
tensor_t tensor_new(int* shape, int ndim);
float tensor_get(tensor_t* t, int* indices);
void tensor_set(tensor_t* t, int* indices, float value);
void tensor_free(tensor_t* t);

#endif
