# Description
This repo provides fpgam_lib ([folder here](cFS/libs/)) and several cFS applications demonstrating its use ([apps here](cFS/apps)).

fpgam_lib allows any cFS application to program programmable logic on a hybrid System on Chip, such as the ZedBoard. Combined with mmio_lib (created by Dong, available here: https://github.com/dong-zh/Thesis), these libraries allow a cFS application to easily program and communicate with programmable logic.

make SIMULATION=native prep && make && make install
