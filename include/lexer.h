#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_EOF,
    TOKEN_IDENT,
    TOKEN_NOMBRE,
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
    TOKEN_ASSIGNATION,
    TOKEN_DIFFERENT,
    TOKEN_ET,
    TOKEN_OU,
    TOKEN_STRING,
    TOKEN_PAR_OUVRANTE,
    TOKEN_PAR_FERMANTE,
    TOKEN_ACCO_OUVRANTE,
    TOKEN_ACCO_FERMANTE,
    TOKEN_CROCHET_OUVRANT,
    TOKEN_CROCHET_FERMANT,
    TOKEN_SEMICOLON,
    TOKEN_COMMA
} TokenType;


typedef struct {
    TokenType type;
    char *value;
} Token;

Token getNextToken(const char *source, int *index);
void printLexer(const char *source);

#endif // LEXER_H
