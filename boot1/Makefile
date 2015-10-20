.include <src.opts.mk>

PROG=           boot1.elf
NEWVERSWHAT=    "OMAP4 SPL " ${MACHINE_ARCH}
TEXT_BASE=	0x40300000
WARNS?=		2

FILES= System.map boot1.bin MLO

SRCS= start.S lowlevel.S platform.c

.PATH: ${.CURDIR}/panda
SRCS+= panda.c

.PATH: ${.CURDIR}/../common
SRCS+= memsize.c sdram_elpida.c uart_ns16550.c cons.c printf.c

MAN=

ACFLAGS+= -D__ASSEMBLY__

CFLAGS+= -DNS16550_REG_SIZE=-4

CFLAGS+= -I${.CURDIR}/../include \
	 -I${.CURDIR}/../../../common \
	 -I. \
	 -ffreestanding -msoft-float -Os

LDFLAGS= -nostdlib -static -dead_strip \
	 -T ${.CURDIR}/ldscript.omap4 -Ttext ${TEXT_BASE}

LIBOMAP4= 	${.OBJDIR}/../libomap/libomap.a
LDADD=		${LIBOMAP4}

HOST_CC?= /usr/bin/cc

vers.c:	${.CURDIR}/../../../common/newvers.sh ${.CURDIR}/version
	sh ${.CURDIR}/../../../common/newvers.sh ${.CURDIR}/version ${NEWVERSWHAT}

MLO: ${PROG} signGP
	./signGP boot1.bin ${TEXT_BASE} CHSETTINGS

signGP: ${.CURDIR}/signGP.c
	${HOST_CC} -Wall -g -O3 -o ${.TARGET} ${.CURDIR}/signGP.c

boot1.bin: ${PROG}
	${OBJCOPY} --gap-fill=0xff -O binary ${PROG} ${.TARGET}

System.map: ${PROG}
	${NM} ${.ALLSRC} | \
	grep -v '\(compiled\)\|\(\.o$$\)\|\( [aUw] \)\|\(\.\.ng$$\)\|\(LASH[RL]DI\)' | \
	sort > System.map

#main.o: ${.CURDIR}/../../../common/ufsread.c

machine:
	ln -sf ${.CURDIR}/../../../../${MACHINE_CPUARCH}/include machine

CLEANFILES+= MLO boot1.bin System.map vers.c sign machine

.include <bsd.prog.mk>

