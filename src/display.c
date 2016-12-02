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
