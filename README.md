clipnotify is a simple program that, using the
[XFIXES](https://cgit.freedesktop.org/xorg/proto/fixesproto/plain/fixesproto.txt)
extension to X11, waits until a new selection is available and then exits.

It was primarily designed for [clipmenu](https://github.com/cdown/clipmenu), to
avoid polling for new selections.

Here's how it's intended to be used:

    while clipnotify; do
        [an event happened, do something with the selection]
    done

clipnotify doesn't try to print anything about the contents of the selection,
it just exits when it changes. This is intentional -- X11's selection API is
verging on the insane, and there are plenty of others who have already lost
their sanity to bring us xclip/xsel/etc. Use one of those tools to complement
clipnotify.
