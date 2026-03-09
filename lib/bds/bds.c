// Basic data structures

#include <stdlib.h>
#include <string.h>
#include "bds.h"

// arrays
array_t* new_array(void){
    array_t* arr = malloc(sizeof(array_t));
    arr->items = malloc(sizeof(void*) * 8);
    arr->size = 0;
    arr->capacity = 8;
    return arr;
}

void arr_push(array_t* arr, void* item){
    if (arr == NULL || item == NULL) return;
    if (arr->size == arr->capacity){
        arr->capacity *= 2;
        arr->items = realloc(arr->items, sizeof(void*) * arr->capacity);
    }
    arr->items[arr->size++] = item;
}

void* arr_pop(array_t* arr){
    if (arr == NULL || arr->size == 0) return NULL;
    
    void* item = arr->items[--arr->size];

    if (arr-> size < arr->capacity /4 && arr->capacity > 8){
        arr->capacity /= 2;
        arr->items = realloc(arr->items, sizeof(void*) * arr->capacity);
    }
    return item; 
}

void* arr_get(array_t* arr, int index){
    if (arr == NULL) return NULL;
    if (index < 0 || index >= arr->size) return NULL;
    return arr->items[index];
}

void arr_set(array_t* arr, int index, void* item){
    if (arr == NULL || item == NULL) return;
    if (index < 0 || index >= arr->size) return;
    arr->items[index] = item;
}

void arr_insert(array_t* arr, int index, void* item){
    if (arr == NULL || item == NULL) return;
    if (index < 0 || index > arr->size) return;
    if (arr->size == arr->capacity){
        arr->capacity *= 2;
        arr->items = realloc(arr->items, sizeof(void*) * arr->capacity);
    }
    memmove(&arr->items[index + 1], &arr->items[index], sizeof(void*) * (arr->size - index));
    arr->items[index] = item;
    arr->size++;
}

void arr_remove(array_t* arr, int index){
    if (arr == NULL) return;
    if (index < 0 || index >= arr->size) return;
    memmove(&arr->items[index], &arr->items[index + 1], sizeof(void*) * (arr->size - index - 1));
    arr->size--;

    if (arr-> size < arr->capacity / 4 && arr->capacity > 8){
        arr->capacity /= 2;
        arr->items = realloc(arr->items, sizeof(void*) * arr->capacity);
    }
}

int arr_len(array_t* arr){
    if (arr == NULL) return -1;
    return arr->size;
}

void arr_free(array_t* arr){
    free(arr->items);
    free(arr);
}

// linkedlists
llist_t* ll_new(void){
    llist_t* ll = malloc(sizeof(llist_t));
    if (ll == NULL) return NULL;
    ll->head = NULL;
    ll->tail = NULL;
    ll->size = 0;
    return ll;
}

void ll_push(llist_t* ll, void* item){ // pushes c to  [a], [b] => [a], [b], [c]
    if (ll == NULL || item == NULL) return;

    llist_node_t* node = malloc(sizeof(llist_node_t));
    if (node == NULL) return;
    node->value = item;
    node->next = NULL;
    node->prev = ll->tail;
    if (ll->tail == NULL){
        ll->head = node;
        ll->tail = node;
    } else{
        ll->tail->next = node;
        ll->tail = node;
    }
    ll->size++;
}

void ll_prepend(llist_t* ll, void* item){ // unshift a to [b], [c] => [a], [b], [c]
    if (ll == NULL || item == NULL) return;

    llist_node_t* node = malloc(sizeof(llist_node_t));
    if (node == NULL) return;
    node->value = item;
    node->next = ll->head;
    node->prev = NULL;
    if (ll->head != NULL) 
        ll->head->prev = node;
    ll->head = node;
    if (ll->tail == NULL) 
        ll->tail = node;
    ll->size++;
}

void* ll_pop(llist_t* ll){ // unpushes [a], [b], [c] => [a], [b] returns c
    if (ll == NULL) return NULL;
    if (ll->size == 0) return NULL;
    llist_node_t* node = ll->tail;
    void* item = node->value;
    ll->tail = node->prev;
    if (ll->tail == NULL){
        ll->head = NULL;
    } else {
        ll->tail->next = NULL;
    }
    ll->size--;
    free(node);
    return item;
}

