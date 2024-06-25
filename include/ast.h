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
    NODE_COMM,
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        //variable delaration
        struct {
            char *var_name;
            TokenType var_type;
        } var_decl;
        //function declaration
        struct {
            char *func_name;
            struct ASTNode *params;
            struct ASTNode *body;
        } func_decl;
        //funciton call
        struct {
            char *func_name;
            struct ASTNode *args;
        } func_call;
        // affectztion
        struct {
            char *var_name;
            struct ASTNode *value;
        } assign;
        // binary operation
        struct {
            struct ASTNode *left;
            struct ASTNode *right;
            TokenType op;
        } binary_op;
        // Literral
        struct {
            Token value;
        } literal;
    } data;
    struct ASTNode *next; // for node list
} ASTNode;

void printAST(ASTNode *root);

#endif 
