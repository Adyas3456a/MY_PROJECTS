#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "s2html_event.h"
#include "s2html_conv.h"

int enable_line_number = 0;

int main (int argc, char *argv[])
{
    FILE *sfp, *dfp;
    pevent_t *event;
    char *src_file = NULL, *html_file = NULL;
    int line_number = 1;

    if (argc < 3)
    {
        printf("\nUsage: /source_to_ntml <src_file.c> <output.html> <-n>\n");
        return 1;
    }

    src_file = argv[1];
    html_file = argv[2];
    if (argc == 4 && strcmp(argv[3], "-n") == 0)
        enable_line_number = 1;

    if ((sfp = fopen(src_file, "r")) == NULL)
    {
        printf("Error! File %s could not be opened\n", src_file);
        return 2;
    }

    if ((dfp = fopen(html_file, "w")) == NULL)
    {
        printf("Error! Could not create %s output file\n", html_file);
        fclose(sfp);
        return 3;
    }

    html_begin(dfp, HTML_OPEN);

    // int new_line = 1;  // whether to print line number
	// int ch;

	// do {
	// 	event = get_parser_event(sfp);

	// 	if (event->type == PEVENT_EOF)
	// 		break;

	// 	for (int i = 0; i < event->length; i++) {
	// 		ch = event->data[i];

	// 		// On new line, print the line number
	// 		if (new_line && enable_line_number) {
	// 			fprintf(dfp, "<span class='line-number'>%4d: </span>", line_number++);
	// 			new_line = 0;
	// 		}

	// 		// Output one character with syntax coloring
	// 		char temp[2] = { ch, '\0' };
	// 		pevent_t tmp_event = *event;
	// 		strcpy(tmp_event.data, temp);
	// 		tmp_event.length = 1;

	// 		// Output this single char with its highlighting
	// 		source_to_html(dfp, &tmp_event);

	// 		// If newline, flag that we need to print a new line number next
	// 		if (ch == '\n') {
	// 			new_line = 1;
	// 		}
	// 	}
	// } while (1);
    int new_line = 1;
    do {
        event = get_parser_event(sfp);
        if (event->type == PEVENT_EOF) break;

        int i = 0;
        while (i < event->length) {
            // Add line number if needed
            if (new_line && enable_line_number) {
                fprintf(dfp, "<span class='line-number'>%4d: </span>", line_number++);
                new_line = 0;
            }

            // Find next newline or end
            int start = i;
            while (i < event->length && event->data[i] != '\n') {
                i++;
            }

            // Emit content before newline
            if (i > start) {
                pevent_t temp_event = *event;
                strncpy(temp_event.data, &event->data[start], i - start);
                temp_event.data[i - start] = '\0';
                temp_event.length = i - start;
                source_to_html(dfp, &temp_event);
            }

            // Handle newline
            if (i < event->length && event->data[i] == '\n') {
                fputc('\n', dfp);
                new_line = 1;
                i++;
            }
        }
    } while (1);

    // ✅ Extra flush if no newline at EOF
    if (!new_line && enable_line_number) {
        fputc('\n', dfp);
    }

    html_end(dfp, HTML_CLOSE);

    printf("Conversion to HTML file done successfully\n");

    fclose(sfp);
    fclose(dfp);

    return 0;
}