void* ll_shift(llist_t* ll){ // shifts [a], [b], [c] => [b], [c] returns a
    if (ll == NULL) return NULL;
    if (ll->size == 0) return NULL;
    llist_node_t* node = ll->head;
    void* item = node->value;
    ll->head = node->next;
    if (ll->head == NULL){
        ll->tail = NULL;
    } else {
        ll->head->prev = NULL;
    }
    ll->size--;
    free(node);
    return item;
}

void* ll_get(llist_t* ll, int index){
    if (ll == NULL) return NULL;
    if (index < 0 || index >= ll->size) return NULL;
    llist_node_t* curr;
    if (index < ll->size /2){ // if index > ll->size start from tail and count down. 
        curr = ll->head;
        for (int i = 0; i < index; i++)
            curr = curr->next;
    } else {
        curr = ll->tail;
        for (int i = ll->size - 1; i > index; i--) 
            curr = curr->prev; // ll-size - 1 to match index and size;
    }
    return curr->value;
}

void ll_insert(llist_t* ll, int index, void* item){
    if (ll == NULL || item == NULL) return;
    if (index < 0 || index > ll->size) return;

    if (index == 0){
        ll_prepend(ll, item);
        return;
    }
    if (index == ll->size){
        ll_push(ll, item);
        return;
    }
    llist_node_t* node = malloc(sizeof(llist_node_t));
    if (node == NULL) return;
    node->value = item;
    llist_node_t* curr = ll->head;
    for (int i = 0; i < index; i++)
        curr = curr->next;
    node->prev = curr->prev;    // node prev is A
    node->next = curr;          // node next is B
    curr->prev->next = node;    // put node as next to A
    curr->prev = node;          // put node as prev to B
    ll->size++;                 // makes A -> node -> B
}

void ll_remove(llist_t* ll, int index){
    if (ll == NULL) return;
    if (index < 0 || index >= ll->size) return;

    if (index == 0){
        ll_shift(ll);
        return;
    }
    if (index == ll->size - 1){
        ll_pop(ll);
        return;
    }
    llist_node_t* curr = ll->head;
    for (int i = 0; i < index; i++)
        curr = curr->next;
    curr->prev->next = curr->next; // sets A next as B
    curr->next->prev = curr->prev; // sets B prev as A
    free(curr);                    // detaches curr from memory
    ll->size--;
}

int ll_len(llist_t* ll){
    if (ll == NULL) return -1;
    return ll->size;    
}

void ll_free(llist_t* ll){
    llist_node_t* curr = ll->head;
    while (curr != NULL){
        llist_node_t* next = curr->next; 
        free(curr);
        curr = next;
    }
    free(ll);
}

// hashmaps
// prerequities
#define MAP_INITIAL_CAPACITY 16

static int hash(const char* key, int capacity){ // example: key = "hi", capacity = 10, h = 0
    unsigned int h = 0;                         // h = 0 * 31 + 'h' = 104
    while (*key) h = h * 31 + *key++;           // h = 104 * 31 + 'i' = 3224 + 105 = 3329
    return h % capacity;                        // return 
}

map_t* map_new(void){
    map_t* map = malloc(sizeof(map_t));
    if (map == NULL) return NULL;
    map->buckets = calloc(MAP_INITIAL_CAPACITY, sizeof(map_entry_t*));
    if (map->buckets == NULL) return NULL;
    map->size = 0;
    map->capacity = MAP_INITIAL_CAPACITY;
    return map;
}

void map_set(map_t* map, char* key, void* value) {
    if (map == NULL || key == NULL) return;

    int index = hash(key, map->capacity);
    map_entry_t* curr = map->buckets[index];
    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            curr->value = value;
            return;
        }
        curr = curr->next;
    }

    map_entry_t* entry = malloc(sizeof(map_entry_t));
    if (entry == NULL) return;
    entry->key = strdup(key);
    entry->value = value;
    entry->next = map->buckets[index];
    map->buckets[index] = entry;
    map->size++;

    if ((float)map->size / map->capacity > 0.75) {
        int new_capacity = map->capacity * 2;
        map_entry_t** new_buckets = calloc(new_capacity, sizeof(map_entry_t*));
        if (new_buckets == NULL) return;

        for (int i = 0; i < map->capacity; i++) {
            map_entry_t* curr = map->buckets[i];
            while (curr != NULL) {
                map_entry_t* next = curr->next;
                int new_index = hash(curr->key, new_capacity);
                curr->next = new_buckets[new_index];
                new_buckets[new_index] = curr;
                curr = next;
            }
        }

        free(map->buckets);
        map->buckets = new_buckets;
        map->capacity = new_capacity;
    }

    // should implement incremental rehashing later 
}

