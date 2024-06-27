#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode *createASTNode(ASTNodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    node->type = type;
    switch (type) {
    case AST_IDENTIFIER:
        node->data.identifier = NULL;
        break;
    case AST_BINARY_OPERATION:
        node->data.binary_expr.left = NULL;
        node->data.binary_expr.right = NULL;
        node->data.binary_expr.operation = '\0';
        break;
    // Gérer d'autres cas selon les types de nœuds nécessaires
    default:
        fprintf(stderr, "Unknown ASTNodeType\n");
        free(node);
        return NULL;
    }
    return node;
}

ASTNode *createASTNodeWithID(ASTNodeType type, char *identifier) {
    ASTNode *node = createASTNode(type);
    if (node == NULL) {
        return NULL;
    }
    if (type == AST_IDENTIFIER && identifier != NULL) {
        node->data.identifier = strdup(identifier);
        if (node->data.identifier == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            destroyAST(node);
            return NULL;
        }
    }
    return node;
}

ASTNode *createASTNodeWithOperation(ASTNodeType type, char *operation) {
    ASTNode *node = createASTNode(type);
    if (node == NULL) {
        return NULL;
    }
    if (type == AST_BINARY_OPERATION) {
        node->data.binary_expr.operation = operation;
    }
    return node;
}

void destroyAST(ASTNode *root) {
    if (root == NULL) {
        return;
    }
    switch (root->type) {
    case AST_IDENTIFIER:
        free(root->data.identifier);
        break;
    // Ajouter d'autres cas selon les types de nœuds nécessaires
    default:
        break;
    }
    free(root);
}

void printAST(ASTNode *root, int level) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    switch (root->type) {
    case AST_IDENTIFIER:
        printf("Identifier: %s\n", root->data.identifier);
        break;
    case AST_BINARY_OPERATION:
        printf("Binary Operation: %s\n", root->data.binary_expr.operation);
        break;
    // Ajouter d'autres cas selon les types de nœuds nécessaires
    default:
        printf("Unknown ASTNodeType\n");
        break;
    }
    printAST(root->data.binary_expr.left, level + 1);
    printAST(root->data.binary_expr.right, level + 1);
}
