all:
	${CC} clipnotify.c -o clipnotify -lX11 -lXfixes
