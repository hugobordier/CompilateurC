#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h" // Inclure ast.h pour avoir la définition de NodeType

// Structure pour représenter un symbole (variable ou fonction)
typedef struct Symbol {
    char *name;
    NodeType type;  // Type du symbole (variable, fonction, etc.)
    TokenType data_type;  // Type de données (int, float, etc.) pour les variables
    struct Symbol *next;  // Pointeur vers le prochain symbole dans la table des symboles
} Symbol;

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
