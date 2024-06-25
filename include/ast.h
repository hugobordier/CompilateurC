#ifndef AST_H
#define AST_H

#include "lexer.h"

typedef enum {
    NODE_UNKNOWN,       // Noeud inconnu ou non spécifié
    NODE_VAR_DECL,
    NODE_FUNC_DECL,
    NODE_FUNC_CALL,
    NODE_ASSIGN,
    NODE_BINARY_OP,
    NODE_LITERAL,
    // ... d'autres types de nœuds
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        // Déclarations de variable
        struct {
            char *var_name;
            TokenType var_type;
        } var_decl;
        // Déclarations de fonction
        struct {
            char *func_name;
            struct ASTNode *params;
            struct ASTNode *body;
        } func_decl;
        // Appels de fonction
        struct {
            char *func_name;
            struct ASTNode *args;
        } func_call;
        // Affectations
        struct {
            char *var_name;
            struct ASTNode *value;
        } assign;
        // Opérations binaires
        struct {
            struct ASTNode *left;
            struct ASTNode *right;
            TokenType op;
        } binary_op;
        // Littéraux
        struct {
            Token value;
        } literal;
        // ... d'autres structures de nœuds
    } data;
    struct ASTNode *next; // Pour les listes de nœuds
} ASTNode;

void printAST(ASTNode *root);

#endif // AST_H
