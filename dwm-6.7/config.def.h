/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=12" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1, col_gray3 },
};

/* staticstatus */
static const int statmonval = 0;

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor    scratch key */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1,        0  },
	{ "firefox",  NULL,       NULL,       0,            0,           -1,        0  },
	{ NULL,        NULL,   "scratchpad",   0,           1,           -1,       't' },
  { NULL,        NULL,   "ncmpcpp",      0,           1,           -1,       'm' },
	{ NULL,        NULL,   "nvim",         0,           1,           -1,       'n' },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

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
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_gray1, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *webcmd[] = {"firefox", NULL };
static const char *filescmd[] = {"st", "-e", "lf", NULL };

/*First arg only serves to match against key in rules*/
static const char *sptermcmd[] = {"t", "st", "-t", "scratchpad", "-g", "144x41", NULL };
static const char *spncmpcppcmd[] = {"m", "st", "-t", "ncmpcpp", "-g", "144x41", "-e", "ncmpcpp", NULL };
static const char *spdailynotecmd[] = {"n", "st", "-t", "nvim", "-g", "144x41", "-e", "nvim", NULL };
static const char *qalc_cmd[] = {"dmenu", "-C", "-p", "Qalc:", NULL};

#include "movestack.c"
#include "exitdwm.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = webcmd } },
  { MODKEY,                       XK_f,      spawn,          {.v = filescmd } },
  { MODKEY|ShiftMask,             XK_Return, togglescratch,  {.v = sptermcmd } }, /* terminal scratchpad */
  { MODKEY|ShiftMask,             XK_m,      togglescratch,  {.v = spncmpcppcmd } }, /* ncmpcpp scratchpad */
  { MODKEY|ShiftMask,             XK_n,      togglescratch,  {.v = spdailynotecmd } }, /* ncmpcpp scratchpad */
	{ MODKEY|ControlMask,           XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
/*{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },*/
/*{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },*/
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
/*{ MODKEY,                       XK_Return, zoom,           {0} },*/
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ 0,                            XK_Print,  spawn,          SHCMD("scrot ~/Pictures/screenshots/%Y%m%d_%H%M%S.png && notify-send" "'Screenshot taken'") },
  { ShiftMask,                    XK_Print,  spawn,          SHCMD("scrot -s ~/Pictures/screenshots/%Y%m%d_%H%M%S.png && notify-send"  "'Screenshot taken'") },
  { MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("slock") },
  { MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("colourpicker.sh") },
  { MODKEY|ShiftMask,             XK_c,      spawn,          {.v = qalc_cmd } },
  { 0,                            XF86XK_MonBrightnessUp, spawn, SHCMD("brightnessctl set +10%") },
  { 0,                            XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl set 10%-") },
  { MODKEY,                       XK_F1,     spawn,          SHCMD("volume.sh mute") },
  { MODKEY,                       XK_F2,     spawn,          SHCMD("volume.sh down") },
  { MODKEY,                       XK_F3,     spawn,          SHCMD("volume.sh up") },
  { 0,                            XF86XK_AudioPlay, spawn,   SHCMD("mpc toggle") },
  { 0,                            XF86XK_AudioPrev, spawn,   SHCMD("mpc prev") },
  { 0,                            XF86XK_AudioNext, spawn,   SHCMD("mpc next") },
  { 0,                            XF86XK_AudioStop, spawn,   SHCMD("mpc stop") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      exitdwm,        {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
  { ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
  { ClkStatusText,        ShiftMask,      Button1,        sigstatusbar,   {.i = 6} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
