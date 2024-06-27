#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h" 
typedef struct Symbol {
    char *name;
    ASTNodeType type;  
    TokenType data_type; 
    struct Symbol *next;  
} Symbol;

void addSymbol(char *name, ASTNodeType type, TokenType data_type);

int symbolExists(char *name);

ASTNodeType getSymbolType(char *name);

void freeSymbolTable();

void analyzeSemantics(ASTNode *root);

#endif
