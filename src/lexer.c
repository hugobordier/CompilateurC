#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

Token getNextToken(const char *source, int *index) {
    while (isspace(source[*index])) (*index)++;
    if (source[*index] == '\0') return (Token){TOKEN_EOF, NULL};

    if (isdigit(source[*index])) {
        int start = *index;
        while (isdigit(source[*index])) (*index)++;
        char *text = strndup(&source[start], *index - start);
        return (Token){TOKEN_NOMBRE, text};
    }

    if (isalpha(source[*index])) {
        int start = *index;
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
        case '=': (*index)++; return (Token){TOKEN_EGALITE, strndup("=", 1)};
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
    }

    (*index)++;
    return (Token){TOKEN_IDENT, strndup("UNKNOWN", 7)};
}
