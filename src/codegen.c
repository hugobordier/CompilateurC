#include "codegen.h"
#include <stdio.h>

void generateCode(ASTNode *root) {
    while (root) {
        switch (root->type) {
            case NODE_VAR_DECL:
                break;
            case NODE_ASSIGN:
                break;
            case NODE_FUNC_CALL:
                break;
            default:
                break;
        }
        root = root->next;
    }
}
