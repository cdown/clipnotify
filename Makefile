x11_bsd_flags = -I/usr/X11R6/include -L/usr/X11R6/lib

all:
	${CC} ${CFLAGS} ${LDFLAGS} clipnotify.c -o clipnotify $(x11_bsd_flags) -lX11 -lXfixes

install: all
	cp clipnotify /usr/local/bin

uninstall:
	rm /usr/local/bin/clipnotify

clean:
	rm -f *.o *~ clipnotify
