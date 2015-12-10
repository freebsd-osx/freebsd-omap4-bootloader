.include <src.opts.mk>

PROG=           boot1.elf
NEWVERSWHAT=    "OMAP4 BOOT1 " ${MACHINE_ARCH}
TEXT_BASE=	0x40300000
WARNS?=		2

FILES= boot1.bin MLO

SRCS= start.S boot1.c panda.c

.PATH: ${.CURDIR}/../common
SRCS+= main.c printf.c util.c

MAN=

#ACFLAGS+= -D__ASSEMBLY__

CFLAGS+= -I${.CURDIR}/../include \
	 -I. \
	 -ffreestanding -msoft-float

LDFLAGS= -nostdlib -static -dead_strip \
	 -T ${.CURDIR}/boot1.lds -Ttext ${TEXT_BASE}

LIBOMAP4= 	${.OBJDIR}/../libomap4/libomap4.a
LDADD=		${LIBOMAP4}

HOST_CC?= /usr/bin/cc

#vers.c:	${.CURDIR}/../../../common/newvers.sh ${.CURDIR}/version
#	sh ${.CURDIR}/../../../common/newvers.sh ${.CURDIR}/version ${NEWVERSWHAT}

MLO: ${PROG} signGP
	./signGP boot1.bin ${TEXT_BASE}

signGP: ${.CURDIR}/signGP.c
	${HOST_CC} -Wall -g -O3 -o ${.TARGET} ${.CURDIR}/signGP.c

boot1.bin: ${PROG}
	${OBJCOPY} -O binary ${PROG} ${.TARGET}
#	${OBJCOPY} --gap-fill=0xff -O binary ${PROG} ${.TARGET}

#main.o: ${.CURDIR}/../../../common/ufsread.c

machine:
	ln -sf ${.CURDIR}/../../../../${MACHINE_CPUARCH}/include machine

CLEANFILES+= MLO boot1.bin vers.c signGP machine

.include <bsd.prog.mk>
