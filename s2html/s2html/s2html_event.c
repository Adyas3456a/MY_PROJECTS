#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "s2html_event.h"

#define SIZE_OF_SYMBOLS (sizeof(symbols))
#define SIZE_OF_OPERATORS (sizeof(operators))
#define WORD_BUFF_SIZE	100
#define PEVENT_DATA_SIZE 1024

/********** Forward Declarations **********/
pevent_t * pstate_idle_handler(FILE *fd, int ch);
pevent_t * pstate_single_line_comment_handler(FILE *fd, int ch);
pevent_t * pstate_multi_line_comment_handler(FILE *fd, int ch);
pevent_t * pstate_numeric_constant_handler(FILE *fd, int ch);
pevent_t * pstate_string_handler(FILE *fd, int ch);
pevent_t * pstate_header_file_handler(FILE *fd, int ch);
pevent_t * pstate_ascii_char_handler(FILE *fd, int ch);
pevent_t * pstate_reserve_keyword_handler(FILE *fd, int ch);
pevent_t * pstate_preprocessor_directive_handler(FILE *fd, int ch);
pevent_t * pstate_sub_preprocessor_main_handler(FILE *fd, int ch);

typedef enum {
	PSTATE_IDLE,
	PSTATE_PREPROCESSOR_DIRECTIVE,
	PSTATE_SUB_PREPROCESSOR_MAIN,
	PSTATE_SUB_PREPROCESSOR_RESERVE_KEYWORD,
	PSTATE_SUB_PREPROCESSOR_ASCII_CHAR,
	PSTATE_HEADER_FILE,
	PSTATE_RESERVE_KEYWORD,
	PSTATE_NUMERIC_CONSTANT,
	PSTATE_STRING,
	PSTATE_SINGLE_LINE_COMMENT,
	PSTATE_MULTI_LINE_COMMENT,
	PSTATE_ASCII_CHAR
} pstate_e;

static pstate_e state = PSTATE_IDLE;
static pstate_e state_sub = PSTATE_SUB_PREPROCESSOR_MAIN;
static pevent_t pevent_data;
static int event_data_idx = 0;
static char word[WORD_BUFF_SIZE];
static int word_idx = 0;

static char* res_kwords_data[] = {"const", "volatile", "extern", "auto", "register",
    "static", "signed", "unsigned", "short", "long", "double", "char", "int", "float", "struct", 
    "union", "enum", "void", "typedef", ""};

static char* res_kwords_non_data[] = {"goto", "return", "continue", "break", "if", "else", 
    "for", "while", "do", "switch", "case", "default", "sizeof", ""};


static int is_reserved_keyword(char *word) {
	int idx = 0;
	while (*res_kwords_data[idx]) {
		if (strcmp(res_kwords_data[idx++], word) == 0)
			return RES_KEYWORD_DATA;
	}
	idx = 0;
	while (*res_kwords_non_data[idx]) {
		if (strcmp(res_kwords_non_data[idx++], word) == 0)
			return RES_KEYWORD_NON_DATA;
	}
	return 0;
}

static void set_parser_event(pstate_e s, pevent_e e) {
	pevent_data.data[event_data_idx] = '\0';
	pevent_data.length = event_data_idx;
	event_data_idx = 0;
	state = s;
	pevent_data.type = e;
}

pevent_t * pstate_idle_handler(FILE *fd, int ch) {
	int pre_ch;
	switch (ch) {
		case '\'':
			state = PSTATE_ASCII_CHAR;
			pevent_data.data[event_data_idx++] = ch;
			break;
		case '"':
			state = PSTATE_STRING;
			pevent_data.data[event_data_idx++] = ch;
			break;
		case '#':
			state = PSTATE_PREPROCESSOR_DIRECTIVE;
			pevent_data.data[event_data_idx++] = ch;
			break;
		case '0' ... '9':
			state = PSTATE_NUMERIC_CONSTANT;
			pevent_data.data[event_data_idx++] = ch;
			break;
		case '/':
			pre_ch = ch;
			if ((ch = fgetc(fd)) == '*') {
				if (event_data_idx) {
					fseek(fd, -2L, SEEK_CUR);
					set_parser_event(PSTATE_IDLE, PEVENT_REGULAR_EXP);
					return &pevent_data;
				}
				state = PSTATE_MULTI_LINE_COMMENT;
				pevent_data.data[event_data_idx++] = pre_ch;
				pevent_data.data[event_data_idx++] = ch;
			}
			else if (ch == '/') {
				if (event_data_idx) {
					fseek(fd, -2L, SEEK_CUR);
					set_parser_event(PSTATE_IDLE, PEVENT_REGULAR_EXP);
					return &pevent_data;
				}
				state = PSTATE_SINGLE_LINE_COMMENT;
				pevent_data.data[event_data_idx++] = pre_ch;
				pevent_data.data[event_data_idx++] = ch;
			}
			else {
				pevent_data.data[event_data_idx++] = pre_ch;
				pevent_data.data[event_data_idx++] = ch;
			}
			break;
		case 'a' ... 'z':
		case 'A' ... 'Z':
		case '_':
			word[word_idx++] = ch;
			pevent_data.data[event_data_idx++] = ch;
			state = PSTATE_RESERVE_KEYWORD;
			break;
		default:
			if (event_data_idx > 0) {
				ungetc(ch, fd);
				pevent_data.data[event_data_idx] = '\0';
				set_parser_event(PSTATE_IDLE, PEVENT_REGULAR_EXP);
				return &pevent_data;
			} else {
				pevent_data.data[event_data_idx++] = ch;
				pevent_data.data[event_data_idx] = '\0';
				set_parser_event(PSTATE_IDLE, PEVENT_REGULAR_EXP);
				return &pevent_data;
			}
		
	}
	return NULL;
}

