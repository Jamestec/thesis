# Branch purpose
This version is what was used for the final Thesis demo. The code has not been cleaned up and files not organised. The cleaned up version should be on the master branch.

The purpose of this branch is for reference if my cleaned up version does not work.

Note that references to bitstreams are absolute, therefore the bitstreams folder should be copied to '/home/ubuntu/bitstreams' on the ZedBoard's SD card to copy my environment. You don't need to do this if you restore a clone of my SD card.

# Exact clone of my SD card when I presented my Thesis C demo

An exact clone of the ZedBoard SD card used in the demo is available here:  
https://1drv.ms/u/s!Ai1_5E6loMIjgVfRgfx_ptqhBtzL?e=RUnwVd   
Download size is 856MG, but will unzip to 64GB.   
Note with the original SD card, the final thesis files are actually in the folder `/home/ubuntu/thesis-files/`. The other folders/files are older versions.

The SD card used was a SanDisk Extreme PRO 64GB U3 A2 microSD (capacity reported by Windows Disk Management > Properties > Volumes: 60906 MB).

The image of the SD card was made by:
1. Using macOS's Disk Utility app to create a .dmg file: https://wikis.utexas.edu/display/comm/Mac+OS+-+Make+a+Backup+Copy+of+Your+SD+Card.
2. Converting the .dmg to an .img: hdiutil convert /path/to/input.dmg -format UDTO -o /path/to/output.img
3. Renamed output.img.cdr to output.img and compressing that .img file.

Please see the main branch README.md for instructions on restoring the SD card from the image.

# Unshrunken image of the image in the main branch

In case I shrunk the partition incorrectly, I also have a version of the image in the main branch where I haven't changed the partition size:
https://1drv.ms/u/s!Ai1_5E6loMIjgVgg_vUzu2YUIDVH?e=6AKGQe  

For reference, I shrunk the ext4 partition with these commands:
1. Check for errors: `sudo e2fsck -f /dev/sdb`
2. Resize the file system: `sudo resize2fs /dev/sdb2 3G`
3. Resize the partition: `sudo parted /dev/sdb` then `print` then `resizepart 2 5GB` then `quit`
4. Check for errors: `sudo e2fsck -f /dev/sdb`
