# Description
This repo provides fpgam_lib ([folder here](cFS/libs/)) and several core Flight Software (cFS, available here: https://github.com/nasa/cFS) applications demonstrating its use ([apps here](cFS/apps)).

fpgam_lib allows any cFS application to program programmable logic on a hybrid System on Chip (SoC), such as the ZedBoard. Combined with mmio_lib (created by Dong, available here: https://github.com/dong-zh/Thesis), these libraries allow a cFS application to easily program and communicate with programmable logic.

Note fpgam_lib uses Linux's FPGA Manager, so it only works when used with an operating system that uses the Linux Kernel.

# Usage
I will assume you have complete CFS-101 (available here: https://github.com/nasa/CFS-101) which goes through how to develop cFS apps, run cFS and use the Ground System for an older version of cFS.

## Replicate the work by duplicating the repo and SD card
There needs to be two copies of the repo: one will be on a computer to be the "Ground System" and the other will be on the SD card in the ZedBoard.

1. Clone the repo onto your computer with `git clone git@github.com:Jamestec/thesis.git` or click on the green `<> Code` button and press Download ZIP and then extract the files from the ZIP file.

2. Clone the SD card by downloading an image of the SD card here: TODO

The image was created using macOS's Disk Utility app (https://wikis.utexas.edu/display/comm/Mac+OS+-+Make+a+Backup+Copy+of+Your+SD+Card).

Therefore you should be able to restore the SD card using these instructions: https://support.apple.com/en-au/guide/disk-utility/dskutl14078/22.0/mac/13.0

Otherwise try using Rufus (available here: https://rufus.ie/en/) if you're using Windows.

3. Once the SD card has been restored, ensure the ZedBoard is powered off, the ZedBoard is plugged into a router with an Ethernet cable and the jumpers on the ZedBoard are set to boot the SD card (with the VGA port facing up, from left to right, the jumpers should be down, up, up, down, down, down; with down meaning the bottom two pins are connected).

4. Insert the SD card into the ZedBoard and power on the ZedBoard. The ZedBoard will now boot the Ubuntu install on the SD card.

5. Ubuntu will obtain an IP address, login to your router to see what IP address it was assigned and SSH into Ubuntu. The username is `ubuntu` and the password is `temppwd`.

6. Navigate to the cFS directory with `cd ~/thesis/cFS`.

7. Build cFS with `make SIMULATION=native prep && make && make install`.

8. Run cFS on the ZedBoard with `cd build/exe/cpu1` and then `sudo ./core-cpu1`. cFS should now be running. You cannot `sudo build/exe/cpu1/copre-cpu1`, you need to be that the cpu1 directory. Sudo is required to use the FPGA Manager.

9. On the computer/Ground System, navigate to `thesis/cFS/tools/cFS-GroundSystem`.

10. Launch the Ground System with `python GroundSystem.py` (or `python3 GroundSystem.py` depending on how python is setup on your computer).

11. Please go ver CFS-101 for how to use the Ground System. Some pointers in using my apps: 
* Make sure you press Display Page and fix the IP address, it should be the same IP address as the ZedBoard obtained in step 5. Otherwise you can edit `thesis/cFS/tools/cFS-GroundSystem/Subsystems/cmdGui/command-pages.txt` and `thesis/cFS/tools/cFS-GroundSystem/Subsystems/cmdGui/quick-buttons.txt` with the correct IP address.
* `PL_Control`, `FIR App` and `FIR2 App` are my Thesis B demo to demonstrate fpgam_lib working with full and partial bitstreams. They use the Centralised Approach where interactions with the PL are all done through `PL_Control`. The FIR apps will send Software Bus messages to PL_Control, requesting actions to be done on the PL.
* `PL_Control`'s source code is in [cFS/apps/sample_app](cFS/apps/sample_app).
* You aren't mean to send messages to `PL_Control` from the Ground System, you still can for custom behaviour, but you're mean to use `FIR App` and `FIR2 App` which in turn uses `PL_Control`.
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

# Help, it doesn't work???
The code present in the master branch is my cleaned up version and I may have broken something (I only checked that cFS compiles and the apps run).

Try using the messy branch (https://github.com/Jamestec/thesis/tree/messy) to see if the problem is fixed. 

Otherwise post an issue. Since I don't have a ZedBoard anymore, I will have to collaborate with you to fix the problem.
