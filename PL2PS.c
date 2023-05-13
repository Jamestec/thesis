#include "fpgam.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define TIME_S 5
#define TIME_CLK TIME_S*100000000

int main(int argc, char **argv) {
	//program_pl("bitstreams/PSPL.bin", 0);
	
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
	//printf("reset = %d, max = %d, data_in = %d, data_out=%d\n", *reset, *max, *data_in, *data_out);
	printf("Testing PL to PS speed over %d seconds...\n", TIME_S);
	const int rounds = (TIME_CLK / 17 / 4) + 1000;
	*reset = 0;
	for (int i = 0; i < rounds; i++) {
		*data_in = -1;
		*data_in = -500;
		*data_in = 0;
		*data_in = 500;
	}
	//printf("reset = %d, max = %d, data_in = %d, data_out=%d\n", *reset, *max, *data_in, *data_out);
	printf("%d transfers of 32bits happened in %d seconds\n", *data_out, TIME_S);
	double pl_clk = (double)TIME_CLK / (double)*data_out;
	printf("Average PL clock cycles per transfer: %.2f\n", pl_clk);
	double speed = ((double)*data_out * 32) / 8 / 1000 / 1000 / TIME_S;
	printf("PL to PS speed = %.2f MB/s\n", speed);

	munmap(mapping, 6*sizeof(int));
	
	return 0;
}
