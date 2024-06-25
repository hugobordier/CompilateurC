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
    NODE_ARRAY_DECL,
    NODE_ARRAY_CALL,
    NODE_BLOCK,
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union { // union c'est pour que la strucure astNode est un type et UNE des srtuct en plus
        //variable delaration
        struct {
            char *var_name;
            TokenType var_type;
        } var_decl;
         struct {
            char *array_name;
            TokenType elem_type;
            struct ASTNode *size; // Optional size expression
        } array_decl;
        // Array access
        struct {
            char *array_name;
            struct ASTNode *index; // Index expression
        } array_access;
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
        struct {
            Token value;
            struct ASTNode* expr;
        }return_stmt;
    } data;
    struct ASTNode *next; // for node list
} ASTNode;

void printAST(ASTNode *root);

#endif 
