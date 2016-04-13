.include <src.opts.mk>

.PATH: ${.CURDIR}/../common ${.CURDIR}/../../../common

FILES= boot1 boot1.bin

PROG=           boot1.elf
NEWVERSWHAT=    "OMAP4 BOOT" ${MACHINE_ARCH}
BINDIR?=	/boot
INSTALLFLAGS=	-b
WARNS?=		2
MAN=

TEXT_BASE=	0x40300000

SRCS=	start.S boot1.c panda.c cons.c \
	main.c vers.c util.c gpt.c crc32.c drv.c \
	syscall.c

.PATH: ${.CURDIR}/../../../../../contrib/compiler-rt/lib/builtins
.PATH: ${.CURDIR}/../../../../../contrib/compiler-rt/lib/builtins/arm

SRCS+=	umoddi3.c udivsi3.S divsi3.S umodsi3.S aeabi_uldivmod.S aeabi_uidivmod.S \
	udivmoddi4.c aeabi_div0.c udivmodsi4.S

ACFLAGS+= -D__ASSEMBLY__

CFLAGS+= -DBOOTPROG=\"boot\" \
	 -DGPT \
	 -DUFS1_AND_UFS2 \
	 -O3 \
	 -I${.CURDIR}/../../../common \
	 -I${.CURDIR}/../common \
	 -I${.CURDIR}/../include \
	 -I${.CURDIR}/../../../.. \
	 -ffreestanding -msoft-float

LDFLAGS= -nostdlib -static -dead_strip \
	 -T ${.CURDIR}/boot1.lds -Ttext ${TEXT_BASE}

LIBOMAP4= 	${.OBJDIR}/../libomap4/libomap4.a
LDADD=		${LIBOMAP4}

HOST_CC?= /usr/bin/cc

vers.c:	${.CURDIR}/../../../common/newvers.sh ${.CURDIR}/version
	sh ${.CURDIR}/../../../common/newvers.sh ${.CURDIR}/version ${NEWVERSWHAT}

boot1: boot1.bin signGP
	./signGP boot1.bin ${TEXT_BASE}

boot1.bin: ${PROG}
	${OBJCOPY} -S -O binary ${PROG} ${.TARGET}

signGP: ${.CURDIR}/signGP.c
	${HOST_CC} -Wall -g -O3 -o ${.TARGET} ${.CURDIR}/signGP.c

machine:
	ln -sf ${.CURDIR}/../../../../${MACHINE_CPUARCH}/include machine

CLEANFILES+= boot1 boot1.bin vers.c signGP machine

.include <bsd.prog.mk>
