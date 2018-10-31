#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __OpenBSD__
#define MAYBE_PLEDGE(p, ep) pledge(p, ep)
#else
#define MAYBE_PLEDGE(p, ep) 0
#endif /* __OpenBSD__ */

int main(void) {
    Display *disp;
    Window root;
    Atom clip;
    XEvent evt;

    if (MAYBE_PLEDGE("stdio rpath", NULL) < 0) {
        perror("pledge");
        exit(2);
    }

    disp = XOpenDisplay(NULL);
    if (!disp) {
        fprintf(stderr, "Can't open X display\n");
        exit(1);
    }

    root = DefaultRootWindow(disp);

    clip = XInternAtom(disp, "CLIPBOARD", False);

    XFixesSelectSelectionInput(disp, root, XA_PRIMARY, XFixesSetSelectionOwnerNotifyMask);
    XFixesSelectSelectionInput(disp, root, clip, XFixesSetSelectionOwnerNotifyMask);

    XNextEvent(disp, &evt);
    XCloseDisplay(disp);
}
