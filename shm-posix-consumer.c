/**
 * Simple program demonstrating shared memory in POSIX systems.
 *
 * This is the consumer process
 *
 * Figure 3.18
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

int main()
{
	const char *name = "shared_memory";
	const char *name2 = "shared_memory2";
	const char *name3 = "shared_memory3";
	const int SIZE = 4096;

	int shm_fd, shm_fd2, shm_fd3;
	void *ptr, *ptr2, *ptr3;
	int i;
	char find;

	/* open the shared memory segment */
	shm_fd = shm_open(name, O_RDONLY, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	shm_fd2 = shm_open(name2, O_RDONLY, 0666);
	if (shm_fd2 == -1) {
		printf("shared memory2 failed\n");
		exit(-1);
	}
	shm_fd3 = shm_open(name3, O_RDONLY, 0666);
	if (shm_fd3 == -1) {
		printf("shared memory3 failed\n");
		exit(-1);
	}

	/* now map the shared memory segment in the 
	address space of the process */
	ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}
	ptr2 = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd2, 0);
	if (ptr2 == MAP_FAILED) {
		printf("Map2 failed\n");
		exit(-1);
	}
	ptr3 = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd3, 0);
	if (ptr3 == MAP_FAILED) {
		printf("Map3 failed\n");
		exit(-1);
	}

	/* now read from the shared memory region */
	printf("%s\n",(char*)ptr);
	printf("%d\n", *((int*)(ptr+strlen(ptr)+1)));

	find = ((char*)ptr2)[0];
	printf("Letra que sera contada: %c\n", find);

	printf("Tamanho do vetor %d\n", (int)(char*)ptr3);

	// for (int i = 0; i 
	
	// sleep(60);
	/* remove the shared memory segment */
//	if (shm_unlink(name) == -1) {
//		printf("Error removing %s\n",name);
//		exit(-1);
//	}

	return 0;
}
