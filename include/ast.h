#ifndef AST_H
#define AST_H

#include "lexer.h"

typedef enum {
    NODE_VAR_DECL,
    NODE_ASSIGNMENT,
    NODE_FUNCTION_CALL,
    NODE_EXPRESSION,
    NODE_IF_STATEMENT,
    NODE_WHILE_STATEMENT,
    NODE_FOR_STATEMENT,
    NODE_FUNCTION_DECL,
    NODE_RETURN_STATEMENT,
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    union {
        struct {
            TokenType var_type;
            char *var_name;
            struct ASTNode *initial_value;
        } var_decl;
        struct {
            char *var_name;
            struct ASTNode *value;
        } assignment;
        struct {
            char *function_name;
            struct ASTNode **arguments;
            int arg_count;
        } function_call;
        struct {
            struct ASTNode *condition;
            struct ASTNode *then_branch;
            struct ASTNode *else_branch;
        } if_statement;
        struct {
            struct ASTNode *condition;
            struct ASTNode *body;
        } while_statement;
        struct {
            struct ASTNode *initializer;
            struct ASTNode *condition;
            struct ASTNode *increment;
            struct ASTNode *body;
        } for_statement;
        struct {
            char *function_name;
            struct ASTNode **parameters;
            int param_count;
            struct ASTNode *body;
        } function_decl;
        struct {
            struct ASTNode *return_value;
        } return_statement;
        // Ajoutez d'autres structures de nœuds si nécessaire
    } data;
    struct ASTNode *next;
} ASTNode;

ASTNode *createNode(ASTNodeType type);
void printASTNode(ASTNode *node);

#endif
