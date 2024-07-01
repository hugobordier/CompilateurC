#ifndef AST_H
#define AST_H

#include "lexer.h"
typedef enum {
    NODE_TYPE_PROGRAM,
    NODE_TYPE_FUNCTION,
    NODE_TYPE_STATEMENT,
    NODE_TYPE_EXPRESSION,
} NodeType;

typedef enum {
    STATEMENT_IF,
    STATEMENT_WHILE,
    STATEMENT_FOR,
    STATEMENT_RETURN,
    STATEMENT_EXPRESSION,
} StatementType;

typedef enum {
    EXPRESSION_BINARY,
    EXPRESSION_UNARY,
    EXPRESSION_LITERAL,
    EXPRESSION_VARIABLE,
    EXPRESSION_ASSIGNMENT,
    EXPRESSION_FUNCTION_CALL,
} ExpressionType;

typedef enum {
    FUNCTION_DECL,
} FunctionType;

typedef enum {
    PROGRAM_DECL,
} ProgramType;

typedef struct ASTNode {
    NodeType type;
    union {
        struct {
            struct ASTNode **functions;//liste de fonction pcq astnode c deja une liste dcp la on veut une liste dans un noeud dcp double pointer
            int function_count;
        } node_program;

        struct {
            Token name;
            struct ASTNode **parameters;
            int param_count;
            struct ASTNode *body;// need to be a stmt
        } node_function;

        struct {
            StatementType statement_type;
            union {
                struct {
                    struct ASTNode *condition;// need to be a expression between parentheses
                    struct ASTNode *then_branch;  //need to be a stmt  
                    //struct ASTNode *else_branch; //stmt 
                } if_stmt;

                struct {
                    struct ASTNode *condition;//expression
                    struct ASTNode *body;//stmt 
                } while_stmt;

                struct {
                    struct ASTNode *init;//expr
                    struct ASTNode *condition;//expr
                    struct ASTNode *update;//expr
                    struct ASTNode *body;//stmt
                } for_stmt;

                struct {
                    struct ASTNode *value;//expr
                } return_stmt;

                struct {
                    struct ASTNode *expression;
                } expression_stmt;
            };
        } node_statement;

        struct {
            ExpressionType expression_type;
            union {
                struct {
                    struct ASTNode *left;//expr
                    struct ASTNode *right;//expr
                    TokenType op; // type d'opérateur
                } binary_expr;

                struct {
                    struct ASTNode *operand;
                    TokenType op; 
                } unary_expr;

                struct {
                    Token value;
                } literal_expr;

                struct {
                    Token name;
                } variable_expr;

                struct {
                    struct ASTNode *left;
                    struct ASTNode *right;
                } assignment_expr;

                struct {
                    Token function_name;
                    struct ASTNode **arguments;
                    int arg_count;
                } function_call_expr;
            };
        } node_expression;
    };
} ASTNode;

ASTNode* create_ast_node(NodeType type);
void free_ast_node(ASTNode *node);
void print_ast_node(ASTNode *node, int indent);

#endif