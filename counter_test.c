#include "fpgam.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// This program prints out the number of PL cycles between two C instructions.
// The test is done 20 times.

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
		*mapping = 1;								// Reset
		*mapping = 0;
		*(mapping + 2) = i;						// Set maximum count number
		*(mapping + 1) = 1;						// start signal
		*(mapping + 1) = 0;
		results[i-100] = *(mapping + 3); // Save counter output
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

	return 0;
}
