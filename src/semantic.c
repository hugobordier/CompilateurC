#include "semantic.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYMBOL_TABLE_SIZE 100

Symbol symbolTable[SYMBOL_TABLE_SIZE];
int symbolCount = 0;

void addSymbol(char *name, ASTNodeType type, TokenType data_type) {
    if (symbolCount < SYMBOL_TABLE_SIZE) {
        Symbol *symbol = &symbolTable[symbolCount++];
        symbol->name = strdup(name);
        symbol->type = type;
        symbol->data_type = data_type;
    } else {
        printf("Symbol table overflow\n");
    }
}

Symbol *findSymbol(char *name) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return &symbolTable[i];
        }
    }
    return NULL;
}

void printSymbolTable() {
    printf("Symbol Table:\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("Name: %s, Type: %d, Data Type: %d\n", symbolTable[i].name,
               symbolTable[i].type, symbolTable[i].data_type);
    }
}

void analyzeAST(ASTNode *root) {
    if (root == NULL) {
        return;
    }

    switch (root->type) {
    case AST_IDENTIFIER: {
        Symbol *symbol = findSymbol(root->data.identifier);
        if (symbol == NULL) {
            printf("Semantic Error: Undefined variable '%s'\n",
                   root->data.identifier);
        }
        break;
    }
    case AST_ASSIGNMENT: {
        Symbol *symbol = findSymbol(root->data.assignment.name);
        if (symbol == NULL) {
            printf("Semantic Error: Undefined variable '%s'\n",
                   root->data.assignment.name);
        } else {
            // Analyser le nœud de la valeur assignée
            analyzeAST(root->data.assignment.value);
            // Vérifier la compatibilité des types si nécessaire
        }
        break;
    }
    case AST_FUNCTION_CALL: {
        Symbol *symbol = findSymbol(root->data.function_call.name);
        if (symbol == NULL) {
            printf("Semantic Error: Undefined function '%s'\n",
                   root->data.function_call.name);
        } else {
            // Vérifier le nombre et le type des arguments
            for (int i = 0; i < root->data.function_call.num_args; i++) {
                analyzeAST(root->data.function_call.args[i]);
                // Vérifier la compatibilité des types si nécessaire
            }
        }
        break;
    }
    // Ajoute d'autres cas selon les types de nœuds nécessaires
    default:
        break;
    }

    // Analyser récursivement les enfants
    for (int i = 0; i < root->childrenCount; i++) {
        analyzeAST(root->children[i]);
    }
}
