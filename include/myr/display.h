#ifndef MYR_DISPLAY_H
#define MYR_DISPLAY_H

typedef struct myr_display MyrDisplay;

MyrDisplay *myr_display_open(void);
void myr_display_ref(MyrDisplay *disp);
void myr_display_unref(MyrDisplay *disp);

#endif
