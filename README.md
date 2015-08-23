# freebsd-omap4-bootloader

Usage

Dowonload the freebsd-omap4-bootloader on sys/boot/arm/omap4
Add omap4 to the SUBDIR in the file /sys/boot/arm/Makefile
Copy the build.sh to the upper directory of the freebsd source directory.
Execute ./build boot
The MLO is created on out/obj/arm.armv6/${WORKING_DIRTORY}/sys/boot/arm/omap4/boot2/
About gpt partion, reffer to http://yagstore.blogspot.kr/2015/07/freebsd-gpt-partiton-on-pandaboard.html

For now, the serial log is available.

To do.
Read the gpt partion and load the ubldr and execute it.

