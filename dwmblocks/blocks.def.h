static const Block blocks[] = {
    /* Icon          Command                          Update Interval  Update Signal */
    {"",    "~/Scripts/music",            1,             11}, // 1 second interval for music
    {"",    "~/Scripts/drives",              30,            0},
    {"",    "~/Scripts/cpu",                 10,            18},
    {"",    "~/Scripts/memory",              10,            14},
    {"",    "~/Scripts/weather",             18000,         5},
    {"",    "date '+%a %b %d %I:%M%p '",     5,             0},
};

static char delim[] = "\0";  // Null delimiter, no separator between commands
static unsigned int delimLen = 5;
