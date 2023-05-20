## Thesis Apps
All thesis apps were based off the sample app provided by NASA.

sample_app is actually "PL_Control", I just haven't changed the name to reflect that.

PL_Control and fir_app and fir2_app was used in my Thesis B demo to demonstrate a "Centralised Approach" where "PL_Users" (e.g. fir_app and fir2_app) that wanted to use the PL, needed to send Software Bus messages to PL_Control, who would then interact with the PL on their behalf.

speedtest_app was used in my Thesis C demo to demonstrate that a cFS application had similar MMIO transfer speeds as a Linux application and that streaming data over the Software Bus (which the Centralised Approach would do) is a bad idea as the speed is about 500 times slower.

## NASA provided apps
The ci_lab, sch_lab and to_lab apps are provided by NASA.
sch_lab and to_lab have had their tables modified.
