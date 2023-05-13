#include <stdio.h>
#include <string.h>
#include <sys/time.h>

int gettime(struct timeval  t0, struct timeval t1)
{
        return ((t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec -t0.tv_usec) / 1000.0f);
}

int fpga_state()
{
	FILE *fptr;
	char buf[10];
	char *state_operating = "operating";
	char *state_unknown = "unknown";

	fptr = fopen("/sys/class/fpga_manager/fpga0/state", "r");
	if (fptr) {
		fgets(buf, 10, fptr);
		fclose(fptr);
		if ((strncmp(buf, state_operating, 9) == 0) || (strncmp(buf, state_unknown, 7) == 0))
			return 0;
		else
			return 1;
	}

	return 1;
}

void copy_file(char *from, char *to) {
	char buffer[1024*1024] = "";
	size_t bytes;

	FILE *fptr_from = fopen(from, "rb");
	FILE *fptr_to = fopen(to, "wb");

	while (0 < (bytes = fread(buffer, 1, sizeof(buffer), fptr_from))) {
		fwrite(buffer, 1, bytes, fptr_to);
	}

	fclose(fptr_from);
	fclose(fptr_to);
}

int program_pl(char *binfile, int partial) {
	char *tmp, *token, *tmp1;
	char copied[512];
	double time;
	struct timeval t1, t0;

	gettimeofday(&t0, NULL);

	// Strip path from binfile
	tmp = strdup(binfile);
	while((token = strsep(&tmp, "/"))) {
		tmp1 = token;
	}

	// Copy binfile to required path
	snprintf(copied, sizeof(copied), "/lib/firmware/%s", tmp1);
	copy_file(binfile, copied);

	// Determine if in full or partial mode
	int flag;
	FILE *fptr = fopen("/sys/class/fpga_manager/fpga0/flags", "r+");
	fscanf(fptr, "%d", &flag);
	// Set new flag if needed
	if (flag != partial) {
		/*
		if (flag == 1 && partial == 0) {
			FILE *fptr2 = fopen("/sys/class/fpga_manager/fpga0/firmware", "w");
			fprintf(fptr2, "%s", tmp1);
			fclose(fptr2);
		}
		*/
		fprintf(fptr, "%x", partial);
	}
	fclose(fptr);

	// Program the PL using fpga_manager
	fptr = fopen("/sys/class/fpga_manager/fpga0/firmware", "w");
	fprintf(fptr, "%s", tmp1);
	fclose(fptr);

	// Handle flags 1 -> 0 problem
	if (partial == 0) {
		while (fpga_state()) { // While loop just in case
			fptr = fopen("/sys/class/fpga_manager/fpga0/flags", "w");
			fprintf(fptr, "%x", 1);
			fclose(fptr);
			fptr = fopen("/sys/class/fpga_manager/fpga0/firmware", "w");
			fprintf(fptr, "%s", tmp1);
			fclose(fptr);
			fptr = fopen("/sys/class/fpga_manager/fpga0/flags", "w");
			fprintf(fptr, "%x", 0);
			fclose(fptr);
			fptr = fopen("/sys/class/fpga_manager/fpga0/firmware", "w");
			fprintf(fptr, "%s", tmp1);
			fclose(fptr);
		}
	}

	// Remove the copied binfile
	remove(copied);

	gettimeofday(&t1, NULL);
	time = gettime(t0, t1);

	if (!fpga_state()) {
		printf("Time taken to load BIN is %f Milli Seconds\n\r", time);
		printf("BIN FILE loaded through FPGA manager successfully\n\r");
	} else {
		printf("BIN FILE loading through FPGA manager failed\n\r");
		return 1;
	}

	return 0;
}
