#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode *parseExpression(const char *source, int *index) {
    // TODO: Implémenter l'analyse des expressions
    return NULL;
}

ASTNode *parseArguments(const char *source, int *index) {
    // TODO: Implémenter l'analyse des arguments de fonction
    return NULL;
}

// Fonction pour créer un nouveau node AST
ASTNode *createNode(NodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;
    node->next = NULL;
    return node;
}

// Fonction principale de parsing
ASTNode *parse(const char *source) {
    int index = 0;
    Token token = getNextToken(source, &index);
    ASTNode *root = NULL;
    ASTNode **current = &root;

    while (token.type != TOKEN_EOF) {
        if (token.type == TOKEN_IDENT) {
            // Vérifier si c'est une déclaration de variable ou une assignation
            Token next_token = getNextToken(source, &index);
            if (next_token.type == TOKEN_IDENT) {
                // Déclaration de variable
                ASTNode *node = createNode(NODE_VAR_DECL);
                node->data.var_decl.var_name = token.value;
                node->data.var_decl.var_type = next_token.type;
                *current = node;
                current = &node->next;
            } else if (next_token.type == TOKEN_EGALITE) {
                // Assignation
                ASTNode *node = createNode(NODE_ASSIGN);
                node->data.assign.var_name = token.value;
                node->data.assign.value = parseExpression(source, &index);
                *current = node;
                current = &node->next;
            }
        } else if (token.type == TOKEN_IDENT) {
            // Appel de fonction
            ASTNode *node = createNode(NODE_FUNC_CALL);
            node->data.func_call.func_name = token.value;
            node->data.func_call.args = parseArguments(source, &index);
            *current = node;
            current = &node->next;
        }
        token = getNextToken(source, &index);
    }

    return root;
}

