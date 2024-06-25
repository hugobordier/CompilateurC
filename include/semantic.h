#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h" 
typedef struct Symbol {
    char *name;
    NodeType type;  
    TokenType data_type; 
    struct Symbol *next;  
} Symbol;

void addSymbol(char *name, NodeType type, TokenType data_type);

int symbolExists(char *name);

NodeType getSymbolType(char *name);

void freeSymbolTable();

void analyzeSemantics(ASTNode *root);

#endif
