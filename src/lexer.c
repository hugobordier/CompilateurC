#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

Token getNextToken(const char *source, int *index) {
    while (isspace(source[*index])) {(*index)++;}; //if is space
    if (source[*index] == '\0') return (Token){TOKEN_EOF, NULL};

    if (isdigit(source[*index])) { // if is digit
        int start = *index;
        while (isdigit(source[*index])) (*index)++;
        char *text = strndup(&source[start], *index - start);
        return (Token){TOKEN_NOMBRE, text};
    }

    if (isalpha(source[*index])) { // if is char
        int start = *index; //set the first character of the token
        while (isalnum(source[*index])) (*index)++;
        char *text = strndup(&source[start], *index - start);

        if (strcmp(text, "si") == 0) return (Token){TOKEN_IF, text};
        if (strcmp(text, "sinon") == 0) return (Token){TOKEN_ELSE, text};
        if (strcmp(text, "aussisi") == 0) return (Token){TOKEN_ELSEIF, text};
        if (strcmp(text, "pour") == 0) return (Token){TOKEN_FOR, text};
        if (strcmp(text, "tantque") == 0) return (Token){TOKEN_WHILE, text};
        if (strcmp(text, "essaie") == 0) return (Token){TOKEN_TRY, text};
        if (strcmp(text, "attrape") == 0) return (Token){TOKEN_CATCH, text};

        return (Token){TOKEN_IDENT, text};
    }

    switch (source[*index]) {
        case '+': (*index)++; return (Token){TOKEN_PLUS, strndup("+", 1)};
        case '-': (*index)++; return (Token){TOKEN_MOINS, strndup("-", 1)};
        case '*': (*index)++; return (Token){TOKEN_FOIS, strndup("*", 1)};
        case '/': (*index)++; return (Token){TOKEN_DIVISION, strndup("/", 1)};
        case '^': (*index)++; return (Token){TOKEN_PUISSANCE, strndup("^", 1)};
        case '%': (*index)++; return (Token){TOKEN_MODULO, strndup("%", 1)};
        case '=':
            (*index)++;
            if (source[*index] == '=') {
                (*index)++;
                return (Token){TOKEN_EGALITE, strndup("==", 2)};
            }
            return (Token){TOKEN_ASSIGNATION, strndup("=", 1)};
        case '!': 
            (*index)++;
            if (source[*index] == '=') {
                (*index)++;
                return (Token){TOKEN_DIFFERENT, strndup("!=", 2)};
            }
            break;
        case '&':
            (*index)++;
            if (source[*index] == '&') {
                (*index)++;
                return (Token){TOKEN_ET, strndup("&&", 2)};
            }
            break;
        case '|':
            (*index)++;
            if (source[*index] == '|') {
                (*index)++;
                return (Token){TOKEN_OU, strndup("||", 2)};
            }
            break;
        case '"': {
            int start = ++(*index);
            while (source[*index] != '"' && source[*index] != '\0') (*index)++;
            if (source[*index] == '"') {
                char *text = strndup(&source[start], *index - start);
                (*index)++;
                return (Token){TOKEN_STRING, text};
            }
            break;
        }
        case '(': (*index)++; return (Token){TOKEN_PAR_OUVRANTE, strndup("(", 1)};
        case ')': (*index)++; return (Token){TOKEN_PAR_FERMANTE, strndup(")", 1)};
        case '{': (*index)++; return (Token){TOKEN_ACCO_OUVRANTE, strndup("{", 1)};
        case '}': (*index)++; return (Token){TOKEN_ACCO_FERMANTE, strndup("}", 1)};
        case '[': (*index)++; return (Token){TOKEN_CROCHET_OUVRANT, strndup("[", 1)};
        case ']': (*index)++; return (Token){TOKEN_CROCHET_FERMANT, strndup("]", 1)};
        case ';': (*index)++; return (Token){TOKEN_SEMICOLON, strndup(";", 1)};
        case ',': (*index)++; return (Token){TOKEN_COMMA, strndup(",", 1)};
    }

    (*index)++;
    return (Token){TOKEN_IDENT, strndup("UNKNOWN", 7)};
}
