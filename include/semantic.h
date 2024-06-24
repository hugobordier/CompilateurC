#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"

// Structure pour représenter un symbole (variable ou fonction)
typedef struct Symbol {
    char *name;
    NodeType type;  // Type du symbole (variable, fonction, etc.)
    TokenType data_type;  // Type de données (int, float, etc.) pour les variables
    struct Symbol *next;  // Pointeur vers le prochain symbole dans la table des symboles
} Symbol;

typedef enum {
    NODE_UNKNOWN,       // Noeud inconnu ou non spécifié
    NODE_VAR_DECL,      // Déclaration de variable
    NODE_FUNC_DECL,     // Déclaration de fonction
    NODE_FUNC_CALL,     // Appel de fonction
    NODE_ASSIGN,        // Assignation
    NODE_BINARY_OP,     // Opération binaire
    NODE_LITERAL        // Littéral
    // Ajoute d'autres types de nœuds au besoin
} NodeType;

// Fonction pour ajouter un symbole à la table des symboles
void addSymbol(char *name, NodeType type, TokenType data_type);

// Fonction pour vérifier si un symbole existe dans la table des symboles
int symbolExists(char *name);

// Fonction pour obtenir le type d'un symbole (variable, fonction, etc.)
NodeType getSymbolType(char *name);

// Fonction pour libérer la mémoire utilisée par la table des symboles
void freeSymbolTable();

// Fonction pour effectuer l'analyse sémantique sur l'AST
void analyzeSemantics(ASTNode *root);

#endif // SEMANTIC_H
