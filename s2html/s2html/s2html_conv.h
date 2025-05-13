#ifndef S2HTML_CONV_H
#define S2HTML_CONV_H

#define HTML_OPEN   1
#define HTML_CLOSE  0

#include <stdio.h>
#include "s2html_event.h"

void html_begin(FILE* dest_fp, int type);
void html_end(FILE* dest_fp, int type);
void source_to_html(FILE* fp, pevent_t *event);

#endif
