#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"

ASTNode *parseProgram(Token *tokens);
ASTNode *parseStatement(Token *tokens, int *index);
ASTNode *parseExpression(Token *tokens, int *index);
ASTNode *parseAssignment(Token *tokens, int *index);
ASTNode *parseConditional(Token *tokens, int *index);
ASTNode *parsePrimary(Token *tokens, int *index);

#endif