pevent_t * pstate_string_handler(FILE *fd, int ch) {
	if (event_data_idx < PEVENT_DATA_SIZE - 1)
		pevent_data.data[event_data_idx++] = ch;

	if (ch == '"') {
		pevent_data.data[event_data_idx] = '\0';
		set_parser_event(PSTATE_IDLE, PEVENT_STRING);
		return &pevent_data;
	}
	return NULL;
}


pevent_t * pstate_numeric_constant_handler(FILE *fd, int ch) {
	if (isdigit(ch) || ch == '.' || ch == 'x' || isalpha(ch)) {
		pevent_data.data[event_data_idx++] = ch;
	} else {
		ungetc(ch, fd);
		pevent_data.data[event_data_idx] = '\0';
		set_parser_event(PSTATE_IDLE, PEVENT_NUMERIC_CONSTANT);
		return &pevent_data;
	}
	return NULL;
}

pevent_t * pstate_reserve_keyword_handler(FILE *fd, int ch) {
	if (isalnum(ch) || ch == '_') {
		word[word_idx++] = ch;
		pevent_data.data[event_data_idx++] = ch;
	} else {
		word[word_idx] = '\0';
		int kw_type = is_reserved_keyword(word);
		word_idx = 0;
		ungetc(ch, fd);
		pevent_data.data[event_data_idx] = '\0';
		if (kw_type) {
			pevent_data.property = kw_type;
			set_parser_event(PSTATE_IDLE, PEVENT_RESERVE_KEYWORD);
			return &pevent_data;
		} else {
			set_parser_event(PSTATE_IDLE, PEVENT_REGULAR_EXP);
			return &pevent_data;
		}
	}
	return NULL;
}

pevent_t * pstate_header_file_handler(FILE *fd, int ch) {
    pevent_data.data[event_data_idx++] = ch;

    if ((pevent_data.data[0] == '<' && ch == '>') ||
        (pevent_data.data[0] == '"' && ch == '"')) {
        pevent_data.property = (ch == '>') ? STD_HEADER_FILE : USER_HEADER_FILE;

        // Strip outer brackets before storing
        pevent_data.data[event_data_idx] = '\0';
        memmove(pevent_data.data, pevent_data.data + 1, event_data_idx - 2);
        pevent_data.data[event_data_idx - 2] = '\0';
        pevent_data.length = event_data_idx - 2;

        set_parser_event(PSTATE_IDLE, PEVENT_HEADER_FILE);
        return &pevent_data;
    }

    return NULL;
}


pevent_t * pstate_ascii_char_handler(FILE *fd, int ch) {
	pevent_data.data[event_data_idx++] = ch;
	if (ch == '\'') {
		pevent_data.data[event_data_idx] = '\0';
		set_parser_event(PSTATE_IDLE, PEVENT_ASCII_CHAR);
		return &pevent_data;
	}
	return NULL;
}

pevent_t *pstate_sub_preprocessor_main_handler(FILE *fd, int ch) {
    if (ch == '\"' || ch == '<') {
        pevent_data.data[event_data_idx] = '\0';
        set_parser_event(PSTATE_HEADER_FILE, PEVENT_PREPROCESSOR_DIRECTIVE);

        // Save directive data and return it
        static pevent_t directive_event;
        directive_event = pevent_data;

        // Prepare for header file next
        event_data_idx = 0;
        pevent_data.data[event_data_idx++] = ch;
        state = PSTATE_HEADER_FILE;

        // Return directive event now, header will be picked up next loop
        return &directive_event;
    }

    pevent_data.data[event_data_idx++] = ch;
    if (ch == '\n') {
        pevent_data.data[event_data_idx] = '\0';
        set_parser_event(PSTATE_IDLE, PEVENT_PREPROCESSOR_DIRECTIVE);
        return &pevent_data;
    }

    return NULL;
}