void* map_get(map_t* map, char* key){
    if (map == NULL || key == NULL) return NULL;
    int index = hash(key, map->capacity);
    map_entry_t* curr = map->buckets[index];
    while (curr != NULL){
        if (strcmp(curr->key, key) == 0)
            return curr->value;
        curr = curr->next;
    }
    return NULL;
}

void map_del(map_t* map, char* key){
    if (map == NULL || key == NULL) return;
    int index = hash(key, map->capacity);
    map_entry_t* curr = map->buckets[index];
    map_entry_t* prev = NULL;
    while (curr != NULL){
        if (strcmp(curr->key, key) == 0){
            if (prev == NULL) map->buckets[index] = curr->next;
            else prev->next = curr->next;
            free(curr->key);
            free(curr);
            map->size--;
            return;
        }
        prev = curr; 
        curr = curr->next;
    }
}

int map_has(map_t* map, char* key){
    if (map == NULL || key == NULL) return -1;
    return map_get(map, key) != NULL;
}

char** map_keys(map_t* map){
    if (map == NULL) return NULL;
    char** keys = malloc(sizeof(char*) * map->size);
    if (keys == NULL) return NULL;
    int k = 0;
    for (int i = 0; i < map->capacity; i++){
        map_entry_t* curr = map->buckets[i];
        while (curr != NULL){
            keys[k++] = curr->key;
            curr = curr->next;
            
        }
    }
    return keys;
}

int map_len(map_t* map){
    if (map == NULL) return -1;
    return map->size;
}

void map_free(map_t* map){
    if (map == NULL) return;
    for (int i = 0; i < map->capacity; i++){
        map_entry_t* curr = map->buckets[i];
        while (curr != NULL){
            map_entry_t* next = curr->next;
            free(curr->key);
            free(curr);
            curr = next;
        }
    }
    free(map->buckets);
    free(map);
}

// hashset

// prerequities of hashset

#define SET_INITIAL_CAPACITY 16

set_t* set_new(void) {
    set_t* set = malloc(sizeof(set_t));
    if (set == NULL) return NULL;
    set->buckets = calloc(SET_INITIAL_CAPACITY, sizeof(set_entry_t*));
    set->size = 0;
    set->capacity = SET_INITIAL_CAPACITY;
    return set;
}

void set_add(set_t* set, char* item) {
    if (set == NULL || item == NULL) return;
    int index = hash(item, set->capacity);
    set_entry_t* curr = set->buckets[index];
    while (curr != NULL) {
        if (strcmp(curr->key, item) == 0) return;
        curr = curr->next;
    }
    set_entry_t* entry = malloc(sizeof(set_entry_t));
    if (entry == NULL) return;
    entry->key = strdup(item);
    entry->next = set->buckets[index];
    set->buckets[index] = entry;
    set->size++;

    if ((float)set->size / set->capacity > 0.75) {
        int new_capacity = set->capacity * 2;
        set_entry_t** new_buckets = calloc(new_capacity, sizeof(set_entry_t*));
        for (int i = 0; i < set->capacity; i++) {
            set_entry_t* curr = set->buckets[i];
            while (curr != NULL) {
                set_entry_t* next = curr->next;
                int new_index = hash(curr->key, new_capacity);
                curr->next = new_buckets[new_index];
                new_buckets[new_index] = curr;
                curr = next;
            }
        }
        free(set->buckets);
        set->buckets = new_buckets;
        set->capacity = new_capacity;
    }
    
    // might implement incremental rehashing here later aswell.
}

