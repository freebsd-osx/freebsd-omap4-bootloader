.include <src.opts.mk>

PROG=           boot2.elf
NEWVERSWHAT=    "OMAP4 SPL " ${MACHINE_ARCH}
TEXT_BASE=	0x40300000
WARNS?=		2

FILES=	System.map boot2.bin MLO

.PATH: ${.CURDIR}/pandaboard

SRCS=	start.S main.c panda.c sdram_elpida.c vers.c

MAN=

ACFLAGS+=	-D__ASSEMBLY__

#CFLAGS+=	-I.
CFLAGS+=	-I${.CURDIR}/../include/

CFLAGS+=	-ffreestanding -msoft-float -Os

LDFLAGS=	-nostdlib -static -dead_strip
LDFLAGS+=	-T ${.CURDIR}/ldscript.omap4 -Ttext ${TEXT_BASE}

LIBOMAP4=	${.OBJDIR}/../lib/libomap4.a

LDADD=		${LIBOMAP4}

vers.c:	${.CURDIR}/../../../common/newvers.sh ${.CURDIR}/version
	sh ${.CURDIR}/../../../common/newvers.sh ${.CURDIR}/version ${NEWVERSWHAT}

MLO: ${PROG} sign
	./sign boot2.bin ${TEXT_BASE} CHSETTINGS

sign: ${.CURDIR}/sign.c
	/usr/bin/cc -Wall -g -O3 -o sign ${.CURDIR}/sign.c

boot2.bin: ${PROG}
	${OBJCOPY} --gap-fill=0xff -O binary ${PROG} ${.TARGET}

System.map: ${PROG}
	${NM} ${.ALLSRC} | \
	grep -v '\(compiled\)\|\(\.o$$\)\|\( [aUw] \)\|\(\.\.ng$$\)\|\(LASH[RL]DI\)' | \
	sort > System.map

machine:
	ln -sf ${.CURDIR}/../../../../${MACHINE_CPUARCH}/include machine

CLEANFILES+=	vers.c sign machine

.include <bsd.prog.mk>

