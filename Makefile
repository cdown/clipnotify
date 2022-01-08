PREFIX ?= /usr/local

x11_bsd_flags = -I/usr/X11R6/include -L/usr/X11R6/lib

all: clipnotify

clipnotify: clipnotify.c
	${CC} ${CFLAGS} ${LDFLAGS} clipnotify.c -o clipnotify $(x11_bsd_flags) -lX11 -lXfixes

install: all
	install -D -m755 clipnotify ${DESTDIR}${PREFIX}/bin

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/clipnotify

clean:
	rm -f *.o *~ clipnotify
