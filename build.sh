#!/bin/sh

TOPDIR=$(pwd)
OUTDIR=${TOPDIR}/out
LOGDIR=${TOPDIR}/logs

FREEBSD=${TOPDIR}/freebsd
UBOOT=${TOPDIR}/u-boot

NCPU=$(sysctl -n hw.ncpu)
if [ ${NCPU} -gt 1 ]; then
	WORLD_JFLAGS="-j${NCPU}"
	KERNEL_JFLAGS="-j$(expr ${NCPU} / 2)"
fi

if [ ! -d ${LOGDIR} ]; then
	mkdir ${LOGDIR}
fi

IMG=${OUTDIR}/pandaboard.img
MB=$((1000 * 1000))
GB=$((1000 * $MB))

#IMG_SIZE=$((100 * $MB))  # for kernel-only images
#IMG_SIZE=$((1950 * $MB)) # for 2 Gigabyte
#IMG_SIZE=$((3900 * $MB)) # for 4 Gigabyte
IMG_SIZE=$((7800 * $MB)) # for 8 Gigabyte
#IMG_SIZE=$((15600 * $MB)) # for 16 Gigabyte

FREEBSD_MOUNTPOINT=${OUTDIR}/freebsd
BOOT_MOUNTPOINT=${OUTDIR}/boot

usage() {
	echo "Usage: $0 options"
	echo " $0 xdev : build an arm cross compiler for u-boot"
	echo " $0 boot : build a bootloader"
	echo " $0 buboot : build a u-boot"
	echo " $0 cuboot : clean a u-boot"
	echo " $0 ubldr : build a ubldr"
	echo " $0 bworld : freebsd buildworld"
	echo " $0 bkernel : freebsd buildkernel"
	echo " $0 ikernel : freebsd installkernel"
	echo " $0 iworld : freebsd installworld"
	echo " $0 delobj : rm -rf out/obj"
	echo " $0 mkimg : make out/pandaboard.img"
	echo " $0 mount : mount pandaboard.img"
	echo " $0 umount"
	echo " $0 delmd <md number>"
	echo " $0 cpboot : copy MLO u-boot.img ubldr to BOOT_MOUNTPOINT"
	echo " $0 cprootfs : copy out/rootfs to FREEBSD_MOUNTPOINT"
	echo " $0 delrootfs : rm -rf out/rootfs"
	exit 1
}

create_image() {
	echo "Creating the raw disk image in:"
	echo "    $IMG"
	[ -f $IMG ] && rm -f $IMG
	dd if=/dev/zero of=$IMG bs=512 seek=$(($IMG_SIZE / 512)) count=0 >/dev/null 2>&1
	DISK_MD=`sudo -E mdconfig -a -t vnode -f $IMG`
}

create_gpt() {
	echo gpart create -s GPT ${DISK_MD}
	sudo -E gpart create -s GPT ${DISK_MD}
}

create_boot() {
	echo gpart add -a 4k -b 128K -s 128K -l boot -t freebsd-boot ${DISK_MD}
	sudo -E gpart add -a 4k -b 128K -s 128K -l boot -t freebsd-boot ${DISK_MD}
}

create_gpt_ufs() {
	echo "Creating the UFS partition"

	DISK_UFS_PARTITION=`sudo -E gpart add -a 4k -l disk -t freebsd-ufs ${DISK_MD} | sed -e 's/ .*//'` || exit 1

	DISK_UFS_DEVICE=/dev/${DISK_UFS_PARTITION}

	sudo -E newfs ${DISK_UFS_DEVICE}
	# Turn on Softupdates
	sudo -E tunefs -n enable ${DISK_UFS_DEVICE}
	# Turn on SUJ with a minimally-sized journal.
	# This makes reboots tolerable if you just pull power on the BB
	# Note:  A slow SDHC reads about 1MB/s, so a 30MB
	# journal can delay boot by 30s.
	sudo -E tunefs -j enable -S 4194304 ${DISK_UFS_DEVICE}
	# Turn on NFSv4 ACLs
	sudo -E tunefs -N enable ${DISK_UFS_DEVICE}
}

create_mbr() {
	echo gpart create -s MBR ${DISK_MD}
	sudo -E gpart create -s MBR ${DISK_MD}
}

