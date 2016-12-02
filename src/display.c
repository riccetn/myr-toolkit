/*
 * Written 2016 by Rickard Närström <rickard@narstrom.se>
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <myr/display.h>
#include <myr/display_x11.h>

#include <stdlib.h>
#include <string.h>

#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <xcb/xcb_util.h>

struct myr_display {
	unsigned refcount;
	xcb_connection_t *xcon;
	int screennr;
	xcb_screen_t *xscreen;
	xcb_ewmh_connection_t xewmh;
};

MyrDisplay *myr_display_open(void) {
	int screennr;
	xcb_connection_t *xcon = xcb_connect(NULL, &screennr);

	return myr_display_create_with_xcb_connection(xcon, screennr);
}

MyrDisplay *myr_display_create_with_xcb_connection(xcb_connection_t *xcon, int screennr) {
	if(!xcon || xcb_connection_has_error(xcon))
		return NULL;

	MyrDisplay *disp = malloc(sizeof *disp);
	if(!disp)
		return NULL;
	memset(disp, '\0', sizeof *disp);

	disp->refcount = 1;
	disp->xcon = xcon;
	disp->screennr = screennr;
	disp->xscreen = xcb_aux_get_screen(disp->xcon, disp->screennr);

	xcb_ewmh_init_atoms_replies(&disp->xewmh, xcb_ewmh_init_atoms(disp->xcon, &disp->xewmh), NULL);

	return disp;
}

void myr_display_ref(MyrDisplay *disp) {
	++disp->refcount;
}
void myr_display_unref(MyrDisplay *disp) {
	if(--disp->refcount != 0)
		return;

	xcb_ewmh_connection_wipe(&disp->ewmh);
	xcb_disconnect(disp->xcon);
	free(disp);
}

int myr_display_get_screen_number(MyrDisplay *disp) {
	return disp->screennr;
}

xcb_screen_t *myr_display_get_xcb_screen(MyrDisplay *disp) {
	return disp->xscreen;
}

xcb_ewmh_connection_t *myr_display_get_xcb_ewmh_connection(MyrDisplay *disp) {
	return &disp->xewmh;
}
