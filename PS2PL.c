#include "fpgam.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// This program tests the transfer rate of MMIO from the PS to the PL.

#define TIME_S 5
#define TIME_CLK TIME_S*100000000

int main(int argc, char **argv) {
	program_pl("bitstreams/PSPL.bin", 0);
	
	int const memFd = open("/dev/mem", O_RDWR | O_SYNC);
	int *mapping = mmap(NULL, 6*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0x43C00000);
	close(memFd);
	if(mapping == MAP_FAILED){
    		printf("Mapping Failed, did you sudo?\n");
    		return 1;
	}
	int *reset = mapping;
	int *max = mapping + 1;
	int *data_in = mapping + 2;
	int *data_out = mapping + 3;
	*reset = 1;
	*max = TIME_CLK;
	*data_in = 0;
	printf("Testing PS to PL speed over %d seconds...\n", TIME_S);
	const int rounds = (TIME_CLK / 17 / 2) + 1000;
	*reset = 0;
	for (int i = 0; i < rounds; i++) {
		*data_in = -1;	// Transfer data to the PL.
		*data_in = 0;		// Transfer data to the PL.
								// The counter in the PL counting the number of transfers only
								// changes when the most sig fig bit changes.
								// Therefore only 31 bits are actually data in each transfer from PS to PL.
	}
	printf("%d transfers of 31bits happened in %d seconds\n", *data_out, TIME_S);
	double pl_clk = (double)TIME_CLK / (double)*data_out;
	printf("Average PL clock cycles per transfer: %.2f\n", pl_clk);
	double speed = ((double)*data_out * 31) / 8 / 1000 / 1000 / TIME_S;
	printf("PS to PL speed = %.2f MB/s\n", speed);

	munmap(mapping, 6*sizeof(int));
	
	return 0;
}
