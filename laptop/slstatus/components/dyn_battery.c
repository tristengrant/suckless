/* Written by Madison Lynch <madi@mxdi.xyz> */
/* Only Linux is supported */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "../slstatus.h"

#define BAT_PREFIX "BAT"
#define BAT_DIR "/sys/class/power_supply"

/**
* Counts number of batteries detected by system.
*
* @return unsigned integer denoting the number of detected batteries.
* @author Madison Lynch
*/
static unsigned int
battery_count(void) {
    DIR *dir = opendir(BAT_DIR);
    unsigned int bat_c = 0;

    struct dirent *entry;
    while((entry = readdir(dir)))
        if(strlen(entry->d_name) > 3)
            if(strncmp(entry->d_name, BAT_PREFIX, 3) == 0)
                bat_c++;

    (void) closedir(dir);
    return bat_c;
}

/**
* Displays the status and capacity of a dynamic amount of batteries (i.e.
* laptop may have secondary external battery).
*
* @param  fmt format string to use for each battery display. ordered key:
*             %u: battery number || %s: battery state || %s battery capacity
* @return string containing the status and capacities of all detected batteries
* @author Madison Lynch
*/
const char *
dyn_battery(const char *fmt) {
    static char *ret;
    free(ret); // Free address from previous output

    const size_t fmt_s = strlen(fmt);
    const unsigned int bat_c = battery_count();

    // Extra byte in calloc() for null byte
    ret = (char *)calloc(fmt_s * bat_c + 1, sizeof(char));
    if(!ret) {
        fprintf(stderr, "dyn_battery: calloc() failed.");
        return NULL;
    }

    unsigned int displacement = 0; // For appending battery displays
    for(unsigned int i=0; i<bat_c; i++) {
        char bat[7]; // "BAT" = 3 + <=3 digit number + null byte
        (void) sprintf(bat, "BAT%u", i);

        // Add battery display to final string to be returned
        (void) sprintf(
            ret + displacement,
            fmt,
            i,
            battery_state(bat),
            battery_perc(bat)
        );
        displacement = strlen(ret);

        // Add space between battery displays
        ret[displacement++] = ' ';
    }

    // Remove extra space after last battery display
    ret[--displacement] = '\0';

    return ret;
}

#undef BAT_DIR
#undef BAT_PREFIX
