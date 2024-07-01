#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"

typedef struct {
    Token *tokens;
    int current;
    int count;
} Parser;

Parser* create_parser(Token *tokens, int count);
void free_parser(Parser *parser);
ASTNode* parse_program(Parser *parser);
void print_ast(ASTNode *node, int indent);

#endif
