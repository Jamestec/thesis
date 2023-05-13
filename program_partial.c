/******************************************************************************
 *
 * Copyright (C) 2019-2020 Xilinx, Inc.  All rights reserved.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ******************************************************************************/
/*****************************************************************************/
/**
 * @file: fpgautil.c
 * Simple command line tool to load fpga via overlay or through sysfs interface
 * and read fpga configuration using Xilinx Zynq/ZynqMP fpga manager
 * Author: Appana Durga Kedareswara Rao <appanad@xilinx.com>
 * Author: Nava kishore Manne <navam@xilinx.com>
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
#include <poll.h>
#include <ctype.h>
#include <libgen.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/stat.h>

#define OVERLAY      1
#define FPGA_SYSFS   2
#define READBACK     3
#define ENCRYPTION_USERKEY_EN		(0x20U)

void print_usage(char *prg)
{

	fprintf(stderr, "\n%s: FPGA Utility for Loading/reading PL Configuration\n\n", prg);
	fprintf(stderr, "Usage:	%s -b <bin file path> -o <dtbo file path>\n\r", prg);
	fprintf(stderr, "\n");
	fprintf(stderr, "Options: -b <binfile>		(Bin file path)\n");
	fprintf(stderr, "         -o <dtbofile>		(DTBO file path)\n");
	fprintf(stderr, "         -f <flags>		Optional: <Bitstream type flags>\n");
	fprintf(stderr, "				   f := <Full | Partial > \n");
	fprintf(stderr, "         -n <Fpga region info>  FPGA Regions represent FPGA's\n");
	fprintf(stderr, "                                and partial reconfiguration\n");
	fprintf(stderr, "                                regions of FPGA's in the\n");
	fprintf(stderr, "                                Device Tree\n");

	fprintf(stderr, " \n");
	fprintf(stderr, "Examples:\n");
	fprintf(stderr, "(Load Full bitstream using Overlay)\n");
	fprintf(stderr, "%s -b top.bit.bin -o can.dtbo -f Full -n Full \n", prg);
	fprintf(stderr, "(Load Partial bitstream using Overlay)\n");
	fprintf(stderr, "%s -b rm0.bit.bin -o rm0.dtbo -f Partial -n PR0\n", prg);
	fprintf(stderr, "(Load Full bitstream using sysfs interface)\n");
	fprintf(stderr, "%s -b top.bit.bin -f Full\n", prg);
	fprintf(stderr, "(Load Partial bitstream using sysfs interface)\n");
	fprintf(stderr, "%s -b rm0.bit.bin -f Partial\n", prg);
	fprintf(stderr, " \n");
}

int gettime(struct timeval  t0, struct timeval t1)
{
        return ((t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec -t0.tv_usec) / 1000.0f);
}

struct fpgaflag {
        char *flag;
        unsigned int value;
};

static struct fpgaflag flagdump[] = {
	{.flag = "Full",                .value = 0x0},
	{.flag = "Partial",             .value = 0x1},
	{.flag = "AuthDDR",             .value = 0x40},
	{.flag = "AuthOCM",             .value = 0x80},
	{.flag = "EnUsrKey",            .value = 0x20},
	{.flag = "EnDevKey",            .value = 0x4},
	{.flag = "AuthEnUsrKeyDDR",     .value = 0x60},
	{.flag = "AuthEnUsrKeyOCM",     .value = 0xA0},
	{.flag = "AuthEnDevKeyDDR",     .value = 0x44},
	{.flag = "AuthEnDevKeyOCM",     .value = 0x84},
	{}
};

static int cmd_flags(int argc, const char *name)
{
	int valid_flag = 0;
	int flag = 0;
	struct fpgaflag *p = flagdump;

	while (p->flag) {
		if (!strcmp(name, p->flag)) {
			flag = p->value;
			break;
		}
		p++;
	}

	return flag;
}

static int isvalid_flags(int argc, const char *name, bool is_secure)
{
	int valid_flag = 0;
	int count = 0;
	struct fpgaflag *p;

	if (!is_secure)
		p = flagdump;
	else
		p = &flagdump[2];

	while (p->flag) {
		if (!strcmp(name, p->flag))
			return 0;
		else if ((!is_secure) && (++count == 2))
			return 1;
		p++;
	}

	return 1;
}

int main(int argc, char **argv)
{
	int ret;
	char *binfile = NULL, *overlay = NULL, *AesKey = NULL, *flag = NULL, *partial_overlay = NULL;
	char *region = NULL, *Module[100] = {0};
	int opt, flags = 0, flow = 0,rm_overlay = 0, readback_type = 0, sflags = 0;
	char command[2048], folder[512], *token, *tmp, *tmp1, *tmp2 , *tmp3;
	const char *filename = "readback", *name;
	struct stat sb;
	double time;
        struct timeval t1, t0;

	if (argc == 1) {
		print_usage(basename(argv[0]));
		return 1;
	}

	while ((opt = getopt(argc, argv, "o:b:n:f:s:p:k:rt::Rh?:")) != -1) {
		switch (opt) {
		case 'o':
			overlay = optarg;
			flow = OVERLAY;
			break;
		case 'b':
			binfile = optarg;
			if (!(flow == OVERLAY))
				flow = FPGA_SYSFS;
			break;
		case 'n':
                        region = optarg;
                        break;
		case 'f':
			if (flow == OVERLAY) {
				name = argv[6];
				flags = cmd_flags(argc, name);
			} else if (flow == FPGA_SYSFS) {
				name = argv[4];
				flags = cmd_flags(argc, name);
			}

			ret = isvalid_flags(argc, name, false);
			if (ret) {
				printf("Error: Invalid arugments :%s\n", strerror(1));
				print_usage(basename(argv[0]));
				return -EINVAL;
                        }

			flags += sflags;
			break;
		case 's':
			if (flow == OVERLAY) {
				name = argv[8];
				sflags = cmd_flags(argc, name);
			} else if (flow == FPGA_SYSFS) {
				name = argv[6];
				sflags = cmd_flags(argc, name);
			}

			ret = isvalid_flags(argc, name, true);
			if (ret) {
				printf("Error: Invalid arugments :%s\n", strerror(1));
				print_usage(basename(argv[0]));
				return -EINVAL;
			}

			flags += sflags;
			break;
		case 'p':
			partial_overlay = optarg;
			break;
		case 'k':
			AesKey = optarg;
			break;	 
		case 't':
			if (optarg == NULL && argv[4] != NULL)
				readback_type = atoi(argv[4]);
			break;
		case 'r':
			if (optarg == NULL && argv[2] != NULL)
				filename = argv[2];
			flow = READBACK;
			break;
		case 'R':
			rm_overlay = 1;
			break;
		case '?':
		case 'h':
		default:
			print_usage(basename(argv[0]));
			return 1;
			break;
		}
	}

	if(region != NULL)
		snprintf(folder, sizeof(folder), "/configfs/device-tree/overlays/%s", region);
	else if (!(flags & 1))
		snprintf(folder, sizeof(folder), "/configfs/device-tree/overlays/full");
	else if (overlay != NULL) {
		printf("Error: Provide valid Overlay region info\n\r");
		return 1;
	}

	
	if (flow == FPGA_SYSFS) {
		if (argc < 3) {
			printf("%s: For more information run %s -h\n", strerror(22), basename(argv[0]));
			return 1;
		}

		snprintf(command, sizeof(command), "echo %x > /sys/class/fpga_manager/fpga0/flags", flags);
		system(command);

		tmp = strdup(binfile);
		while((token = strsep(&tmp, "/"))) {
			tmp1 = token;
		}

		snprintf(command, sizeof(command), "echo %s > /sys/class/fpga_manager/fpga0/firmware", tmp1);
		gettimeofday(&t0, NULL);
		system(command);
		gettimeofday(&t1, NULL);
		time = gettime(t0, t1);

		/* FPGA state check */
		printf("Time taken to load BIN is %f Milli Seconds\n\r", time);
	} else if (flow == READBACK) {
		if (readback_type > 1) {
			printf("Invalid arugments :%s\n", strerror(1));
			printf("For more information run %s -h\n", basename(argv[0]));
			return -EINVAL;	
		}
		snprintf(command, sizeof(command), "echo %x > /sys/module/zynqmp_fpga/parameters/readback_type", readback_type);
		system(command);
		snprintf(command, sizeof(command), "cat /sys/kernel/debug/fpga/fpga0/image >> %s.bin", filename);
		system(command);
		printf("Readback contents are stored in the file %s.bin\n\r", filename);
	}

	return 0;
}

