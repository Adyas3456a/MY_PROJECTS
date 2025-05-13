#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "s2html_event.h"
#include "s2html_conv.h"

void html_begin(FILE* dest_fp, int type) {
    fprintf(dest_fp, "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n");
    fprintf(dest_fp, "<meta charset=\"UTF-8\">\n<title>source2html</title>\n");
    fprintf(dest_fp, "<link rel=\"stylesheet\" href=\"styles.css\">\n");
    fprintf(dest_fp, "</head>\n<body style=\"background-color:lightgrey;\">\n<pre>\n");
}

void html_end(FILE* dest_fp, int type) {
    fprintf(dest_fp, "</pre>\n</body>\n</html>\n");
}

void source_to_html(FILE* fp, pevent_t *event) {
    switch (event->type) {
        case PEVENT_PREPROCESSOR_DIRECTIVE:
            if (strncmp(event->data, "#define", 7) == 0) {
                fprintf(fp, "<span class='preprocess_dir'>#define</span>");

                const char* rest = event->data + 7;
                while (*rest == ' ' || *rest == '\t') rest++; // skip whitespace

                if (*rest) {
                    fprintf(fp, " <span class='header_file'>%s</span>", rest);
                }
            } else {
                fprintf(fp, "<span class='preprocess_dir'>%s</span>", event->data);
            }
            break;


        case PEVENT_HEADER_FILE:
            if (event->property == USER_HEADER_FILE)
                fprintf(fp, "<span class='header_file'>&quot;%s&quot;</span>", event->data);
            else
                fprintf(fp, "<span class='header_file'>&lt;%s&gt;</span>", event->data);
            break;

        case PEVENT_MULTI_LINE_COMMENT:
        case PEVENT_SINGLE_LINE_COMMENT:
            fprintf(fp, "<span class='comment'>%s</span>", event->data); break;
        case PEVENT_STRING:
            fprintf(fp, "<span class='string'>%s</span>", event->data); break;
        case PEVENT_NUMERIC_CONSTANT:
            fprintf(fp, "<span class='numeric_constant'>%s</span>", event->data); break;
        case PEVENT_RESERVE_KEYWORD:
            fprintf(fp, "<span class='%s'>%s</span>",
                    (event->property == RES_KEYWORD_DATA ? "reserved_key1" : "reserved_key2"),
                    event->data);
            break;
        case PEVENT_ASCII_CHAR:
            fprintf(fp, "<span class='ascii_char'>%s</span>", event->data); break;
        case PEVENT_REGULAR_EXP:
        case PEVENT_EOF:
        default:
            fprintf(fp, "%s", event->data); break;
    }
}
