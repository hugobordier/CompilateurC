#include "ast.h"
#include <stdio.h>

void printASTNode(ASTNode *node, int indent) {
    if (!node) return;
    for (int i = 0; i < indent; i++) printf("  ");
    switch (node->type) {
        case NODE_VAR_DECL:
            printf("VarDecl: %s\n", node->data.var_decl.var_name);
            break;
        case NODE_ARRAY_DECL:
            printf("ArrayDecl: %s\n", node->data.array_decl.array_name);
            break;
        case NODE_FUNC_DECL:
            printf("FuncDecl: %s\n", node->data.func_decl.func_name);
            break;
        case NODE_FUNC_CALL:
            printf("FuncCall: %s\n", node->data.func_call.func_name);
            break;
        case NODE_ASSIGN:
            printf("Assign: %s\n", node->data.assign.var_name);
            break;
        case NODE_BINARY_OP:
            printf("BinaryOp: %d\n", node->data.binary_op.op);
            break;
        case NODE_LITERAL:
            printf("Literal: %s\n", node->data.literal.value.value);
            break;
        case NODE_RETURN:
            printf("Return\n");
            break;
        case NODE_ARRAY_CALL:
            printf("ArrayCall: %s\n", node->data.array_access.array_name);
            break;
        case NODE_BLOCK:
            printf("Block\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }
    printASTNode(node->next, indent);
}

void printAST(ASTNode *root) {
    printASTNode(root, 0);
}
