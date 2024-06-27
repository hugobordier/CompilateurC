#include "lexer.h"
#include <ctype.h> // for is...()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token getNextToken(const char *source, int *index) {
    while (isspace(source[*index])) {
        (*index)++;
    } // ignore spaces

    if (source[*index] == '\0')
        return (Token){TOKEN_EOF, NULL};

    if (isdigit(source[*index])) {
        int start = *index;
        while (isdigit(source[*index]))
            (*index)++;
        if (source[*index] == '.')
            (*index)++; // look a the decimal part for a float
        while (isdigit(source[*index]))
            (*index)++;
        char *text = strndup(&source[start], *index - start);
        if (strchr(text, '.') != NULL) {
            return (Token){TOKEN_REEL, text};
        } else {
            return (Token){TOKEN_NOMBRE, text};
        }
    }

    if (source[*index] == '"') {
        int start = ++(*index);
        while (source[*index] != '"' && source[*index] != '\0')
            (*index)++;
        if (source[*index] == '"') {
            char *text = strndup(&source[start], *index - start);
            (*index)++;
            return (Token){TOKEN_STRING, text};
        }
    }

    if (source[*index] == '\'') {
        (*index)++;
        char *text = strndup(&source[*index], 1);
        (*index)++;
        if (source[*index] == '\'')
            (*index)++;
        return (Token){TOKEN_LETTRE, text};
    }

    if (isalpha(source[*index])) {
        int start = *index;
        while (isalnum(source[*index]))
            (*index)++;
        char *text = strndup(&source[start], *index - start);

        // Check for types
        if (strcmp(text, "nombre") == 0)
            return (Token){TOKEN_TYPE_NOMBRE, text};
        if (strcmp(text, "reel") == 0)
            return (Token){TOKEN_TYPE_REEL, text};
        if (strcmp(text, "lettres") == 0)
            return (Token){TOKEN_TYPE_LETTRES, text};
        if (strcmp(text, "lettre") == 0)
            return (Token){TOKEN_TYPE_LETTRE, text};
        if (strcmp(text, "boolean") == 0)
            return (Token){TOKEN_TYPE_BOOLEAN, text};

        // Check for keywords
        if (strcmp(text, "si") == 0)
            return (Token){TOKEN_IF, text};
        if (strcmp(text, "sinon") == 0)
            return (Token){TOKEN_ELSE, text};
        if (strcmp(text, "aussisi") == 0)
            return (Token){TOKEN_ELSEIF, text};
        if (strcmp(text, "pour") == 0)
            return (Token){TOKEN_FOR, text};
        if (strcmp(text, "tantque") == 0)
            return (Token){TOKEN_WHILE, text};
        if (strcmp(text, "essaie") == 0)
            return (Token){TOKEN_TRY, text};
        if (strcmp(text, "attrape") == 0)
            return (Token){TOKEN_CATCH, text};
        if (strcmp(text, "fonction") == 0)
            return (Token){TOKEN_FONCTION, text};

        return (Token){TOKEN_IDENT, text};
    }

    // other sprecial tokens
    switch (source[*index]) {
    case '+':
        (*index)++;
        return (Token){TOKEN_PLUS, strndup("+", 1)};
    case '-':
        (*index)++;
        return (Token){TOKEN_MOINS, strndup("-", 1)};
    case '*':
        (*index)++;
        return (Token){TOKEN_FOIS, strndup("*", 1)};
    case '^':
        (*index)++;
        return (Token){TOKEN_PUISSANCE, strndup("^", 1)};
    case '%':
        (*index)++;
        return (Token){TOKEN_MODULO, strndup("%", 1)};
    case '/':
        (*index)++;
        if (source[*index] == '/') {
            (*index)++;
            return (Token){TOKEN_COMM, strndup("//", 2)};
        }
        return (Token){TOKEN_DIVISION, strndup("/", 1)};
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
    case '(':
        (*index)++;
        return (Token){TOKEN_PAR_OUVRANTE, strndup("(", 1)};
    case ')':
        (*index)++;
        return (Token){TOKEN_PAR_FERMANTE, strndup(")", 1)};
    case '{':
        (*index)++;
        return (Token){TOKEN_ACCO_OUVRANTE, strndup("{", 1)};
    case '}':
        (*index)++;
        return (Token){TOKEN_ACCO_FERMANTE, strndup("}", 1)};
    case '[':
        (*index)++;
        return (Token){TOKEN_CROCHET_OUVRANT, strndup("[", 1)};
    case ']':
        (*index)++;
        return (Token){TOKEN_CROCHET_FERMANT, strndup("]", 1)};
    case ';':
        (*index)++;
        return (Token){TOKEN_SEMICOLON, strndup(";", 1)};
    case ',':
        (*index)++;
        return (Token){TOKEN_COMMA, strndup(",", 1)};
    }

    (*index)++;
    return (Token){TOKEN_IDENT, strndup("UNKNOWN", 7)};
}

void printLexer(const char *source) {
    int index = 0;
    Token token;

    while ((token = getNextToken(source, &index)).type != TOKEN_EOF) {
        printf("Token Type: %d, Token Value: %s\n", token.type, token.value);
        free(token.value);
    }
}

Token *tokenize(const char *source) {
    int index = 0;
    int capacity = 10; // initial capacity for tokens array
    int size = 0;      // current size of tokens array
    Token *tokens = malloc(capacity * sizeof(Token));

    if (!tokens) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Loop through the source string and tokenize
    while (1) {
        // Get the next token
        Token token = getNextToken(source, &index);

        // Check if we need to resize tokens array
        if (size >= capacity) {
            capacity *= 2;
            tokens = realloc(tokens, capacity * sizeof(Token));
            if (!tokens) {
                fprintf(stderr, "Memory reallocation failed.\n");
                exit(EXIT_FAILURE);
            }
        }

        // Add token to tokens array
        tokens[size++] = token;

        // Check for end of source
        if (token.type == TOKEN_EOF) {
            break;
        }
    }

    // Resize tokens array to actual size
    tokens = realloc(tokens, size * sizeof(Token));

    return tokens;
}