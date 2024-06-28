#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_EOF,//0
    TOKEN_IDENT,//1
    TOKEN_NOMBRE,
    TOKEN_REEL,
    TOKEN_STRING,
    TOKEN_LETTRE,//5
    TOKEN_LETTRES,
    TOKEN_BOOLEAN,

    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_ELSEIF,//10
    TOKEN_FOR,
    TOKEN_WHILE,
    TOKEN_TRY,
    TOKEN_CATCH,
    TOKEN_FONCTION,//15

    TOKEN_TYPE_NOMBRE,
    TOKEN_TYPE_REEL,
    TOKEN_TYPE_LETTRES,
    TOKEN_TYPE_LETTRE,
    TOKEN_TYPE_BOOLEAN,//20

    TOKEN_PLUS,
    TOKEN_MOINS,
    TOKEN_FOIS,
    TOKEN_DIVISION,
    TOKEN_PUISSANCE,//25
    TOKEN_MODULO,
    TOKEN_ASSIGNATION,
    TOKEN_EGALITE,
    TOKEN_DIFFERENT,
    TOKEN_ET,//30
    TOKEN_OU,

    TOKEN_PAR_OUVRANTE,
    TOKEN_PAR_FERMANTE,
    TOKEN_ACCO_OUVRANTE,
    TOKEN_ACCO_FERMANTE,//35
    TOKEN_CROCHET_OUVRANT,
    TOKEN_CROCHET_FERMANT,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_COMM,//40
    TOKEN_UNKNOWN,
} TokenType;





typedef struct {
    TokenType type;
    char *value;
} Token;

Token getNextToken(const char *source, int *index);
void printLexer(const char *source);
Token *tokenize(const char* source);

#endif 
