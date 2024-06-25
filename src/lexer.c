#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Token getNextToken(const char *source, int *index) {
    while (isspace(source[*index])) { (*index)++; } // Ignorer les espaces

    // Fin du fichier
    if (source[*index] == '\0') return (Token){TOKEN_EOF, NULL};

    // Si c'est un nombre (int) ou réel (float)
    if (isdigit(source[*index])) {
        int start = *index;
        while (isdigit(source[*index])) (*index)++;
        if (source[*index] == '.') (*index)++; // Vérifier la partie décimale pour le réel
        while (isdigit(source[*index])) (*index)++;
        char *text = strndup(&source[start], *index - start);
        if (strchr(text, '.') != NULL) {
            return (Token){TOKEN_REEL, text};
        } else {
            return (Token){TOKEN_NOMBRE, text};
        }
    }

    // Si c'est une chaîne de caractères
    if (source[*index] == '"') {
        int start = ++(*index);
        while (source[*index] != '"' && source[*index] != '\0') (*index)++;
        if (source[*index] == '"') {
            char *text = strndup(&source[start], *index - start);
            (*index)++;
            return (Token){TOKEN_STRING, text};
        }
    }

    // Si c'est un caractère (lettre)
    if (source[*index] == '\'') {
        (*index)++;
        char *text = strndup(&source[*index], 1);
        (*index)++;
        if (source[*index] == '\'') (*index)++;
        return (Token){TOKEN_LETTRE, text};
    }

    // Si c'est un mot-clé ou un identifiant
    if (isalpha(source[*index])) {
        int start = *index;
        while (isalnum(source[*index])) (*index)++;
        char *text = strndup(&source[start], *index - start);

        // Vérifier les mots-clés pour les types de données
        if (strcmp(text, "nombre") == 0) return (Token){TOKEN_NOMBRE, text};
        if (strcmp(text, "reel") == 0) return (Token){TOKEN_REEL, text};
        if (strcmp(text, "lettres") == 0) return (Token){TOKEN_LETTRES, text};
        if (strcmp(text, "lettre") == 0) return (Token){TOKEN_LETTRE, text};
        if (strcmp(text, "tableau") == 0) return (Token){TOKEN_TYPE_TABLEAU, text};
        if (strcmp(text, "boolean") == 0) return (Token){TOKEN_BOOLEAN, text};

        // Vérifier les mots-clés pour les instructions conditionnelles et les boucles
        if (strcmp(text, "si") == 0) return (Token){TOKEN_IF, text};
        if (strcmp(text, "sinon") == 0) return (Token){TOKEN_ELSE, text};
        if (strcmp(text, "aussisi") == 0) return (Token){TOKEN_ELSEIF, text};
        if (strcmp(text, "pour") == 0) return (Token){TOKEN_FOR, text};
        if (strcmp(text, "tantque") == 0) return (Token){TOKEN_WHILE, text};
        if (strcmp(text, "essaie") == 0) return (Token){TOKEN_TRY, text};
        if (strcmp(text, "attrape") == 0) return (Token){TOKEN_CATCH, text};

        // Sinon, c'est un identifiant
        return (Token){TOKEN_IDENT, text};
    }

    // Autres tokens spéciaux
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

void printLexer(const char *source) {
    int index = 0;
    Token token;

    while ((token = getNextToken(source, &index)).type != TOKEN_EOF) {
        printf("Token Type: %d, Token Value: %s\n", token.type, token.value);
        free(token.value);
    }
}
