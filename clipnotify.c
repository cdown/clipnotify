#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>

static enum selections {
    NONE                = 0,
    SELECTION_CLIPBOARD = (1 << 0),
    SELECTION_PRIMARY   = (1 << 1),
    SELECTION_SECONDARY = (1 << 2)
} selections = NONE;

int main(int argc, char *argv[]) {
    static const char USAGE[] = "Usage: %s [-s SELECTION...]\n";

    static const char SEL_OPT_CLIPBOARD[] = "clipboard";
    static const char SEL_OPT_PRIMARY[]   = "primary";
    static const char SEL_OPT_SECONDARY[] = "secondary";

    static const char SEL_OPT_SEPARATOR[] = ",";

    int optchar;
    while ((optchar = getopt(argc, argv, "hs:")) != -1) {
        switch (optchar)
        {
        case 'h':
            printf(USAGE, argv[0]);
            return EXIT_SUCCESS;
        /* We need the pair of braces because C does not allow a declaration after a labeled statement. */
        case 's': {
            char *token = strtok(optarg, SEL_OPT_SEPARATOR);
            while(token != NULL) {
                if (strcmp(token, SEL_OPT_CLIPBOARD) == 0) {
                    selections |= SELECTION_CLIPBOARD;
                } else if (strcmp(token, SEL_OPT_PRIMARY) == 0) {
                    selections |= SELECTION_PRIMARY;
                } else if (strcmp(token, SEL_OPT_SECONDARY) == 0) {
                    selections |= SELECTION_SECONDARY;
                } else {
                    fprintf(stderr, "Unrecognized selection '%s'. Available selections: clipboard, primary.\n", token);
                    return EXIT_FAILURE;
                }
                token = strtok(NULL, SEL_OPT_SEPARATOR);
            }
            break;
        }
        default: /* '?' */
            fprintf(stderr, USAGE, argv[0]);
            return EXIT_FAILURE;
        }
    }
    Display *display = XOpenDisplay(NULL);

    if (!display) {
        fprintf(stderr, "Can't open X display\n");
        return EXIT_FAILURE;
    }

    XEvent event;
    Window root         = DefaultRootWindow(display);
    Atom   xa_clipboard = XInternAtom(display, "CLIPBOARD", False);

    /* Monitor all selections by default if -s was not specified. */
    if (selections == NONE)
        selections = ~selections;

    if (selections & SELECTION_CLIPBOARD)
        XFixesSelectSelectionInput(display, root, xa_clipboard, XFixesSetSelectionOwnerNotifyMask);
    if (selections & SELECTION_PRIMARY)
        XFixesSelectSelectionInput(display, root, XA_PRIMARY,   XFixesSetSelectionOwnerNotifyMask);
    if (selections & SELECTION_SECONDARY)
        XFixesSelectSelectionInput(display, root, XA_SECONDARY, XFixesSetSelectionOwnerNotifyMask);

    XNextEvent(display, &event);
    XCloseDisplay(display);

    return EXIT_SUCCESS;
}
