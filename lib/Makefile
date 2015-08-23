.include <src.opts.mk>


LIB=		omap4
INTERNALLIB=
WARNS?=		2

SRCS+=	platform.c clock.c emif.c
SRCS+=	printf.c console.c uart_ns16550.c
SRCS+=	init.c

ACFLAGS+= -D__ASSEMBLY__

CFLAGS+= -ffreestanding -msoft-float -Os

LDFLAGS+= -nostdlib -static

CFLAGS+= -I${.CURDIR}/../include/ -I.

machine:
	ln -sf ${.CURDIR}/../../../../${MACHINE_CPUARCH}/include machine

CLEANFILES+=	machine

.include <bsd.lib.mk>

beforedepend ${OBJS}: machine
