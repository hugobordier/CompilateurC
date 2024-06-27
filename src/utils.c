#include "utils.h"

const char* tokenTypeToString(TokenType type) {
    switch (type) {
        case TOKEN_TYPE_NOMBRE: return "nombre";
        case TOKEN_TYPE_REEL: return "reel";
        case TOKEN_TYPE_LETTRES: return "lettres";
        case TOKEN_TYPE_LETTRE: return "lettre";
        case TOKEN_TYPE_BOOLEAN: return "boolean";
        default: return "unknown";
    }
}
