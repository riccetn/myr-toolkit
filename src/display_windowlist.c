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

#include "display_windowlist.h"

#include <stdlib.h>
#include <string.h>

typedef struct node Node;

struct node {
	Node *next;
	MyrWindow *window;
};

struct myr_display_window_list {
	Node *table;
	int nbuckets;
	int nnodes;
};

MyrDisplayWindowList *myr_display_window_list_create(void) {
	MyrDisplayWindowList *list = malloc(sizeof *list);
	if(!list)
		return NULL;
	memset(list, '\0', sizeof *list);

	list->nbuckets = 16;
	list->nnodes = 0;
	list->table = calloc(list->nbuckets, sizeof *list->table);
	if(!list) {
		myr_display_window_list_free(list);
		return NULL;
	}
	return list;
}

void myr_display_window_list_free(MyrDisplayWindowList *list) {
	if(list->table)
		free(list->table);
	free(list);
}

MyrWindow *myr_display_window_list_lookup(MyrDisplayWindowList *list, xcb_window_t xwindowid) {
	return NULL;
}

void myr_display_window_list_add(MyrDisplayWindowList *list, xcb_window_t xwindowid, MyrWindow *window) {
}
