#ifndef BDS_TYPES_H
#define BDS_TYPES_H

// arrays
typedef struct {
    void** items;
    int size;
    int capacity;
} array_t;


// linkedlists
typedef struct llist_node {
    void* value;
    struct llist_node* next;
    struct llist_node* prev;
} llist_node_t;

typedef struct {
    llist_node_t* head;
    llist_node_t* tail;
    int size;
} llist_t;


// hashmap
typedef struct map_entry {
    char* key;
    void* value;
    struct map_entry* next;
} map_entry_t;

typedef struct {
    map_entry_t** buckets;
    int size; 
    int capacity;
} map_t;

// hashset

typedef struct set_entry {
    void* key;
    struct set_entry* next;
} set_entry_t;

typedef struct {
    struct set_entry** buckets;
    int size; 
    int capacity; 
} set_t;

// stack

typedef struct {
    void** items;
    int size;
    int capacity;
} stk_t;

// queue

typedef struct queue_node {
    void* value;
    struct queue_node* next; 
} queue_node_t;

typedef struct {
    queue_node_t* front;
    queue_node_t* back; 
    int size;
} q_t;

// tensor

typedef struct {
    float* data;
    int* shape;
    int* strides;
    int ndim;
    int size;
} tensor_t;

#endif
