#ifndef DEF_MAPPING_TOOLS
#define DEF_MAPPING_TOOLS

#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <unistd.h>

void* get_memory_map(char* name, int size);
void release_memory_map(void* pointer, int size);

#endif
