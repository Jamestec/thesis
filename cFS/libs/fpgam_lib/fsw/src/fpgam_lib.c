#include "fpgam_lib.h"

// Based off of Xilinx's fpgautil.c.
// Ideally file manipulation is done using functions provided by cFS's abstraction layer.
// That is what I tried to do in the file_exists function, however it was not working correctly.
// This may be due to cFS transitioning to version 7.0, which has not been completed.
// However since we're using Linux's FPGA Manager, using POSIX functions should be
// fine since Linux aims to be POSIX compliant.

int gettime(struct timeval  t0, struct timeval t1)
{
        return ((t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec -t0.tv_usec) / 1000.0f);
}

int fpga_state(void)
{
    FILE *fptr;
    char buf[10];
    const char *state_operating = "operating";
    const char *state_unknown = "unknown";

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
    char buffer[256] = "";
    size_t bytes;

    FILE *fptr_from = fopen(from, "rb");
    FILE *fptr_to = fopen(to, "wb");

    while (0 < (bytes = fread(buffer, 1, sizeof(buffer), fptr_from))) {
        fwrite(buffer, 1, bytes, fptr_to);
    }

    fclose(fptr_from);
    fclose(fptr_to);
}

char *get_filename(char *path) {
    char *ret;
    if (path == NULL) return path;
    int i = 0;
    ret = path;
    while (path[i] != '\0') {
        if (path[i] == '/') {
            ret = &path[i+1];
        }
        i++;
    }
    return ret;
}

// Returns 0 if it exists
int file_exists(const char *path) {
    struct stat buffer;
    int res = stat(path, &buffer);
    if (res != 0) {
        CFE_ES_WriteToSysLog("FPGAM_LIB ERROR: %s does not exist.", path);
    }
    return res;

    // For some reason this keeps saying files don't exist.
    /*os_fstat_t buffer;  
    int32 res = OS_stat(path, &buffer);
    if (res == OS_INVALID_POINTER) {
        CFE_ES_WriteToSysLog("FPGAM_LIB ERROR: bin file location is NULL.");
    } else if (res == OS_FS_ERR_PATH_INVALID) {
        CFE_ES_WriteToSysLog("FPGAM_LIB ERROR: %s does not exist.", path);
    } else if (res == OS_FS_ERR_PATH_TOO_LONG) {
        CFE_ES_WriteToSysLog("FPGAM_LIB ERROR: %s path is too long.", path);
    } else if (res == OS_ERROR) {
        CFE_ES_WriteToSysLog("FPGAM_LIB ERROR: %s stat OS call failed.", path);
    } else if (res == OS_ERR_NOT_IMPLEMENTED) {
        CFE_ES_WriteToSysLog("FPGAM_LIB ERROR: %s OS_stat is not implemented for this OS.", path);
    }
    return res != OS_SUCCESS;*/
}

int32 fpgam_lib_Init(void)
{
    OS_printf("Initialised fpgam_lib.\n");
    return CFE_SUCCESS;
}

int32 program_pl(char *binfile, int partial) {

    // Check required files exists
    if (file_exists(binfile) != 0 ||  file_exists("/sys/class/fpga_manager/fpga0/firmware") != 0) {
        return CFE_STATUS_EXTERNAL_RESOURCE_FAIL;
    }

    char *binfilename;
    char copied[512];
    double time;
    struct timeval t1, t0;

    gettimeofday(&t0, NULL);

    // Strip path from binfile
    binfilename = get_filename(binfile);

    // Copy binfile to required path
    snprintf(copied, sizeof(copied), "/lib/firmware/%s", binfilename);
    copy_file(binfile, copied);

    // Determine if in full or partial mode
    int flag;
    FILE *fptr = fopen("/sys/class/fpga_manager/fpga0/flags", "r+");
    fscanf(fptr, "%d", &flag);
    // Set new flag if needed
    if (flag != partial) {
        fprintf(fptr, "%x", partial);
    }
    fclose(fptr);

    // Program the PL using fpga_manager
    fptr = fopen("/sys/class/fpga_manager/fpga0/firmware", "w");
    fprintf(fptr, "%s", binfilename);
    fclose(fptr);

    // Handle flags 1 -> 0 problem
    if (flag == 1 && partial == 0) {
        // Trying to program a .bit can get stuck at writing phase, only retry 3 times.
        for (int i = 0; i < 3; i++) {
            if (!fpga_state()) {
                break;
            } else {
                fptr = fopen("/sys/class/fpga_manager/fpga0/flags", "w");
                fprintf(fptr, "%x", 1);
                fclose(fptr);
                fptr = fopen("/sys/class/fpga_manager/fpga0/firmware", "w");
                fprintf(fptr, "%s", binfilename);
                fclose(fptr);
                fptr = fopen("/sys/class/fpga_manager/fpga0/flags", "w");
                fprintf(fptr, "%x", 0);
                fclose(fptr);
                fptr = fopen("/sys/class/fpga_manager/fpga0/firmware", "w");
                fprintf(fptr, "%s", binfilename);
                fclose(fptr);
            }
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

    return CFE_SUCCESS;
}
