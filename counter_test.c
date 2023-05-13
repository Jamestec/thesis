#include "fpgam.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define START 10000

int func(int *stop) {
	int const memFd = open("/dev/mem", O_RDWR | O_SYNC);
	int *mapping = mmap(NULL, 6*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0x43C00000);
	*(mapping+1) = 0;
	int count_out = *(mapping+3);
	munmap(mapping, 6*sizeof(int));
	close(memFd);
	return count_out;
}

int main(int argc, char **argv) {
	program_pl("bitstreams/count1.bin", 0);

	int results[20];
	int const memFd = open("/dev/mem", O_RDWR | O_SYNC);
	int *mapping = mmap(NULL, 6*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0x43C00000);
	close(memFd);
	if(mapping == MAP_FAILED){
    		printf("Mapping Failed\n");
    		return 1;
	}
	for (int i=100;i<120;i++) {
		*mapping = 1;
		*mapping = 0;
		*(mapping + 2) = i;
		*(mapping + 1) = 1;
		*(mapping + 1) = 0;
		results[i-100] = *(mapping + 3);
	}
	munmap(mapping, 6*sizeof(int));

	char string[200];
	for (int i = 0; i < 200; i++) {
		string[i] = '\0';;
	}
	char *outputs = string;
	*outputs++ = '[';
	for (int i = 0; i < 20; i++) {
		outputs = outputs + snprintf(outputs, 6, "%d, ", results[i]);
	}
	*--outputs = '\0';
	*--outputs = ']';

	printf("PS next instruction delay in PL clock cycles:\n%s", string);

	/*
	int results[100];
	//for (int i=START;i<START+100;i++) {
	int const memFd = open("/dev/mem", O_RDWR | O_SYNC);
	int *mapping = mmap(NULL, 6*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0x43C00000);
	close(memFd);
	if(mapping == MAP_FAILED){
    		printf("Mapping Failed\n");
    		return 1;
	}
	int done = -1;
	int count_out = -1;
	for (int i=START;i<START+100;i++) {
		*mapping = 1;
		*mapping = 0;
		printf("to = %d, done = %d, out = %d\n", i, *(mapping+4), *(mapping+3));
		*(mapping + 2) = i;
		*(mapping + 1) = 1;
		//munmap(mapping, 6*sizeof(int));
		//printf("test\n");
		//count_out = func(mapping);
		*(mapping + 1) = 0;
		done = *(mapping + 4);
		count_out = *(mapping + 3);
		//*(mapping + 1) = 0;
		results[i-START] = count_out;
		printf("done = %d\n", done);
		printf("out = %d\n\n", count_out);
		//*(mapping + 1) = 0;
	}

	munmap(mapping, 6*sizeof(int));

	//FILE *fptr = fopen("overheads/bare_next_instr.txt", "w");
	for (int i = 0; i < 100; i++) {
		//fprintf(fptr, "%d\n", results[i]);
		printf("%d\n", results[i]);
	}
	//fclose(fptr);
	*/
	
	return 0;
}