create_fat() {
	FAT_SIZE=2m
	_DISK_FAT_SLICE=`sudo -E gpart add -a 63 -b 63 -s $FAT_SIZE -t '!12' ${DISK_MD} | sed -e 's/ .*//'`
	DISK_FAT_DEVICE=/dev/${_DISK_FAT_SLICE}
	DISK_FAT_SLICE_NUMBER=`echo ${_DISK_FAT_SLICE} | sed -e 's/.*[^0-9]//'`
	sudo -E gpart set -a active -i ${DISK_FAT_SLICE_NUMBER} ${DISK_MD}

	case $FAT_SIZE in
		*k | [1-9]m | 1[0-6]m) _FAT_TYPE=12
			;;
		*m) _FAT_TYPE=16
			;;
		*g) _FAT_TYPE=32
			;;
	esac
	echo "Default to FAT${_FAT_TYPE} for partition size $FAT_SIZE"

	sudo -E newfs_msdos -L "boot" -F ${_FAT_TYPE} ${DISK_FAT_DEVICE} >/dev/null
}

mount_fat() {
	echo "Mounting FAT partition"
	if [ -d "${BOOT_MOUNTPOINT}" ]; then
		echo "   Removing already-existing mount directory."
		umount $1 || true
		if rmdir ${BOOT_MOUNTPOINT}; then
			echo "   Removed pre-existing mount directory; creating new one."
		else
			echo "Error: Unable to remove pre-existing mount directory?"
			echo "   ${BOOT_MOUNTPOINT}"
			exit 1
		fi
	fi

	mkdir ${BOOT_MOUNTPOINT}
	sudo -E mount_msdosfs ${DISK_FAT_DEVICE} ${BOOT_MOUNTPOINT}
}

create_mbr_ufs() {
	echo "Creating the UFS partition"

	_DISK_UFS_SLICE=`sudo -E gpart add -t freebsd ${DISK_MD} | sed -e 's/ .*//'` || exit 1
	DISK_UFS_SLICE_NUMBER=`echo ${_DISK_UFS_SLICE} | sed -e 's/.*[^0-9]//'`

	sudo -E gpart create -s BSD ${_DISK_UFS_SLICE}
	DISK_UFS_PARTITION=`sudo -E gpart add -t freebsd-ufs ${_DISK_UFS_SLICE} | sed -e 's/ .*//'` || exit 1

	DISK_UFS_DEVICE=/dev/${DISK_UFS_PARTITION}

	sudo -E newfs ${DISK_UFS_DEVICE}
	# Turn on Softupdates
	sudo -E tunefs -n enable ${DISK_UFS_DEVICE}
	# Turn on SUJ with a minimally-sized journal.
	# This makes reboots tolerable if you just pull power on the BB
	# Note:  A slow SDHC reads about 1MB/s, so a 30MB
	# journal can delay boot by 30s.
	sudo -E tunefs -j enable -S 4194304 ${DISK_UFS_DEVICE}
	# Turn on NFSv4 ACLs
	sudo -E tunefs -N enable ${DISK_UFS_DEVICE}
}

mount_ufs() {
	echo "Mounting UFS partition"
	if [ -d "${FREEBSD_MOUNTPOINT}" ]; then
		echo "   Removing already-existing mount directory."
		umount ${FREEBSD_MOUNTPOINT} || true
		if rmdir ${FREEBSD_MOUNTPOINT}; then
			 echo "   Removed pre-existing mount directory; creating new one."
		else
			echo "Error: Unable to remove pre-existing mount directory?"
			echo "   ${FREEBSD_MOUNTPOINT}"
			exit 1
		fi
	fi

	mkdir ${FREEBSD_MOUNTPOINT} || exit 1
	sudo -E mount ${DISK_UFS_DEVICE} ${FREEBSD_MOUNTPOINT} || exit 1
}

make_gpt_image() {
	create_image
	create_gpt
	create_boot
	create_gpt_ufs
}

make_fat_image() {
		create_image
		create_mbr
		create_fat
		create_mbr_ufs
}

mount_image() {
	if [ ! -f $IMG ]; then
		echo "Error $IMG not exist"
		exit 1
	fi
	DISK_MD=`sudo -E mdconfig -a -t vnode -f $IMG`

	DISK_FAT_DEVICE=/dev/${DISK_MD}s1
	DISK_UFS_DEVICE=/dev/${DISK_MD}s2a

	mount_fat
	mount_ufs
}

unmount_image() {
	echo "Unmount partition"

	sudo -E umount ${BOOT_MOUNTPOINT} || true
	rmdir ${BOOT_MOUNTPOINT}

	sudo -E umount ${FREEBSD_MOUNTPOINT} || true
	rmdir ${FREEBSD_MOUNTPOINT}
}

release_md() {
	echo "Release md $1"
	sudo -E mdconfig -d -u $1 || true
	ls -l /dev/md*
}

uboot_envsetup() {
#	export PATH=${OUTDIR}/host/usr/bin:${OUTDIR}/host/usr/arm-freebsd/usr/libexec:$PATH
	export CROSS_COMPILE=arm-freebsd-
	export ARCH=arm

	if [ ! -d ${OUTDIR} ]; then
		mkdir ${OUTDIR}
	fi

	cd ${UBOOT}
}

