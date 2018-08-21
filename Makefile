all:
	${CC} ${CFLAGS} ${LDFLAGS} clipnotify.c -o clipnotify -lX11 -lXfixes
