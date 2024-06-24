#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_NOMBRE,
    TOKEN_IDENT,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_ELSEIF,
    TOKEN_FOR,
    TOKEN_WHILE,
    TOKEN_TRY,
    TOKEN_CATCH,
    TOKEN_PLUS,
    TOKEN_MOINS,
    TOKEN_FOIS,
    TOKEN_DIVISION,
    TOKEN_PUISSANCE,
    TOKEN_MODULO,
    TOKEN_EGALITE,
    TOKEN_DIFFERENT,
    TOKEN_ET,
    TOKEN_OU,
    TOKEN_EOF,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

Token getNextToken(const char *source, int *index);

#endif // LEXER_H
