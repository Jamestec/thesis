#include "fpgam.h"
#include <stdio.h>

int main(int argc, char **argv) {
	int ret = 0;
	int count = 0;
	while (ret == 0) {
		ret = program_pl("bitstreams/leddefault.bin", 0);
		if (ret != 0) {
			/*
			ret = program_pl("bitstreams/leddefault.bin", 1);
			if (ret != 0) {
				printf("first retry dead\n");
			}
			ret = program_pl("bitstreams/leddefault.bin", 0);
			if (ret != 0) {
				printf("second retry dead\n");
				break;
			}
			*/
			break;
		}
		ret = program_pl("bitstreams/leddefaultnotpartial.bin", 1);
		if (ret != 0) break;
		ret = program_pl("bitstreams/leddefaultpartial.bin", 1);
		if (ret != 0) break;
		ret = program_pl("bitstreams/leddefaultnotpartial.bin", 1);
		if (ret != 0) break;
		ret = program_pl("bitstreams/leddefaultpartial.bin", 1);
		if (ret != 0) break;
		ret = program_pl("bitstreams/leddefaultnot.bin", 0);
		if (ret != 0) {
			/*
			ret = program_pl("bitstreams/leddefault.bin", 1);
			if (ret != 0) {
				printf("first retry dead\n");
			}
			ret = program_pl("bitstreams/leddefault.bin", 0);
			if (ret != 0) {
				printf("second retry dead\n");
				break;
			}
			*/
			break;
		}
		ret = program_pl("bitstreams/leddefaultpartial.bin", 1);
		if (ret != 0) break;
		ret = program_pl("bitstreams/leddefaultnotpartial.bin", 1);
		if (ret != 0) break;
		ret = program_pl("bitstreams/leddefaultpartial.bin", 1);
		if (ret != 0) break;
		ret = program_pl("bitstreams/leddefaultnotpartial.bin", 1);
		count = count + 1;
		printf("run %d\n", count);
	}

	return 0;
}