uboot_build() {
	uboot_envsetup

	gmake distclean
	gmake omap4_panda_config
	time -h gmake HOSTCC=cc V=1 2>&1 | tee u-boot_build.log

	cp -av ${OUTDIR}/u-boot.img ${OUTDIR}/u-boot.img.old
	cp -av ${UBOOT}/u-boot.img ${OUTDIR}/u-boot.img
	cp -av ${OUTDIR}/MLO ${OUTDIR}/MLO.old
	cp -av ${UBOOT}/MLO ${OUTDIR}/MLO
	mv -v ./u-boot_build.log ${LOGDIR}/u-boot_build.log
}

uboot_clean() {
	uboot_envsetup

	gmake clean
}

freebsd_xdev() {
	cd ${FREEBSD}
	export MAKEOBJDIRPREFIX=${OUTDIR}/obj

#	time -h make -j${NCPU} TARGET=arm TARGET_ARCH=arm DESTDIR=${OUTDIR}/host xdev 2>&1 | tee xdev.log
	time -h make -j${NCPU} TARGET=arm TARGET_ARCH=arm destdir=${outdir}/host \
			WITH_GCC=1 WITH_GCC_BOOTSTRAP=1 WITHOUT_CLANG=1 WITHOUT_CLANG_BOOTSTRAP=1 WITHOUT_CLANG_IS_CC=1 WITHOUT_TESTS=1 xdev 2>&1 | tee xdev.log
	mv ./xdev.log ${LOGDIR}/xdev.log

	sudo make -j${NCPU} TARGET=arm TARGET_ARCH=arm destdir=${outdir}/host xdev-links

}

freebsd_envsetup() {
	export MAKEOBJDIRPREFIX=${OUTDIR}/obj
	export MAKESYSPATH=${FREEBSD}/share/mk

	TARGET_ARCH=armv6
	TARGET_CPUTYPE=armv6

	KERNCONF=PANDABOARD

	UBLDR_LOADADDR=0x88000000

	DESTDIR=${OUTDIR}/rootfs

	if [ ! -d ${MAKEOBJDIRPREFIX} ]; then
		mkdir -p ${MAKEOBJDIRPREFIX}
	fi

	cd ${FREEBSD}
}

freebsd_buildworld() {
	freebsd_envsetup

	time -h make ${WORLD_JFLAGS} TARGET_ARCH=${TARGET_ARCH} TARGET_CPUTYPE=${TARGET_CPUTYPE} \
							UBLDR_LOADADDR=${UBLDR_LOADADDR} buildworld 2>&1 | tee buildworld.log

	mv -v ./buildworld.log ${LOGDIR}/buildworld.log
}

freebsd_buildkernel() {
	freebsd_envsetup

	time -h make ${KERNEL_JFLAGS} TARGET_ARCH=${TARGET_ARCH} TARGET_CPUTYPE=${TARGET_CPUTYPE} \
								KERNCONF=${KERNCONF} buildkernel 2>&1 | tee buildkernel.log

	mv -v ./buildkernel.log ${LOGDIR}/buildkernel.log
}

