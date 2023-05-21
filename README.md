# Description
This repo provides fpgam_lib ([folder here](cFS/libs/)) and several core Flight Software (cFS, available here: https://github.com/nasa/cFS) applications demonstrating its use ([apps here](cFS/apps)).

fpgam_lib allows any cFS application to program programmable logic on a hybrid System on Chip (SoC), such as the ZedBoard. Combined with mmio_lib (created by Dong, available here: https://github.com/dong-zh/Thesis), these libraries allow a cFS application to easily program and communicate with programmable logic.

Note fpgam_lib uses Linux's FPGA Manager, so it only works when used with an operating system that uses the Linux Kernel.

# Usage
It is assumed that you have completed CFS-101 (available here: https://github.com/nasa/CFS-101) which goes through how to develop cFS apps, run cFS and use the Ground System for an older version of cFS.

## Replicate the work by duplicating the repo and SD card
There needs to be two copies of the repo: one will be on a computer to be the "Ground System" and the other will be on the SD card in the ZedBoard.

1. Clone the repo onto your computer with `git clone git@github.com:Jamestec/thesis.git` or click on the green `<> Code` button and press Download ZIP and then extract the files from the ZIP file.

2. Clone the SD card by downloading an image of the SD card (`ZedBoard_fpgam_tidy_5GB.img.zip`) here: https://1drv.ms/u/s!Ai1_5E6loMIjgVaJqquxmLJTf4EE?e=rOTwBN  
The file is actually 548MB in size, once you unzip the file, it'll be 5GB.

3. Unzip `ZedBoard_fpgam_tidy_5GB.img.zip` to get `ZedBoard_fpgam_tidy_5GB.img`.

4. For Windows, proceed to [Windows: Cloning the SD card](#windows-cloning-the-sd-card), for MacOS or Linux proceed to [MacOS: Cloning the SD card](#macos-cloning-the-sd-card).

### Windows: Cloning the SD card.

1. Download Rufus (portable version is fine and it's available here: https://rufus.ie/en/) and run Rufus.

2. Plug in your SD card/reader and make sure the correct USB/SD card reader is chosen under the `Device` label.

3. Under the `Boot selection` label, press the `SELECT` button and choose the `ZedBoard_fpgam_tidy_5GB.img` file.

4. Press start to restore the image to your SD card.

5. [After replicating the SD card.](#after-replicating-the-sd-card)

### MacOS: Cloning the SD card.

1. Plug in your SD card/reader and open the Terminal.

2. Find the path to your SD card/reader, for example run `diskutil list` in the terminal.

3. Unmount the SD card/reader with `diskutil unmountDisk /dev/diskX`.

3. Restore the image to your SD card with this terminal command: `sudo dd if=/path/to/ZedBoard_fpgam_tidy_5GB.img of=/dev/diskX bs=1m`. Make sure you replace `/path/to` with the actual path, you can simply drag in the .img file into the terminal. Also make sure you replace `/dev/diskX` with the actual disk path found in step 2. You can check the speed by pressing `control T`. If restoring is going too slowly and you're using MacOS, you can try replacing the disk path with `/dev/rdiskX`: note the change is adding an `r` in front of `disk`.

4. [After replicating the SD card.](#after-replicating-the-sd-card)

### After replicating the SD card.

5. Once the SD card has been restored, ensure the ZedBoard is powered off, the ZedBoard is plugged into a router with an Ethernet cable and the jumpers on the ZedBoard are set to boot the SD card (with the VGA port facing up, from left to right, the jumpers should be down, up, up, down, down, down; with down meaning the bottom two pins are connected).

6. Insert the SD card into the ZedBoard and power on the ZedBoard. The ZedBoard will now boot the Ubuntu install on the SD card.

7. Ubuntu will obtain an IP address, login to your router to see what IP address it was assigned and SSH into Ubuntu. The username is `ubuntu` and the password is `temppwd`.

8. Navigate to the cFS directory with `cd ~/thesis/cFS`.

9. Build cFS with `make SIMULATION=native prep && make && make install`.

10. Run cFS on the ZedBoard with `cd build/exe/cpu1` and then `sudo ./core-cpu1`. cFS should now be running. You cannot `sudo build/exe/cpu1/copre-cpu1`, you need to be in the cpu1 directory. Sudo is required to use the FPGA Manager.

11. On the computer/Ground System, navigate to `thesis/cFS/tools/cFS-GroundSystem`.

12. Launch the Ground System with `python GroundSystem.py` (or `python3 GroundSystem.py` depending on how python is setup on your computer).

13. Please go over CFS-101 for how to use the Ground System. Some pointers in using my apps: 
* Make sure you press Display Page and fix the IP address, it should be the same IP address as the ZedBoard obtained in step 5. Otherwise you can edit `thesis/cFS/tools/cFS-GroundSystem/Subsystems/cmdGui/command-pages.txt` and `thesis/cFS/tools/cFS-GroundSystem/Subsystems/cmdGui/quick-buttons.txt` with the correct IP address.
* `PL_Control`, `FIR App` and `FIR2 App` are my Thesis B demo to demonstrate fpgam_lib working with full and partial bitstreams. They use the Centralised Approach where interactions with the PL are all done through `PL_Control`. The FIR apps will send Software Bus messages to PL_Control, requesting actions to be done on the PL.
* `PL_Control`'s source code is in [cFS/apps/sample_app](cFS/apps/sample_app).
* You aren't meant to send messages to `PL_Control` from the Ground System, you still can for custom behaviour, but you're meant to use `FIR App` and `FIR2 App` which in turn uses `PL_Control`.
* The two FIR apps have the same behaviour, the purpose of having two is to demonstrate `PL_Control` only allowing one app to use the PL at the same time.
* `FIR_APP_FULLFIR1_CC` will program the PL with non-zero coefficents and `FIR_APP_FULLFIR0_CC` will program the PL with coefficents that are all zero, therefore the output will always be zero. The partial variants only partially reconfigure the FIR IP core.
* Use `FIR_APP_RELEASE_CC` after programming the PL to allow another app to program or use the PL.
* SpeedTest app is my Thesis C demo, the purpose is to demonstrate that MIMO transfer speeds of a cFS application is similar to a Linux application, so there is no overhead. It also demonstrates that using the Software Bus has a large overhead when streaming data, therefore the Centralised Approach which uses the Software Bus a lot is not a good approach.

## No dupe, just using the library.
For information about setting up cFS, please refer to Dong's work here: https://www.youtube.com/watch?v=9uizHChV59k and https://github.com/dong-zh/Thesis .

To use fpgam_lib, make sure the fpgam_lib folder ([folder can be found here](cFS/libs/)) and its contents are present in the libs folder of your cFS instance on the hybrid SoC. Then ensure the fpgam_lib will be compiled and launched when cFS starts by modifying the make scripts. If the default makefile and definitions are used, the two files that need to be modified are:

1. `cFS/sample_defs/targets.cmake`
2. `cFS/sample_defs/cpu1_cfe_es_startup.scr`

For the first file, `targets.cmake`, ensure that fpgam_lib is appended to the global app list, for example, the line we’re interested in is by default:

`list(APPEND MISSION_GLOBAL_APPLIST sample_app sample_lib)`

The line needs to be changed to include fpgam_lib, like so:

`list(APPEND MISSION_GLOBAL_APPLIST sample_app sample_lib fpgam_lib)`

For the second file, `cpu1_cfe_es_startup.scr`, ensure that the fpgam_lib starts when cFS starts by adding a line to the file, for example, after the sample_lib entry:

`CFE_LIB, fpgam_lib, fpgam_lib_Init, FPGAM_LIB, 0, 0, 0x0, 0;`

Then for cFS applications that want to use the fpgam_lib library, modify the `CMakeList.txt` file located in the cFS application’s root directory to declare that the application depends on fpgam_lib. This is done by adding the line:

`add_cfe_app_dependency(fpgam_lib)`

The last step is to include the fpgam_lib.h header file in the cFS application’s source code as if the file was in the same directory:

`#include "fpgam_lib.h"`

Then call the function in the library to program a bitstream or bin file. For example:

```
char bin[] = "/home/ubuntu/bitstreams/PSPL.bin";
program_pl(bin, 0);
```

Note that `program_pl` declares the character array without the const qualifier, which means trying to use a string literal as the argument will result in an error when compiling cFS. However, `program_pl` does not actually modify the character array, so it is possible to add the const qualifier to the character array if preferred.

# Loose C files
Compile the files with `gcc fpgam.c theFile.c`.

`PL2PS.c`: this program tests the transfer rate of MMIO from the PL to a Linux application.

`PS2PL.c`: this program tests the transfer rate of MMIO from a Linux application to the PL.

`counter_test.c`: this program prints out the number of PL cycles between two C instructions.

`fpgam.c`: this is the C library version of fpgam.

`fpgam_test.c`: this program was used to stress test fpgam.c.

`fpgautil.c`: this is provided by Xilinx, it uses the system call `system` instead of directly writing to files. It also shows how to read back the PL configuration. Note that this needs the FPGA_MGR_DEBUG_FS flag enabled when compiling the Linux Kernel, by default it's not enabled. Please refer to Dong's work on how to compile the Linux Kernel here: https://youtu.be/9uizHChV59k?t=1268

# bitstreams
`PSPL.bin`: this bitstream has an IP core that runs at 100 MHz and has four 32 bit memory mapped registers using AXI-Lite starting at `0x43C00000`:
1. `0x43C00000` reset: (the least significant bit).
2. `0x43C00004` max: how many clock cycles before the IP core stops accepting new input (32 bits).
3. `0x43C00008` data_in: the input from the PS to the PL. This increments a counter when the most significant bit changes (32 bits).
4. `0x43C0000C` data_out: the IP core's counter value (32 bits).

`count1.bin`: this bitstream has an IP core that runs at 100 MHz and has four 32 bit memory mapped registers using AXI-Lite starting at `0x43C00000`:
1. `0x43C00000` reset: (the least significant bit).
2. `0x43C00004` start: when this is asserted, a counter increments every rising clock edge (the least significant bit).
3. `0x43C00008` max: the counter only ever counts to this number (32 bits).
4. `0x43C0000C` count_out: the IP core's counter value (32 bits).

`fir0.bin`: this bitstream has an IP core that is a rudimentary finite impulse filter. The coefficents are always all zeros so the output will always be zero. It has 12 32 bit memory mapped registers using AXI-Lite starting at `0x43C00000`:
1. `0x43C00000`: 0xDEADBEEF
2. `0x43C00004` start: when this is asserted, the IP core will process the input (the least significant bit).
3. `0x43C00008` reset: (the least significant bit).
4. `0x43C0000C` input: the next input into the FIR (32 bits).
5. `0x43C00010` output: the output of the FIR (32 bits).
6. `0x43C00014` done: asserted when the FIR has finished processing the input (the least significant bit).
7. `0x43C00018` stage: I don't remember.
8. `0x43C0001C` shift1: the value of the IP core's 1st shift register used to calculate the FIR output (32 bits).
9. `0x43C00020` shift2: the value of the IP core's 2nd shift register used to calculate the FIR output (32 bits).
10. `0x43C00024` shift3: the value of the IP core's 3rd shift register used to calculate the FIR output (32 bits).
11. `0x43C00028` shift4: the value of the IP core's 4th shift register used to calculate the FIR output (32 bits).
12. `0x43C0002C` clk_count: I don't remember, I think it's just a counter that increments on each rising edge so you know the IP core is alive (32 bits).

`fir0p.bin`: this bitstream is the partial bitstream version of `fir0.bin`. It reprograms the whole custom IP core, not just the coefficients.

`fir1.bin`: this bitstream has an IP core that is a rudimentary finite impulse filter. The coefficents are not all zeros so the output will change. It has 5 32 bit memory mapped registers using AXI-Lite starting at `0x43C00004` (`0x43C00000` is 0xDEADBEEF):   
See `fir0.bin` for details.

`fir1p.bin`: this bitstream is the partial bitstream version of `fir1.bin`. It reprograms the whole custom IP core, not just the coefficients.

`leddefault.bin`: this bitstream links the switches on the ZedBoard with the LEDs. Toggling the switches will change the state of a corresponding LED.

`leddefaultnot.bin`: this bitstream is like `leddefault.bin`, but the logic between the switches and LEDs are inverted. Programming this will show the opposite state of the LEDs compared to `leddefault.bin`.

`leddefaultnotpartial.bin`: this bitstream is the partial bitstream version of `leddefaultnot.bin`. It only reprograms the custom IP core.

`leddefaultpartial.bin`: this bitstream is the partial bitstream version of `leddefault.bin`. It only reprograms the custom IP core.

# Help, it doesn't work???
The code present in the master branch is my cleaned up version and I may have broken something (I only checked that cFS compiles and the apps run).

Try using the messy branch (https://github.com/Jamestec/thesis/tree/messy) to see if the problem is fixed. 

Otherwise post an issue. Since I don't have a ZedBoard anymore, I will have to collaborate with you to fix the problem.
