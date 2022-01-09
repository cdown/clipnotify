#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alloca.h>

/* USE_FD - unix only, set aside stdout stream medium, using its file descriptor directly. */

#ifdef USE_UNLOCKED_IO
/* Nothing against this attempt, at least for now. */
    #define f_fwrite fwrite_unlocked
    #define f_fileno fileno_unlocked
#else
    #define f_fwrite fwrite
    #define f_fileno fileno
#endif

#ifdef USE_ALLOCA
/* At user's risk. Should be little to no problem in our case. */
    #define f_alloc alloca
#else
    #define f_alloc malloc
#endif

int main(int argc, char **argv) {
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
    if (argc > 1) {
        ////////////////////////////

        //~ while (1) {
            //~ printf ("%s\n", argv[1]);
            //~ XNextEvent(disp, &evt);
        //~ }

        ////////////////////////////

        //~ while (1) {
            //~ dprintf (2, "%s\n", argv[1]);            
            //~ XNextEvent(disp, &evt);
        //~ }

        ////////////////////////////

        #ifdef USE_FD
            int outd = f_fileno(stdout);
        #endif

        int s_len = strlen(argv[1]);
        char *buf = f_alloc(s_len + 1);
        memcpy(buf, argv[1], s_len);
        buf[s_len++] = '\n';
        while (1) {
            #ifdef USE_FD
                #include <unistd.h>
                write(outd, buf, s_len);
            #else
                f_fwrite(buf, s_len, 1, stdout);
            #endif
            XNextEvent(disp, &evt);
        }
    }
    XCloseDisplay(disp);
}