freebsd_delrootfs() {
	freebsd_envsetup

	if [ -d ${DESTDIR} ]; then
		echo "Delete rootfs"
		sudo chflags -R noschg ${DESTDIR}/*
		sudo -E rm -rf ${DESTDIR}
	fi
}

freebsd_installkernel() {
	freebsd_envsetup

	if [ ! -d ${DESTDIR} ]; then
		mkdir -p ${DESTDIR}
	fi

	time -h sudo -E make TARGET_ARCH=${TARGET_ARCH} KERNCONF=${KERNCONF} DESTDIR=${DESTDIR} \
								installkernel 2>&1 | tee installkernel.log
	mv -v ./installkernel.log ${LOGDIR}/installkernel.log
}

freebsd_installworld() {
	freebsd_envsetup

	if [ ! -d ${DESTDIR} ]; then
		mkdir -p ${DESTDIR}
	fi

	time -h sudo -E make TARGET_ARCH=${TARGET_ARCH} TARGET_CPUTYPE=${TARGET_CPUTYPE} \
								DESTDIR=${DESTDIR} SHAREOWN=root SHAREGRP=wheel installworld \
								#INSTALL=${FREEBSD}/tools/install.sh installworld \
								-DWITHOUT_SHAREDOCS -DWITHOUT_EXAMPLES -DWITHOUT_GAMES -DWITHOUT_HTML \
								-DWITHOUT_INFO -DWITHOUT_MAN 2>&1 | tee installworld.log

	time -h sudo -E make TARGET_ARCH=${TARGET_ARCH} TARGET_CPUTYPE=${TARGET_CPUTYPE} \
								DESTDIR=${DESTDIR} distrib-dirs 2>&1 | tee distrib-dirs.log
	time -h sudo -E make TARGET_ARCH=${TARGET_ARCH} TARGET_CPUTYPE=${TARGET_CPUTYPE} \
								DESTDIR=${DESTDIR} distribution 2>&1 | tee distribution.log

	cp -av ${DESTDIR}/boot/ubldr ${OUTDIR}/ubldr

	mv -v ./installworld.log ${LOGDIR}/installworld.log
	mv -v ./distrib-dirs.log ${LOGDIR}/distrib-dirs.log
	mv -v ./distribution.log ${LOGDIR}/distribution.log
}

freebsd_ubldr() {
	freebsd_envsetup

	if [ ! -d ${DESTDIR} ]; then
		mkdir -p ${DESTDIR}
	fi

	buildenv=`make TARGET_ARCH=$TARGET_ARCH buildenvvars`

	eval $buildenv make -C ${FREEBSD}/sys/boot clean
	eval $buildenv make -C ${FREEBSD}/sys/boot obj
	eval $buildenv make -C ${FREEBSD}/sys/boot \
				UBLDR_LOADADDR=${UBLDR_LOADADDR} all 2>&1 | tee ubldr_build.log
	eval sudo -E $buildenv make -C ${FREEBSD}/sys/boot/arm/uboot \
				DESTDIR=${DESTDIR} NO_MAN=true install 2>&1 | tee ubldr_install.log

	mv -v ./ubldr_build.log ${LOGDIR}/ubldr_build.log
	mv -v ./ubldr_install.log ${LOGDIR}/ubldr_install.log

}

freebsd_boot() {
	freebsd_envsetup

	if [ ! -d ${DESTDIR} ]; then
		mkdir -p ${DESTDIR}
	fi

	buildenv=`make TARGET_ARCH=$TARGET_ARCH buildenvvars`

	eval $buildenv make -C ${FREEBSD}/sys/boot/arm/omap4 clean
	eval $buildenv make -C ${FREEBSD}/sys/boot/arm/omap4 obj
	eval $buildenv make -C ${FREEBSD}/sys/boot/arm/omap4 all 2>&1 | tee boot_build.log
#	eval sudo -E $buildenv make -C ${FREEBSD}/sys/boot/arm/uboot \
#				DESTDIR=${DESTDIR} NO_MAN=true install 2>&1 | tee boot_install.log

	mv -v ./boot_build.log ${LOGDIR}/boot_build.log
#	mv -v ./ubldr_install.log ${LOGDIR}/ubldr_install.log

}

freebsd_delobj() {
	OBJDIR=${OUTDIR}/obj

	if [ -d ${OBJDIR} ]; then
		sudo chflags -R noschg ${OBJDIR}/*
		sudo rm -rf ${OBJDIR}
	fi
}

copy_boot() {
	cp -av ${OUTDIR}/MLO ${BOOT_MOUNTPOINT}
	cp -av ${OUTDIR}/u-boot.img ${BOOT_MOUNTPOINT}
	cp -av ${OUTDIR}/rootfs/boot/ubldr ${BOOT_MOUNTPOINT}
}

copy_rootfs() {
	sudo cp -av ${OUTDIR}/rootfs/* ${FREEBSD_MOUNTPOINT}
}

copy_img() {
	sudo dd if=out/pandaboard.img of=/dev/da0 bs=1m
}

fsck_ufs() {
	sudo fsck -t ufs /dev/da0p2
}

case $1 in
	xdev)
		freebsd_xdev
		;;
	buboot)
		uboot_build
		;;
	cuboot)
		uboot_clean
		;;
	bworld)
		freebsd_buildworld
		;;
	bkernel)
		freebsd_buildkernel
		;;
	iworld)
		freebsd_installworld
		;;
	ikernel)
		freebsd_installkernel
		;;
	ubldr)
		freebsd_ubldr
		;;
	boot)
		freebsd_boot
		;;
	delobj)
		freebsd_delobj
		;;
	mkgpt)
		make_gpt_image
		;;
	mkfat)
		make_fat_image
		;;
	mount)
		mount_image
		;;
	umount)
		unmount_image
		;;
	cpboot)
		copy_boot
		;;
	cprootfs)
		copy_rootfs
		;;
	delmd)
		release_md $2
		;;
	delrootfs)
		freebsd_delrootfs
		;;
	fsck)
		fsck_ufs
		;;
	cpimg)
		copy_img
		;;
	*)
		usage
		;;
esac
