#ifndef AST_H
#define AST_H

typedef enum {
    // Principal Node Types
    NODE_FUNCTION,
    NODE_EXPRESSION,
    NODE_STMT,
    NODE_PROGRAM,
} NODETypePrimary;

typedef enum {
    // Detailed Node Types
    NODE_FUNCTION_DECL_PROGRAM,
    NODE_PARAMETER_FUNCTION,
    NODE_COMPOUND_STMT,
    NODE_CONDITIONAL_STMT,
    NODE_LOOP_STMT,
    NODE_RETURN_STMT,
    NODE_VARIABLE_DEFINITION,
    NODE_EXPRESSION_STMT,
    NODE_NOOP_STMT,
    NODE_INTEGER_LITERAL_EXPRESSION,
    NODE_STRING_LITERAL_EXPRESSION,
    NODE_IDENTIFIER_EXPRESSION,
    NODE_INDEXING_EXPRESSION,
    NODE_FUNCTION_CALL_EXPRESSION,
    NODE_BINARY_EXPRESSION,
    NODE_UNARY_EXPRESSION,
} NODEType;

typedef struct ASTNode {
    NODEType type;
    union {
        struct {
            struct ASTNode *left;
            struct ASTNode *right;
            char *operation;
        } binary_expr;
        struct {
            struct ASTNode *operand;
            char *operation;
        } unary_expr;
        struct {
            char *name;
            struct ASTNode **parameters;
            int parameter_count;
            struct ASTNode *body;
        } function_decl;
        struct {
            struct ASTNode **statements;
            int statement_count;
        } compound_stmt;
        struct {
            struct ASTNode *condition;
            struct ASTNode *then_branch;
            struct ASTNode *else_branch;
        } conditional_stmt;
        struct {
            struct ASTNode *condition;
            struct ASTNode *body;
        } loop_stmt;
        struct {
            struct ASTNode *value;
        } return_stmt;
        struct {
            char *name;
            struct ASTNode *initializer;
        } variable_definition;
        struct {
            struct ASTNode *expression;
        } expression_stmt;
        struct {
            int value;
        } integer_literal_expr;
        struct {
            char *value;
        } string_literal_expr;
        struct {
            char *name;
        } identifier_expr;
        struct {
            struct ASTNode *array;
            struct ASTNode *index;
        } indexing_expr;
        struct {
            char *name;
            struct ASTNode **arguments;
            int argument_count;
        } function_call_expr;
    } data;
} ASTNode;

#endif
