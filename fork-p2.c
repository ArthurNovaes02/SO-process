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

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define N 3
// Com N = 3, são criado 8 processos, isso acontece por causa do for que são gerado os forks
/*
 * loop 0: p1 (1 processo)
 * loop 1: p1 // p1-2 (2 processos)
 * loop 2: p1 // p1-2 // p1-3 // p1-2-1 (4 processos)
 * loop 3: p1 // p1-2 // p1-3 // p1-2-1 // p1-3 // p1-2-2 // p1-3-1 // p1-2-1-1 (8 processos)
 */

int main()
{
	const char *name = "shared_memory";
	const char *name2 = "shared_memory2";
	const int SIZE = 4096;

	int shm_fd;
	void *ptr;
	int i;

	// pega o número do processo do Pai
	int numProcPai = getpid();



	/*
	int shm_fd2;
	char *ptr2;
	shm_fd2 = shm_open(name2, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd2,SIZE);
	ptr2 = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd2, 0);
	if (ptr2 == MAP_FAILED) {
		printf("Map 2 failed\n");
		return -1;
	}
	*ptr2 = numProcPai;




	/* open the shared memory segment */
	shm_fd = shm_open(name, O_RDONLY, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	/* now map the shared memory segment in the address space of the process */
	ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}
   
	/* now read from the shared memory region */
   	char *palavra = (char*)ptr;
	char letra = *((char*)(ptr+strlen(ptr)+1));
	int tamanho = strlen(ptr);
	
	printf("Palavra: %s\n", palavra);
	printf("Letra a ser procurada: %c\n", letra);
	printf("Tamanho da palavra %d\n\n", tamanho);

	// cria 8 processos
	for(int a = 0; a < N; a++) {
		fork () ; //Cria novo processo
	}
	
	int count = 0;
	int pedaco = getpid() - numProcPai;
	printf("Sou o processo %5d, pedaco: %5d\n", getpid(), pedaco);

	// conta o número de incidências
	for (int i = (tamanho/8)*pedaco; i < tamanho; i++) {
		if(palavra[i] == letra){
			count ++;
		}
	}
	printf("Número de incidências: %d\n", count);

	
//	sleep(60);
	/* remove the shared memory segment */
//	if (shm_unlink(name) == -1) {
//		printf("Error removing %s\n",name);
//		exit(-1);
//	}

	return 0;
}
