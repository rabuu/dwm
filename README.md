![dwm](dwm.png)
# dwm - dynamic window manager
dwm is an extremely fast, small, and dynamic window manager for X.


### Requirements
In order to build dwm you need the Xlib header files.


### Installation
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

`make clean install`


### Running dwm
Add the following line to your .xinitrc to start dwm using startx:

`exec dwm`

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

`DISPLAY=foo.bar:1 exec dwm`

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

```
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
	sleep 1
done &
exec dwm
```

### Configuration
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.


## edit by rabuu
Font, colors and other settings can be defined in Xresources with:
- dwm.normbordercolor
- dwm.normbgcolor
- dwm.normfgcolor
- dwm.selbordercolor
- dwm.selbgcolor
- dwm.selfgcolor
- dwm.borderpx
- dwm.snap
- dwm.showbar
- dwm.topbar
- dwm.nmaster
- dwm.resizehints
- dwm.mfact
- dwm.mainfont
- dwm.gappx

As standard font JetBrains Mono is set. Unless you set a own font you need to install it.<br>
`$TERMINAL` and `$BROWSER` must be set.<br>
For some commands you need to have the appropriate programs installed.<br>
For some commands you need to have a script ([my dotfiles](https://github.com/rabuu/dotfiles)).<br>

### used patches
- [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/dwm-actualfullscreen-20191112-cb3f58a.diff)
- [alwaysfullscreen](https://dwm.suckless.org/patches/alwaysfullscreen/dwm-alwaysfullscreen-6.1.diff)
- [cfacts](https://dwm.suckless.org/patches/cfacts/dwm-cfacts-20200913-61bb8b2.diff)
- [status2d](https://dwm.suckless.org/patches/status2d/dwm-status2d-20200508-60bb3df.diff)
- [sticky](https://dwm.suckless.org/patches/sticky/dwm-sticky-6.1.diff)
	- [stickyindicator](https://dwm.suckless.org/patches/stickyindicator/dwm-stickyindicator-6.2.diff)
- [swallow](https://dwm.suckless.org/patches/swallow/dwm-swallow-20201211-61bb8b2.diff)
- [tilegap](https://dwm.suckless.org/patches/tilegap/dwm-tilegap-6.2.diff)
- [tcl (Three Column Layout)](https://dwm.suckless.org/patches/three-column/)
- [xresources](https://dwm.suckless.org/patches/xresources/dwm-xresources-6.2.diff)
