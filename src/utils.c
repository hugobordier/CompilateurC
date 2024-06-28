#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *tokenTypeToString(TokenType type) {
    switch (type) {
    case TOKEN_TYPE_NOMBRE:
        return "nombre";
    case TOKEN_TYPE_REEL:
        return "reel";
    case TOKEN_TYPE_LETTRES:
        return "lettres";
    case TOKEN_TYPE_LETTRE:
        return "lettre";
    case TOKEN_TYPE_BOOLEAN:
        return "boolean";
    default:
        return "unknown";
    }
}

char *charArrayToString(char array[]) {
    size_t length = strlen(array);
    char *str = (char *)malloc(length + 1);

    if (str == NULL) {
        printf("Allocation error in charArrayToString\n");
        return NULL;
    }

    strcpy(str, array);
    return str;
}
