#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum {
    NODE_VAR_DECL,
    NODE_FUNC_DECL,
    NODE_FUNC_CALL,
    NODE_ASSIGN,
    NODE_BINARY_OP,
    NODE_LITERAL,
    // ... autres types de nœuds
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        struct {
            char *var_name;
            TokenType var_type;
        } var_decl;
        struct {
            char *func_name;
            struct ASTNode *params;
            struct ASTNode *body;
        } func_decl;
        struct {
            char *func_name;
            struct ASTNode *args;
        } func_call;
        struct {
            char *var_name;
            struct ASTNode *value;
        } assign;
        struct {
            struct ASTNode *left;
            struct ASTNode *right;
            TokenType op;
        } binary_op;
        struct {
            Token value;
        } literal;
        // ... autres structures de nœuds
    } data;
    struct ASTNode *next;
} ASTNode;

ASTNode *parse(const char *source);

#endif // PARSER_H
