#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

static FILE *src = NULL;
static int currentChar = ' ';

static const char* keywords[MAX_KEYWORDS] = {
    "int", "float", "return", "if", "else", "while", "for", "do", "break", "continue",
    "char", "double", "void", "switch", "case", "default", "const", "static", "sizeof", "struct"
};

static const char* operators = "+-*/%=!<>|&";
static const char* specialCharacters = ",;{}()[]";

void initializeLexer(const char* filename) {
    src = fopen(filename, "r");
    if (!src) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    currentChar = fgetc(src);
}

static void skipWhitespace() {
    while (isspace(currentChar)) {
        currentChar = fgetc(src);
    }
}

static int isKeyword(const char* str) {
    for (int i = 0; i < MAX_KEYWORDS; i++) {
        if (keywords[i] && strcmp(str, keywords[i]) == 0) return 1;
    }
    return 0;
}

Token getNextToken() {
    Token token;
    memset(&token, 0, sizeof(Token));
    skipWhitespace();

    if (currentChar == EOF) {
        token.type = END_OF_FILE;
        strcpy(token.lexeme, "EOF");
        return token;
    }
    

    if (isalpha(currentChar) || currentChar == '_') {
        int i = 0;
        while (isalnum(currentChar) || currentChar == '_') {
            token.lexeme[i++] = currentChar;
            currentChar = fgetc(src);
        }
        token.lexeme[i] = '\0';
        token.type = isKeyword(token.lexeme) ? KEYWORD : IDENTIFIER;
        return token;
    }

    if (isdigit(currentChar)) {
        int i = 0;
        while (isdigit(currentChar)) {
            token.lexeme[i++] = currentChar;
            currentChar = fgetc(src);
        }
        token.lexeme[i] = '\0';
        token.type = CONSTANT;
        return token;
    }

    if (currentChar == '\"') {
        int i = 0;
        token.lexeme[i++] = currentChar;
        currentChar = fgetc(src);
        while (currentChar != '\"' && currentChar != EOF) {
            token.lexeme[i++] = currentChar;
            currentChar = fgetc(src);
        }
        token.lexeme[i++] = '\"';
        token.lexeme[i] = '\0';
        currentChar = fgetc(src);
        token.type = STRING_LITERAL;
        return token;
    }

    if (strchr(operators, currentChar)) {
        token.lexeme[0] = currentChar;
        token.lexeme[1] = '\0';
        token.type = OPERATOR;
        currentChar = fgetc(src);
        return token;
    }

    if (strchr(specialCharacters, currentChar)) {
        token.lexeme[0] = currentChar;
        token.lexeme[1] = '\0';
        token.type = SPECIAL_CHARACTER;
        currentChar = fgetc(src);
        return token;
    }

    token.lexeme[0] = currentChar;
    token.lexeme[1] = '\0';
    token.type = UNKNOWN;
    currentChar = fgetc(src);
    return token;
}