void set_remove(set_t* set, char* item) {
    if (set == NULL || item == NULL) return;
    int index = hash(item, set->capacity);
    set_entry_t* curr = set->buckets[index];
    set_entry_t* prev = NULL;
    while (curr != NULL) {
        if (strcmp(curr->key, item) == 0) {
            if (prev == NULL) set->buckets[index] = curr->next;
            else prev->next = curr->next;
            free(curr->key);
            free(curr);
            set->size--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

int set_has(set_t* set, char* item) {
    if (set == NULL || item == NULL) return 0;
    int index = hash(item, set->capacity);
    set_entry_t* curr = set->buckets[index];
    while (curr != NULL) {
        if (strcmp(curr->key, item) == 0) return 1;
        curr = curr->next;
    }
    return 0;
}

char** set_items(set_t* set) {
    if (set == NULL) return NULL;
    char** items = malloc(sizeof(char*) * set->size);
    int k = 0;
    for (int i = 0; i < set->capacity; i++) {
        set_entry_t* curr = set->buckets[i];
        while (curr != NULL) {
            items[k++] = curr->key;
            curr = curr->next;
        }
    }
    return items;
}

int set_len(set_t* set) {
    return set->size;
}

void set_free(set_t* set) {
    for (int i = 0; i < set->capacity; i++) {
        set_entry_t* curr = set->buckets[i];
        while (curr != NULL) {
            set_entry_t* next = curr->next;
            free(curr->key);
            free(curr);
            curr = next;
        }
    }
    free(set->buckets);
    free(set);
}

// stack
stk_t* stk_new(void){
    stk_t* stk = malloc(sizeof(stk_t));
    if (stk == NULL) return NULL;
    stk->items = malloc(sizeof(void*) * 8);
    stk->size = 0;
    stk->capacity = 8;
    return stk;
}


void stk_push(stk_t* stk, void* item){
    if (stk == NULL || item == NULL) return;
    if (stk->size == stk->capacity){
        stk->capacity *= 2;
        stk->items = realloc(stk->items, sizeof(void*) * stk->capacity);
    }
    stk->items[stk->size++] = item;
}

void* stk_pop(stk_t* stk){
    if (stk == NULL || stk->size == 0) return NULL;
    void* item = stk->items[--stk->size];
    if (stk->size < stk->capacity / 4 && stk->capacity > 8){
        stk->capacity /= 2;
        stk->items = realloc(stk->items, sizeof(void*) * stk->capacity);
    }
    return item;
}

void* stk_peek(stk_t* stk){
    if (stk == NULL || stk->size == 0) return NULL;
    return stk->items[stk->size - 1];
}

int stk_len(stk_t* stk){
    return stk->size;
}

void stk_free(stk_t* stk){
    free(stk->items);
    free(stk);
}

// queue
q_t* q_new(void) {
    q_t* q = malloc(sizeof(q_t));
    if (q == NULL) return NULL;
    q->front = NULL;
    q->back = NULL;
    q->size = 0;
    return q;
}

void q_enqueue(q_t* q, void* item) {
    if (q == NULL || item == NULL) return;
    queue_node_t* node = malloc(sizeof(queue_node_t));
    if (node == NULL) return;
    node->value = item;
    node->next = NULL;
    if (q->back == NULL) {
        q->front = node;
        q->back = node;
    } else {
        q->back->next = node;
        q->back = node;
    }
    q->size++;
}

void* q_dequeue(q_t* q) {
    if (q == NULL || q->size == 0) return NULL;
    queue_node_t* node = q->front;
    void* item = node->value;
    q->front = node->next;
    if (q->front == NULL) q->back = NULL;
    q->size--;
    free(node);
    return item;
}

void* q_peek(q_t* q) {
    if (q == NULL || q->size == 0) return NULL;
    return q->front->value;
}

int q_len(q_t* q) {
    return q->size;
}

void q_free(q_t* q) {
    queue_node_t* curr = q->front;
    while (curr != NULL) {
        queue_node_t* next = curr->next;
        free(curr);
        curr = next;
    }
    free(q);
}

// tensor
tensor_t* tensor_new(int* shape, int ndim){
    tensor_t* t = malloc(sizeof(tensor_t));
    t->ndim = ndim;
    t->shape = malloc(sizeof(int) * ndim);
    t->strides = malloc(sizeof(int) * ndim);
    t->size = 1;
    for (int i = 0; i < ndim; i++){
        t->shape[i] = shape[i];
        t->size *= shape[i];
    }
    t->strides[ndim - 1] = 1;
    for (int i = ndim - 2; i >= 0; i--)
        t->strides[i] = t->strides[i + 1] * t->shape[i + 1];
    t->data = calloc(t->size, sizeof(float));
    return t;
}

float tensor_get(tensor_t* t, int* indices){
    int index = 0;
    for (int i = 0; i < t->ndim; i++)
        index += indices[i] * t->strides[i];
    return t->data[index];
}

void tensor_set(tensor_t* t, int* indices, float value){
    int index = 0;
    for (int i = 0; i < t->ndim; i++)
        index += indices[i] * t->strides[i];
    t->data[index] = value;
}

void tensor_free(tensor_t* t){
    free(t->data);
    free(t->shape);
    free(t->strides);
    free(t);
}
