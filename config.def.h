/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
    "AurulentSansMono Nerd Font:style=Regular:size=9",
    "ProggyCleanTT Nerd Font:style=Book:size=12",
    "Iosevka Nerd Font:style=Medium:size=10",
    "Estrangelo Edessa:style=Regular:size=12",
    "Berthold Akzidenz Grotesk:style=Medium:size=9",
    "Slate Pro:style=Regular:size=12",
    "NanumGothicCoding:size=11",
    "Quattrocento Sans:style=Regular:size=12",
    "ABeeZee:size=10",
    "Inconsolata:size=9",
    "VL Gothic:size=10.5",  
    "WenQuanYi Micro Hei:size=10.5",
};
#define NUMCOLORS         2
static const char colors[NUMCOLORS][MAXCOLORS][8] = {
  // border     foreground   background
  { "#2d2d2d", "#ffffff",   "#111111" },  // normal
  { "#4d4d4d", "#ffffff",   "#222222" },  // selected
};
static const char dmenufont[] = "AurulentSansMono Nerd Font:style=Regular:size=9";
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, 0: display systray on the last monitor*/
static const int showsystray        = 0;        /* 0 means no systray */

static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = {"\ue795 tmux", "\uf268 net", "\uf40e dev", "\uf1c5 files", "\u2665"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	/*
  { "Gimp",     NULL,       NULL,       0,            False,        -1 },

  { "Firefox",  NULL,       NULL,       1<<1,         False,        -1 },

  { "Navigator", 
                NULL,       NULL,       1<<1,         False,        -1 },

  { "Main.py",  NULL,       NULL,       0,            True,         -1 },*/

  { "Google-chrome",
                NULL,       NULL,       1<<1,         False,        -1 },

  { "Google-chrome-stable",
                NULL,       NULL,       1<<1,         False,        -1 },

  { "Google-chrome-unstable",
                NULL,       NULL,       1<<1,         False,        -1 },

  /*
  { "Linuxdcpp",
                NULL,       NULL,       1<<0,         False,        -1 },*/

  { "Vlc",      NULL,       NULL,       1<<4,         True,         -1 },

  { "Pcmanfm",  NULL,       NULL,       1<<3,         False,        -1 },

  { "gnome-terminal-server",
                NULL,       NULL,       1<<0,         False,        -1 },

  /*
  { "urxvt",    NULL,       NULL,       0,            True,         -1 },

  { "Lyx",      NULL,       NULL,       1<<3,         False,        -1 }*/

};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "ti",      tile },    /* no layout function means floating behavior */
  { "fl",      NULL },    /* first entry is default */
	{ "fu",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *fmcmd[] = {"urxvt", "-e", "/bin/sh", "-c", "ranger", NULL};
static const char *chromecmd[] = {"firefox", NULL};
static const char *dccmd[] = {"linuxdcpp", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
  { MODKEY,                       XK_e,      spawn,          {.v = fmcmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = chromecmd} },
  { MODKEY,                       XK_q,      spawn,          {.v = dccmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ Mod4Mask,                     XK_space,  spawn,          {.v = dmenucmd} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

