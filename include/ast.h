#ifndef AST_H
#define AST_H

typedef enum {
    AST_PROGRAM,
    AST_STATEMENT,
    AST_EXPRESSION,
    AST_TERM,
    AST_FACTOR,
    AST_IDENTIFIER,
    AST_CONSTANT,
    AST_STRING_LITERAL,
    AST_UNARY_OPERATION,
    AST_BINARY_OPERATION,
    AST_CONDITIONAL,
    AST_FUNCTION_CALL,
    AST_ASSIGNMENT,
    AST_TYPE,
    // Ajoute d'autres types de nœuds selon les besoins
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    union {
        char *identifier;       // Pour AST_IDENTIFIER, AST_FUNCTION_CALL, etc.
        double constant;        // Pour AST_CONSTANT (nombre réel)
        char *string_literal;   // Pour AST_STRING_LITERAL
        struct ASTNode *unary_expr;    // Pour AST_UNARY_OPERATION
        struct {
            struct ASTNode *left;
            struct ASTNode *right;
            char *operation;
        } binary_expr;         // Pour AST_BINARY_OPERATION
        struct {
            struct ASTNode *condition;
            struct ASTNode *true_branch;
            struct ASTNode *false_branch;
        } conditional;         // Pour AST_CONDITIONAL
        struct {
            char *name;
            struct ASTNode **args;
            int num_args;
        } function_call;       // Pour AST_FUNCTION_CALL
        struct {
            char *name;
            struct ASTNode *value;
        } assignment;          // Pour AST_ASSIGNMENT
        struct {
            char *name;
        } type;                // Pour AST_TYPE
        // Ajoute d'autres membres d'union selon les types de nœuds nécessaires
    } data;
    struct ASTNode **children;
    int childrenCount;
    char *identifier; // Pour AST_IDENTIFIER
} ASTNode;

ASTNode *createASTNode(ASTNodeType type);
void addASTChild(ASTNode *parent, ASTNode *child);
void destroyAST(ASTNode *node);
void printAST(ASTNode *node, int level);

#endif
