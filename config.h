/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static unsigned int gappx     = 6;        /* gaps between windows */
static char mainfont[] 				= "JetBrains Mono:size=13";
static const char *fonts[]          = { mainfont };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance 	   title       tags mask     isfloating   monitor */
	{ NULL, 	    NULL,       NULL, 	      0,            0,           0 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) (const char*[]) { "/bin/sh", "-c", cmd, NULL }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] 		  		 = { "dmenu_run", "-m", dmenumon, NULL };
static const char *passmenucmd[]             = { "passmenu", "-p", "Pass", "-l", "2", NULL };
static const char *networkmanagerdmenucmd[]  = { "networkmanager_dmenu", NULL };

static const char *termcmd[]  		= SHCMD("$TERMINAL");
static const char *browsercmd[] 	= SHCMD("$BROWSER");

static const char *slockcmd[]       = { "slock",                    NULL };

static const char *telegramcmd[]    = { "telegram-desktop",         NULL };
static const char *discordcmd[]     = { "discord",                  NULL };
static const char *spotifycmd[]     = { "spotify",                  NULL };

static const char *switchkeyboardlayoutcmd[] = { "switch_keyboard_layout",   NULL };
static const char *volumeupcmd[]             = { "volume_up",                NULL };
static const char *volumedowncmd[]           = { "volume_down",              NULL };
static const char *volumetogglecmd[]         = { "volume_toggle",            NULL };
static const char *microphonetogglecmd[]     = { "microphone_toggle",        NULL };
static const char *brightnessupcmd[]         = { "brightness_up",            NULL };
static const char *brightnessdowncmd[]       = { "brightness_down",          NULL };

static const char *killxorg[]				 = { "pkill", "-15", "Xorg", 	 NULL };


#include <X11/XF86keysym.h>
/* key bindings */
static Key keys[] = {
	/* modifier                     key        function        argument */
	
	/* dmenu prompts */
	{ MODKEY,                         XK_p,                       spawn,            { .v = dmenucmd                } },
	{ MODKEY|ShiftMask,               XK_p,                       spawn,            { .v = passmenucmd             } },
	{ MODKEY|ShiftMask,               XK_n,                       spawn,            { .v = networkmanagerdmenucmd  } },

	/* start program */
	{ MODKEY,                         XK_space,                   spawn,            { .v = slockcmd                } },
	{ MODKEY,                         XK_Return,                  spawn,            { .v = termcmd 				   } },
	{ MODKEY|ShiftMask,               XK_space,                   spawn,            { .v = switchkeyboardlayoutcmd } },
	{ MODKEY|ShiftMask,               XK_b,                       spawn,            { .v = browsercmd              } },
	{ MODKEY|ShiftMask,               XK_t,                       spawn,            { .v = telegramcmd             } },
	{ MODKEY|ShiftMask,               XK_d,                       spawn,            { .v = discordcmd              } },
	{ MODKEY|ShiftMask,               XK_s,                       spawn,            { .v = spotifycmd              } },

	/* quit program */
	{ MODKEY|ShiftMask,               XK_c,                       killclient,       { 0 }                            },

	/* quit dwm */
	{ MODKEY|ShiftMask,               XK_q,                       quit,             { 0 }                            },
	{ MODKEY|ControlMask|ShiftMask,   XK_q,                       spawn,            { .v = killxorg				   } },

	/* media keys */
	{ 0,                              XF86XK_AudioRaiseVolume,    spawn,            { .v = volumeupcmd             } },
	{ 0,                              XF86XK_AudioLowerVolume,    spawn,            { .v = volumedowncmd           } },
	{ 0,                              XF86XK_AudioMute,           spawn,            { .v = volumetogglecmd         } },
	{ 0,                              XF86XK_AudioMicMute,        spawn,            { .v = microphonetogglecmd     } },
	{ 0,                              XF86XK_MonBrightnessUp,     spawn,            { .v = brightnessupcmd         } },
	{ 0,                              XF86XK_MonBrightnessDown,   spawn,            { .v = brightnessdowncmd       } },
	{ 0, 							  XF86XK_Search, 			  spawn,            { .v = dmenucmd                } },

	/* toggle bar */
	{ MODKEY|ControlMask,             XK_b,                       togglebar,        { 0 }                            },

	/* change layout */
	{ MODKEY|ControlMask,             XK_t,      				  setlayout,      	{.v = &layouts[0]} 				 },
	{ MODKEY|ControlMask,             XK_f,      				  setlayout,      	{.v = &layouts[1]} 				 },
	{ MODKEY|ControlMask,             XK_m,      				  setlayout,      	{.v = &layouts[2]} 				 },
	{ MODKEY|ControlMask|ShiftMask,   XK_space,                   togglefloating,   { 0 }                            },
	{ MODKEY|ControlMask,             XK_Return,                  togglefullscr,    { 0 }                            },

	/* resize windows */
	{ MODKEY,                         XK_h,                       setmfact,         { .f = -0.05 }                   },
	{ MODKEY,                         XK_l,                       setmfact,         { .f = +0.05 }                   },
	{ MODKEY,                         XK_o,                       setmfact,         { .f =  0.00 }                   },
	{ MODKEY|ShiftMask,               XK_l,                       setcfact,         { .f = -0.25 }                   },
	{ MODKEY|ShiftMask,               XK_h,                       setcfact,         { .f = +0.25 }                   },
	{ MODKEY|ShiftMask,               XK_o,                       setcfact,         { .f =  0.00 }                   },

	/* reorder windows */
	{ MODKEY|ShiftMask,               XK_Return,                  zoom,             { 0 }                            },

	/* navigate windows */
	{ MODKEY,                         XK_j,                       focusstack,       { .i = +1 }                      },
	{ MODKEY,                         XK_k,                       focusstack,       { .i = -1 }                      },

	/* navigate monitors */
	{ MODKEY,                         XK_comma,                   focusmon,         { .i = -1 }                      },
	{ MODKEY,                         XK_period,                  focusmon,         { .i = +1 }                      },

	/* change monitors */
	{ MODKEY|ShiftMask,               XK_comma,                   tagmon,           { .i = -1 }                      },
	{ MODKEY|ShiftMask,               XK_period,                  tagmon,           { .i = +1 }                      },

	/* change views */
	{ MODKEY,                         XK_Tab,                     view,             { 0 }                            },
	{ MODKEY,                         XK_0,                       view,             { .ui = ~0 }                     },

	/* change tags */
	{ MODKEY|ShiftMask,               XK_0,                       tag,              { .ui = ~0 }                     },
	TAGKEYS(                          XK_1,                       0 )
	TAGKEYS(                          XK_2,                       1 )
	TAGKEYS(                          XK_3,                       2 )
	TAGKEYS(                          XK_4,                       3 )
	TAGKEYS(                          XK_5,                       4 )
	TAGKEYS(                          XK_6,                       5 )
	TAGKEYS(                          XK_7,                       6 )
	TAGKEYS(                          XK_8,                       7 )
	TAGKEYS(                          XK_9,                       8 )

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
		{ "mainfont", 			STRING,  &mainfont },
		{ "gappx", 				INTEGER, &gappx },
};

