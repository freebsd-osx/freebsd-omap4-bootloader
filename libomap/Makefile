.include <src.opts.mk>


LIB=		omap
INTERNALLIB=
WARNS?=		2

SRCS+=	init.c omap_data.c prcm-regs.c clock.c vc.c timer.c syslib.c \
	omap_gpio.c abb.c reset.c emif-common.c

.PATH: ${.CURDIR}/../../../../libkern/arm
SRCS+=	divsi3.S

#SRCS+=	_udivsi3.S
#SRCS+=	util.c cons.c uart_ns16550.c
#SRCS+=	mmc.c gpt.c crc32.c drv.c
#.PATH: ${.CURDIR}/../../../../../contrib/compiler-rt/lib/builtins/arm
#SRCS+=	udivsi3.S divsi3.S aeabi_div0.c #umodsi3.S

# Decide level of UFS support.
#GPTBOOT_UFS?=	UFS1_AND_UFS2

#ACFLAGS+=	-D__ASSEMBLY__

#CFLAGS+= -DBOOTPROG=\"gptboot\" \
#	 -DGPT
# 	 -D${GPTBOOT_UFS}
CFLAGS+= -D_STANDALONE
CFLAGS+= -I${.CURDIR}/../include/ \
	 -I. \
	 -ffreestanding -msoft-float -Os

machine:
	ln -sf ${.CURDIR}/../../../../${MACHINE_CPUARCH}/include machine

CLEANFILES+=	machine

.include <bsd.lib.mk>

beforedepend ${OBJS}: machine
