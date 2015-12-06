.include <src.opts.mk>

LIB=		omap4
INTERNALLIB=
WARNS?=		2

SRCS+= clock.c serial.c vcore.c cpu.c sdram.c syslib.c gpio.c

CFLAGS+= -D_STANDALONE
CFLAGS+= -I${.CURDIR}/../include/ \
	 -I. \
	 -ffreestanding -msoft-float

machine:
	ln -sf ${.CURDIR}/../../../../${MACHINE_CPUARCH}/include machine

CLEANFILES+=	machine

.include <bsd.lib.mk>

beforedepend ${OBJS}: machine
