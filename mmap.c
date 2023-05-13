#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int const memFd = open("/dev/mem", O_RDWR | O_SYNC);
	if (memFd < 0){
		printf("Failed to open the /dev/mem !\n");
		return 0;
	} else {
		printf("open /dev/mem successfully !\n");
	}
	int *mapping;
	mapping = mmap(NULL, 32, PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0x43C00000);
	printf("Mapping %p == %p\n", mapping, MAP_FAILED);
	mapping = mapping + 2;
	*mapping = 5;
	close(memFd);
	return 0;
}
