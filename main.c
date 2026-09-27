#include <stdio.h>
#include <sys/mman.h>

typedef struct Block {
    size_t size;
    bool free;
    struct Block* next;
} Block;

void* my_malloc(size_t size) {
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

int my_free(void* addr, size_t size) {
    return munmap(addr, size);
}

int main() {
    int* ptr = my_malloc(sizeof(int) * 15);
    
    for (int i = 0; i < 15; ++i){
        ptr[i] = i;
        printf("%d", ptr[i]);
    }


    if (my_free(ptr, sizeof(int) * 15) == -1){
        perror("munmap error");
    }

}

