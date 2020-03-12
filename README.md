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

## Installation via Packages

On Arch Linux, you can install the `clipnotify` package.

## Manual installation

First you need to make sure "XFixes.h" is already installed. On Debian-derived systems,
this is located in the package `libxfixes-dev`.


    git clone https://github.com/cdown/clipnotify.git
    cd clipnotify
    make
    sudo make install

The final step will install the `clipnotify` binary at `/usr/bin/clipnotify`.
