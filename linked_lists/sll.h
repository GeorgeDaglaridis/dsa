#ifndef __SLL__H
#define __SLL__H

#define SUCCESS    0
#define ERR_ALLOC -1
#define INV_DATA  -2
#define ALRD_INIT -3
#define EMPTY_LL  -4

// Not needed in this code but I added it 
// just for practicing it
#define DEBUG 1

#if DEBUG
    #define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...)
#endif

int list_init(int data);
int add_in_the_beginning(int data);
int add_at_the_end(int data);
int traverse(void);
int exists(int data);
int delete_node(int data); // https://chatgpt.com/g/g-p-6992edb5eef48191bdf9516f432c3dd7-c-coding/c/69e9f10c-5884-83eb-a2c5-7b85df95a930
int delete_node_piyush(int data);
int insert(int key, int data);
int insert_piyush(int key, int data);

#endif