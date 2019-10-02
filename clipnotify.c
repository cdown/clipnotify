#include <stdio.h>
#include <stdlib.h>

#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>

int main(void) {
    Display *display = XOpenDisplay(NULL);

    if (!display) {
        fprintf(stderr, "Can't open X display\n");
        return EXIT_FAILURE;
    }

    XEvent event;
    Window root         = DefaultRootWindow(display);
    Atom   xa_clipboard = XInternAtom(display, "CLIPBOARD", False);

    XFixesSelectSelectionInput(display, root, XA_PRIMARY,   XFixesSetSelectionOwnerNotifyMask);
    XFixesSelectSelectionInput(display, root, xa_clipboard, XFixesSetSelectionOwnerNotifyMask);

    XNextEvent(display, &event);
    XCloseDisplay(display);

    return EXIT_SUCCESS;
}
