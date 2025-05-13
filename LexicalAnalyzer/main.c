#include <stdio.h>
#include <string.h>
#include "lexer.h"

const char* tokenTypeToString(TokenType type) {
    switch(type) {
        case KEYWORD: return "Keyword";
        case IDENTIFIER: return "Identifier";
        case OPERATOR: return "Operator";
        case CONSTANT: return "Literal";
        case STRING_LITERAL: return "Literal";
        case SPECIAL_CHARACTER: return "Operator";
        case END_OF_FILE: return "EndOfFile";
        default: return "Unknown";
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("\nUsage: %s <.c file>\n\n", argv[0]);
        return 1;
    }

    // Header style output
    printf("Open        :   %s   :    Success\n", argv[1]);
    printf("Parsing     :   %s   :    Started\n\n", argv[1]);

    // Token output
    initializeLexer(argv[1]);
    Token token;
    while ((token = getNextToken()).type != END_OF_FILE) {
        printf("%-18s :   %s\n", tokenTypeToString(token.type), token.lexeme);
    }

    // Parsing completion footer
    printf("\nParsing     :   %s   :    Done\n\n", argv[1]);
    return 0;
}