pevent_t * pstate_preprocessor_directive_handler(FILE *fd, int ch) {
	switch (state_sub) {
		case PSTATE_SUB_PREPROCESSOR_MAIN:
			return pstate_sub_preprocessor_main_handler(fd, ch);
		default:
			state = PSTATE_IDLE;
			break;
	}
	return NULL;
}

pevent_t *get_parser_event(FILE *fd) {
	int ch;
	pevent_t *evptr = NULL;
	while ((ch = fgetc(fd)) != EOF) {
		switch (state) {
			case PSTATE_IDLE:
				if ((evptr = pstate_idle_handler(fd, ch)) != NULL)
					return evptr;
				break;
			case PSTATE_SINGLE_LINE_COMMENT:
				if ((evptr = pstate_single_line_comment_handler(fd, ch)) != NULL)
					return evptr;
				break;
			case PSTATE_MULTI_LINE_COMMENT:
				if ((evptr = pstate_multi_line_comment_handler(fd, ch)) != NULL)
					return evptr;
				break;
			case PSTATE_PREPROCESSOR_DIRECTIVE:
				if ((evptr = pstate_preprocessor_directive_handler(fd, ch)) != NULL)
					return evptr;
				break;
			case PSTATE_RESERVE_KEYWORD:
				if ((evptr = pstate_reserve_keyword_handler(fd, ch)) != NULL)
					return evptr;
				break;
			case PSTATE_NUMERIC_CONSTANT:
				if ((evptr = pstate_numeric_constant_handler(fd, ch)) != NULL)
					return evptr;
				break;
			case PSTATE_STRING:
				if ((evptr = pstate_string_handler(fd, ch)) != NULL)
					return evptr;
				break;
			case PSTATE_HEADER_FILE:
				if ((evptr = pstate_header_file_handler(fd, ch)) != NULL)
					return evptr;
				break;
			case PSTATE_ASCII_CHAR:
				if ((evptr = pstate_ascii_char_handler(fd, ch)) != NULL)
					return evptr;
				break;
			default:
				state = PSTATE_IDLE;
				break;
		}
	}
	// Flush any unfinished string at EOF
	switch (state) {
		case PSTATE_STRING:
			pevent_data.data[event_data_idx] = '\0';
			set_parser_event(PSTATE_IDLE, PEVENT_STRING);
			return &pevent_data;
		case PSTATE_NUMERIC_CONSTANT:
			pevent_data.data[event_data_idx] = '\0';
			set_parser_event(PSTATE_IDLE, PEVENT_NUMERIC_CONSTANT);
			return &pevent_data;
		case PSTATE_ASCII_CHAR:
			pevent_data.data[event_data_idx] = '\0';
			set_parser_event(PSTATE_IDLE, PEVENT_ASCII_CHAR);
			return &pevent_data;
		case PSTATE_RESERVE_KEYWORD:
			word[word_idx] = '\0';
			int kw_type = is_reserved_keyword(word);
			pevent_data.data[event_data_idx] = '\0';
			pevent_data.property = kw_type;
			set_parser_event(PSTATE_IDLE, kw_type ? PEVENT_RESERVE_KEYWORD : PEVENT_REGULAR_EXP);
			return &pevent_data;
		case PSTATE_PREPROCESSOR_DIRECTIVE:
			pevent_data.data[event_data_idx] = '\0';
			set_parser_event(PSTATE_IDLE, PEVENT_PREPROCESSOR_DIRECTIVE);
			return &pevent_data;
		case PSTATE_HEADER_FILE:
			pevent_data.data[event_data_idx] = '\0';
			set_parser_event(PSTATE_IDLE, PEVENT_HEADER_FILE);
			return &pevent_data;
		default:
			break;
	}

	// Final EOF event
	set_parser_event(PSTATE_IDLE, PEVENT_EOF);
	return &pevent_data;

}

pevent_t * pstate_single_line_comment_handler(FILE *fd, int ch) {
	pevent_data.data[event_data_idx++] = ch;
	if (ch == '\n') {
		pevent_data.data[event_data_idx] = '\0';
		set_parser_event(PSTATE_IDLE, PEVENT_SINGLE_LINE_COMMENT);
		return &pevent_data;
	}
	return NULL;
}

pevent_t * pstate_multi_line_comment_handler(FILE *fd, int ch) {
	pevent_data.data[event_data_idx++] = ch;
	if (ch == '*') {
		int next = fgetc(fd);
		if (next == '/') {
			pevent_data.data[event_data_idx++] = next;
			pevent_data.data[event_data_idx] = '\0';
			set_parser_event(PSTATE_IDLE, PEVENT_MULTI_LINE_COMMENT);
			return &pevent_data;
		} else {
			ungetc(next, fd);
		}
	}
	return NULL;
}
