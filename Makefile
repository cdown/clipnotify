PREFIX ?= /usr/local

x11_bsd_flags = -I/usr/X11R6/include -L/usr/X11R6/lib

all:
	${CC} ${CFLAGS} ${LDFLAGS} clipnotify.c -o clipnotify $(x11_bsd_flags) -lX11 -lXfixes

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f clipnotify ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/clipnotify

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/clipnotify

clean:
	rm -f *.o *~ clipnotify
