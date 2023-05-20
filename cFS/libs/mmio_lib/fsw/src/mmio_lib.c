#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "cfe.h"
#include "mmio_lib.h"

// Rudimentary platform check
#ifndef __linux__
#error This implementation assumes a Linux system. it open()s and mmap()s /dev/mem to perform memory mapped IO.
#endif

// Constants
static char const *const MEM_PATH = "/dev/mem";

static cpusize PAGE_SIZE = 0; // Set in mmio_lib_Init()

// Helper functions
static cpuaddr roundUp(cpuaddr numberToRound, cpusize multiple);

/**
 * @brief This macro evaluates an expression, and it it's false, prints the error message via
 * strerror_r() and returns retVal.
 *
 * @example The following tries to close a file, and if it fails, prepends "Failed to close file" to the message given
 * by strerror_r(), and returns -1: CHECK_STRERROR(close(myFile), "Failed to close file", -1)
 */
#define CHECK_STRERROR(failCond, errMsgPrefix, retVal)                                   \
    do                                                                                   \
    {                                                                                    \
        if ((failCond))                                                                  \
        {                                                                                \
            char const *const DEFAULT_ERROR = "strerror_r() failed to get message";      \
            char              errBuf[256]   = {'\0'};                                    \
            char const       *errMsg        = DEFAULT_ERROR;                             \
                                                                                         \
            errMsg = strerror_r(errno, errBuf, sizeof(errBuf)) ? DEFAULT_ERROR : errBuf; \
            OS_printf("%s: %s\n", (errMsgPrefix), errMsg);                               \
                                                                                         \
            return (retVal);                                                             \
        }                                                                                \
    } while (0)

// Please see the header file for further documentation on the exported functions.

// The Linux implementation uses sysconf() to get the page size.
int32 mmio_lib_Init(void)
{
    CHECK_STRERROR((PAGE_SIZE = sysconf(_SC_PAGESIZE)) == -1, "Failed to get page size", OS_ERROR);

    OS_printf("Initialised mmio_lib, page size is %zu\n", PAGE_SIZE);
    return CFE_SUCCESS;
}

// The Linux implementation uses opens /dev/mem with open(), and then uses mmap() to map the memory.
int32 mmio_lib_NewMapping(void **const mapping, cpuaddr const startAddress, cpusize const size)
{
    // Mapping pointer mustn't be null
    BUGCHECK(mapping != NULL, OS_INVALID_POINTER);
    // Size mustn't be 0
    BUGCHECK(size != 0, OS_ERR_INVALID_SIZE);

    // Round up to the nearest page size
    cpusize const newSize = roundUp(size, PAGE_SIZE);

    int const memFd = open(MEM_PATH, O_RDWR | O_SYNC);
    CHECK_STRERROR(memFd < 0, "Failed to open memory file", OS_ERR_FILE);

    *mapping = mmap(NULL, newSize, PROT_READ | PROT_WRITE, MAP_SHARED, memFd, startAddress);
    CHECK_STRERROR(*mapping == MAP_FAILED, "Failed to mmap", OS_ERROR);

    CHECK_STRERROR(close(memFd), "Failed to close memory file", OS_ERR_FILE);

    return newSize;
}

int32 mmio_lib_DeleteMapping(void *const mapping, cpusize const size)
{
    // Mapping pointer mustn't be null
    BUGCHECK(mapping != NULL, OS_INVALID_POINTER);
    // Size mustn't be 0
    BUGCHECK(size != 0, OS_ERR_INVALID_SIZE);

    // Round up to the nearest page size
    cpusize const newSize = roundUp(size, PAGE_SIZE);

    CHECK_STRERROR(munmap(mapping, newSize), "Failed to munmap", CFE_PSP_ERROR);

    return CFE_SUCCESS;
}

static cpuaddr roundUp(cpuaddr const numberToRound, cpusize const multiple)
{
    return ((numberToRound + multiple - 1) / multiple) * multiple;
}
