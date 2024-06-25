#include "semantic.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Table des symboles
Symbol *symbolTable = NULL;

// Ajouter un symbole à la table des symboles
void addSymbol(char *name, NodeType type, TokenType data_type) {
    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
    symbol->name = strdup(name);
    symbol->type = type;
    symbol->data_type = data_type;
    symbol->next = symbolTable;
    symbolTable = symbol;
}

// Vérifier si un symbole existe dans la table des symboles
int symbolExists(char *name) {
    Symbol *current = symbolTable;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return 1; // Le symbole existe
        }
        current = current->next;
    }
    return 0; // Le symbole n'existe pas
}

// Obtenir le type d'un symbole
NodeType getSymbolType(char *name) {
    Symbol *current = symbolTable;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current->type;
        }
        current = current->next;
    }
    return NODE_UNKNOWN; // Symbole non trouvé (type inconnu)
}

// Libérer la mémoire utilisée par la table des symboles
void freeSymbolTable() {
    Symbol *current = symbolTable;
    while (current != NULL) {
        Symbol *temp = current;
        current = current->next;
        free(temp->name);
        free(temp);
    }
    symbolTable = NULL;
}

// Analyse sémantique
void analyzeSemantics(ASTNode *root) {
    while (root != NULL) {
        switch (root->type) {
            case NODE_VAR_DECL:
                if (symbolExists(root->data.var_decl.var_name)) {
                    printf("Erreur : Redéclaration de la variable %s\n", root->data.var_decl.var_name);
                    exit(1);
                }
                addSymbol(root->data.var_decl.var_name, NODE_VAR_DECL, root->data.var_decl.var_type);
                break;
            case NODE_FUNC_DECL:
                if (symbolExists(root->data.func_decl.func_name)) {
                    printf("Erreur : Redéclaration de la fonction %s\n", root->data.func_decl.func_name);
                    exit(1);
                }
                addSymbol(root->data.func_decl.func_name, NODE_FUNC_DECL, TOKEN_UNKNOWN); // Type de fonction inconnu
                break;
            case NODE_FUNC_CALL:
                if (!symbolExists(root->data.func_call.func_name)) {
                    printf("Erreur : Appel de fonction non déclarée : %s\n", root->data.func_call.func_name);
                    exit(1);
                }
                break;
            case NODE_ASSIGN:
                if (!symbolExists(root->data.assign.var_name)) {
                    printf("Erreur : Assignation à une variable non déclarée : %s\n", root->data.assign.var_name);
                    exit(1);
                }
                // Vérifier la compatibilité des types pour l'assignation, par exemple
                break;
            // ... autres cas à gérer selon les nœuds de l'AST
            default:
                break;
        }
        root = root->next;
    }
}
