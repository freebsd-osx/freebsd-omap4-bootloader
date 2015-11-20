.include <src.opts.mk>

LIB=		omap4
INTERNALLIB=
WARNS?=		2

SRCS+= clock.c syslib.c serial.c id.c sdram.c

CFLAGS+= -D_STANDALONE
CFLAGS+= -I${.CURDIR}/../include/ \
	 -I. \
	 -ffreestanding -msoft-float

machine:
	ln -sf ${.CURDIR}/../../../../${MACHINE_CPUARCH}/include machine

CLEANFILES+=	machine

.include <bsd.lib.mk>

beforedepend ${OBJS}: machine
