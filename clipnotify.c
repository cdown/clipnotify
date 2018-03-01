#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    Display *disp;
    Window root;
    Atom clip;
    XEvent evt;

    // Parse and validate flags
    int disablePrimary = 0;
    for (int i = 1; i < argc; i++) {
        int disPrimary = (
            strcmp(argv[i], "-P") == 0 || 
            strcmp(argv[i], "--disable-primary") == 0
        );

        if (disPrimary) {
            disablePrimary = 1;
        } else {
            fprintf(stderr, "Unrecognized option: %s\n", argv[i]);
            exit(1);
        }
    }

    disp = XOpenDisplay(NULL);
    if (!disp) {
        fprintf(stderr, "Can't open X display\n");
        exit(1);
    }

    root = DefaultRootWindow(disp);
    clip = XInternAtom(disp, "CLIPBOARD", False);

    if (!disablePrimary) {
        XFixesSelectSelectionInput(disp, root, XA_PRIMARY, XFixesSetSelectionOwnerNotifyMask);
    }

    XFixesSelectSelectionInput(disp, root, clip, XFixesSetSelectionOwnerNotifyMask);

    XNextEvent(disp, &evt);
    XCloseDisplay(disp);
}
