#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Display *disp;
    Window root;
    Atom clip;
    XEvent evt;

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
