x11_flags = $(shell pkg-config --cflags --libs x11)

all:
	${CC} ${CFLAGS} ${LDFLAGS} clipnotify.c -o clipnotify $(x11_flags) -lXfixes
