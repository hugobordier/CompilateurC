#include "ast.h"
#include "parser.h"
#include <stdio.h>

void printAST(ASTNode *root) {
    while (root) {
        switch (root->type) {
            case NODE_VAR_DECL:
                printf("Variable Declaration: %s\n", root->data.var_decl.var_name);
                break;
            case NODE_ASSIGN:
                printf("Assignment: %s\n", root->data.assign.var_name);
                break;
            case NODE_FUNC_CALL:
                printf("Function Call: %s\n", root->data.func_call.func_name);
                break;
            default:
                printf("Unknown node type\n");
                break;
        }
        root = root->next;
    }
}
