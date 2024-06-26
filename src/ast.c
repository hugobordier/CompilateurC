#include "ast.h"
#include <stdio.h>

void printNodeType(NodeType type) {
    switch (type) {
        case NODE_UNKNOWN:       printf("NODE_UNKNOWN"); break;
        case NODE_VAR_DECL:      printf("NODE_VAR_DECL"); break;
        case NODE_FUNC_DECL:     printf("NODE_FUNC_DECL"); break;
        case NODE_FUNC_CALL:     printf("NODE_FUNC_CALL"); break;
        case NODE_ASSIGN:        printf("NODE_ASSIGN"); break;
        case NODE_BINARY_OP:     printf("NODE_BINARY_OP"); break;
        case NODE_LITERAL:       printf("NODE_LITERAL"); break;
        case NODE_RETURN:        printf("NODE_RETURN"); break;
        case NODE_COMMENT:          printf("NODE_COMMENT"); break;
        case NODE_ARRAY_DECL:    printf("NODE_ARRAY_DECL"); break;
        case NODE_ARRAY_ACCESS:    printf("NODE_ARRAY_ACCESS"); break;
        case NODE_BLOCK:         printf("NODE_BLOCK"); break;
        default:                 printf("UNKNOWN_NODE_TYPE"); break;
    }
}

void printASTNode(ASTNode *node) {
    if (node == NULL) {
        printf("NULL\n");
        return;
    }

    printf("Type: ");
    printNodeType(node->type);
    printf("\n");

    switch (node->type) {
        case NODE_VAR_DECL:
            printf("Variable Name: %s\n", node->data.var_decl.var_name);
            printf("Variable Type: %d\n", node->data.var_decl.var_type);
            break;
        case NODE_FUNC_DECL:
            printf("Function Name: %s\n", node->data.func_decl.func_name);
            printf("Parameters:\n");
            printAST(node->data.func_decl.params);
            printf("Body:\n");
            printAST(node->data.func_decl.body);
            break;
        case NODE_FUNC_CALL:
            printf("Function Call: %s\n", node->data.func_call.func_name);
            printf("Arguments:\n");
            printAST(node->data.func_call.args);
            break;
        case NODE_ASSIGN:
            printf("Assignment:\n");
            printf("Variable Name: %s\n", node->data.assign.var_name);
            printf("Assigned Value:\n");
            printAST(node->data.assign.value);
            break;
        case NODE_BINARY_OP:
            printf("Binary Operation:\n");
            printf("Left Operand:\n");
            printAST(node->data.binary_op.left);
            printf("Operator: %d\n", node->data.binary_op.op);
            printf("Right Operand:\n");
            printAST(node->data.binary_op.right);
            break;
        case NODE_LITERAL:
            printf("Literal Value: %s\n", node->data.literal.value.value);
            break;
        case NODE_RETURN:
            printf("Return Statement:\n");
            printAST(node->data.return_stmt.expr);
            break;
        case NODE_COMMENT:
            printf("Comment: %s\n", node->data.comment.text);
            break;
        case NODE_ARRAY_DECL:
            printf("Array Declaration:\n");
            printf("Array Name: %s\n", node->data.array_decl.array_name);
            printf("Element Type: %d\n", node->data.array_decl.elem_type);
            printf("Array Size Expression:\n");
            printAST(node->data.array_decl.size);
            break;
        case NODE_ARRAY_ACCESS:
            printf("Array Access:\n");
            printf("Array Name: %s\n", node->data.array_access.array_name);
            printf("Index Expression:\n");
            printAST(node->data.array_access.index);
            break;
        case NODE_BLOCK:
            printf("Block Statement:\n");
            node = node->next; // Move to the first statement inside the block
            while (node != NULL) {
                printASTNode(node);
                node = node->next;
            }
            break;
        default:
            printf("Unhandled node type.\n");
            break;
    }
}


void printAST(ASTNode *root) {
    if (root == NULL) {
        printf("AST is empty.\n");
        return;
    }

    printf("Printing AST:\n");
    while (root != NULL) {
        printASTNode(root);
        root = root->next;
    }
}
