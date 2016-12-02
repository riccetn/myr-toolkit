#ifndef MYR_DISPLAY_X11_H
#define MYR_DISPLAY_X11_H

#include "display.h"

#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>

MyrDisplay *myr_display_create_with_xcb_connection(xcb_connection_t *xcon, int screennr);

xcb_connection_t *myr_display_get_xcb_display(MyrDisplay *disp);
int myr_display_get_screen_number(MyrDisplay *disp);
xcb_screen_t *myr_display_get_xcb_screen(MyrDisplay *disp);
xcb_ewmh_connection_t *myr_display_get_xcb_ewmh_connection(MyrDisplay *disp);

#endif
