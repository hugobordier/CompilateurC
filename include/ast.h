#ifndef AST_H
#define AST_H

#include "lexer.h"
typedef enum {
    NODE_UNKNOWN,       
    NODE_VAR_DECL,
    NODE_FUNC_DECL,
    NODE_FUNC_CALL,
    NODE_ASSIGN,
    NODE_BINARY_OP,
    NODE_LITERAL,
    NODE_RETURN,
    NODE_COMMENT,
    NODE_ARRAY_DECL,
    NODE_ARRAY_ACCESS,
    NODE_BLOCK,
} NodeType;
typedef struct ASTNode {
    NodeType type; // Type du nœud
    union {
        // Déclaration de variable
        struct {
            char *var_name;
            TokenType var_type;
        } var_decl;

        // Déclaration de tableau
        struct {
            char *array_name;
            TokenType elem_type;
            struct ASTNode *size; // Expression de taille (facultative)
        } array_decl;

        // Accès au tableau
        struct {
            char *array_name;
            struct ASTNode *index; // Expression d'index
        } array_access;

        // Déclaration de fonction
        struct {
            char *func_name;
            struct ASTNode *params; // Liste des paramètres
            struct ASTNode *body; // Corps de la fonction
        } func_decl;

        // Appel de fonction
        struct {
            char *func_name;
            struct ASTNode *args; // Liste des arguments
        } func_call;

        // Affectation
        struct {
            char *var_name;
            struct ASTNode *value; // Valeur à affecter
        } assign;

        // Opération binaire
        struct {
            struct ASTNode *left; // Opérande gauche
            struct ASTNode *right; // Opérande droite
            TokenType op; // Type de l'opération
        } binary_op;

        // Littéral
        struct {
            Token value; // Valeur littérale
        } literal;

        // Commentaire
        struct {
            char *text; // Texte du commentaire
        } comment;

        // Retour
        struct {
            struct ASTNode* expr; // Expression de retour
        } return_stmt;
    } data;

    struct ASTNode *next; // Pointeur vers le nœud suivant pour les listes de nœuds
} ASTNode;

// Fonction pour imprimer l'AST
void printAST(ASTNode *root);

#endif
