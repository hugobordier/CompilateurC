#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct {
    Token *tokens;
    int currentTokenIndex;
} Parser;

Parser createParser(const char *source);
void destroyParser(Parser *parser);
Token getCurrentToken(Parser *parser);
void advance(Parser *parser);
ASTNode *parse(Parser *parser);
void printAST(ASTNode *node, int level);

#endif
