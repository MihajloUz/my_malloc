#include "malloc.h"
#include <sys/mman.h>
#include <stdbool.h>

typedef struct Block {
    size_t size;
    bool free;
    struct Block *next;
} Block;


//HEAD pointer 
static Block *HEAD = NULL;

void *mmalloc(size_t size) {  //the part where we find the next not occupied chunk of memory
    if (HEAD == NULL){
        void *memory = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); 
        HEAD = memory;
        HEAD->size = size;
        HEAD->free = false;
        HEAD->next = NULL;
        return (char *)HEAD + sizeof(Block); 
    }
    else{
        Block* current = HEAD; //traversing the linked list
        while (current->next != NULL) {
            if (current->free)
                break;
            current = current->next;
        }

        if (current->size >= size && current->free){
            current->free = false;
            current->size = size;
            return (char *)current + sizeof(Block);
        } 

        Block* new_block = (Block *)((char *)current + sizeof(Block) + current->size);
        new_block->size = size;
        new_block->free = false;
        new_block->next = NULL;
        
        return (char *)new_block + sizeof(Block);
    }
}


void mfree(void *addr) {
    if (addr == NULL)
        return;

    Block* block = (Block *)((char *)addr - sizeof(Block));
    block->free = true;
}
