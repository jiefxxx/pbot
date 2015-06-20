#include <tools/mapping.h>
#include <stdio.h>
#include <stdlib.h>

void* get_memory_map(char* name, int size){
	int fd;
	void* file_memory;
	fd = open(name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd<0){
		printf("error sur open memoire partagée\n");
		exit(fd);
	}
	lseek (fd, size+1, SEEK_SET);
	write (fd, "", 1);
	lseek (fd, 0, SEEK_SET);
	file_memory = mmap (0, size, PROT_WRITE, MAP_SHARED, fd, 0);
	close (fd);
	return file_memory;
}


void release_memory_map(void* pointer, int size){
	munmap (pointer, size);
}
