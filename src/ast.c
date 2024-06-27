#include "ast.h"
#include "utils.h" // Inclure utils.h pour le prototype de tokenTypeToString
#include <stdio.h>
#include <stdlib.h>

void printASTNode(ASTNode *node) {
    if (node == NULL) {
        return;
    }
    switch (node->type) {
    case NODE_VAR_DECL:
        printf("Type: NODE_VAR_DECL\n");
        printf("Variable Declaration: %s %s\n",
               tokenTypeToString(node->data.var_decl.var_type),
               node->data.var_decl.var_name);
        if (node->data.var_decl.initial_value) {
            printf("Initial Value:\n");
            printASTNode(node->data.var_decl.initial_value);
        }
        break;
    case NODE_ASSIGNMENT:
        printf("Type: NODE_ASSIGNMENT\n");
        printf("Assignment: %s = ", node->data.assignment.var_name);
        printASTNode(node->data.assignment.value);
        break;
    case NODE_FUNCTION_CALL:
        printf("Type: NODE_FUNCTION_CALL\n");
        printf("Function Call: %s(", node->data.function_call.function_name);
        for (int i = 0; i < node->data.function_call.arg_count; i++) {
            printASTNode(node->data.function_call.arguments[i]);
            if (i < node->data.function_call.arg_count - 1) {
                printf(", ");
            }
        }
        printf(")\n");
        break;
    case NODE_EXPRESSION:
        printf("Type: NODE_EXPRESSION\n");
        // Assurez-vous d'afficher correctement les informations sur le nœud
        // d'expression
        if (node->data.var_decl.initial_value) {
            printf("Expression Value: ");
            printASTNode(node->data.var_decl.initial_value);
        }
        break;
    case NODE_IF_STATEMENT:
        printf("Type: NODE_IF_STATEMENT\n");
        printf("If Statement: if (");
        printASTNode(node->data.if_statement.condition);
        printf(") ");
        printASTNode(node->data.if_statement.then_branch);
        if (node->data.if_statement.else_branch) {
            printf("else ");
            printASTNode(node->data.if_statement.else_branch);
        }
        break;
    // Ajoutez les autres cas de types de nœuds si nécessaire
    default:
        printf("Unhandled node type.\n");
    }
    if (node->next) {
        printASTNode(node->next);
    }
}
