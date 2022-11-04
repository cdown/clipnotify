#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static enum selections {
    NONE = 0,
    SELECTION_CLIPBOARD = (1 << 0),
    SELECTION_PRIMARY = (1 << 1),
    SELECTION_SECONDARY = (1 << 2)
} selections = NONE;

int main(int argc, char *argv[]) {
    static const char *usage =
        "clipnotify: Notify on clipboard events.\n\n"
        "  -s    The selection to use. Available selections:\n"
        "        clipboard, primary, secondary\n"
        "        The default is to monitor clipboard and primary.\n";
    Display *disp;
    Window root;
    Atom clip;
    XEvent evt;
    int opt;

    while ((opt = getopt(argc, argv, "hs:")) != -1) {
        switch (opt) {
            case 'h':
                printf(usage, argv[0]);
                return EXIT_SUCCESS;
            case 's': {
                char *token = strtok(optarg, ",");
                while (token != NULL) {
                    if (strcmp(token, "clipboard") == 0) {
                        selections |= SELECTION_CLIPBOARD;
                    } else if (strcmp(token, "primary") == 0) {
                        selections |= SELECTION_PRIMARY;
                    } else if (strcmp(token, "secondary") == 0) {
                        selections |= SELECTION_SECONDARY;
                    } else {
                        fprintf(stderr, "Unknown selection '%s'\n", token);
                        return EXIT_FAILURE;
                    }
                    token = strtok(NULL, ",");
                }
                break;
            }
            default:
                fprintf(stderr, usage, argv[0]);
                return EXIT_FAILURE;
        }
    }

    disp = XOpenDisplay(NULL);
    if (!disp) {
        fprintf(stderr, "Can't open X display\n");
        return EXIT_FAILURE;
    }

    root = DefaultRootWindow(disp);

    clip = XInternAtom(disp, "CLIPBOARD", False);

    /* <= 1.0.2 backwards compatibility */
    if (!selections)
        selections = SELECTION_CLIPBOARD | SELECTION_PRIMARY;

    if (selections & SELECTION_CLIPBOARD)
        XFixesSelectSelectionInput(disp, root, clip,
                                   XFixesSetSelectionOwnerNotifyMask);
    if (selections & SELECTION_PRIMARY)
        XFixesSelectSelectionInput(disp, root, XA_PRIMARY,
                                   XFixesSetSelectionOwnerNotifyMask);
    if (selections & SELECTION_SECONDARY)
        XFixesSelectSelectionInput(disp, root, XA_SECONDARY,
                                   XFixesSetSelectionOwnerNotifyMask);

    XNextEvent(disp, &evt);
    XCloseDisplay(disp);
}
