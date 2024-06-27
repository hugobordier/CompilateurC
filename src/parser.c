#include "parser.h"
#include "ast.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode *parseStatement(const char **source, int *index);
ASTNode *parseExpression(const char **source, int *index);
ASTNode *parsePrimary(const char **source, int *index);
ASTNode *parseAssignment(const char **source, int *index);
ASTNode *parseVarDeclaration(const char **source, int *index);

// Function to create a new AST node
ASTNode *createNode(ASTNodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;
    node->next = NULL;
    memset(&node->data, 0, sizeof(node->data));
    return node;
}

// Function to parse the source code and create the AST
ASTNode *parse(const char *source) {
    int index = 0;
    ASTNode *root = NULL;
    ASTNode *current = NULL;

    while (1) {
        Token token = getNextToken(source, &index);
        if (token.type == TOKEN_EOF) {
            break;
        }
        if (token.type == TOKEN_UNKNOWN) {
            printf("Unknown token: %s\n", token.value);
            free(token.value);
            continue;
        }

        ASTNode *node = parseStatement(&source, &index);
        if (node == NULL) {
            printf("Syntax error at position %d\n", index);
            return NULL;
        }

        if (root == NULL) {
            root = node;
        } else {
            current->next = node;
        }
        current = node;

        token = getNextToken(source, &index);
        if (token.type != TOKEN_SEMICOLON) {
            printf("Syntax error: expected ';' at position %d\n", index);
            return NULL;
        }
    }
    return root;
}

ASTNode *parseStatement(const char **source, int *index) {
    Token token = getNextToken(*source, index);

    if (token.type == TOKEN_TYPE_NOMBRE || token.type == TOKEN_TYPE_REEL ||
        token.type == TOKEN_TYPE_LETTRES || token.type == TOKEN_TYPE_LETTRE ||
        token.type == TOKEN_TYPE_BOOLEAN) {
        // Parse variable declaration
        return parseVarDeclaration(source, index);
    }

    if (token.type == TOKEN_IDENT) {
        // Parse assignment or function call
        Token nextToken = getNextToken(*source, index);
        if (nextToken.type == TOKEN_ASSIGNATION) {
            return parseAssignment(source, index);
        }
    }

    printf("Syntax error: unexpected token %s at position %d\n", token.value,
           *index);
    return NULL;
}

ASTNode *parseVarDeclaration(const char **source, int *index) {
    Token typeToken = getNextToken(*source, index);
    Token nameToken = getNextToken(*source, index);

    if (nameToken.type != TOKEN_IDENT) {
        printf("Syntax error: expected identifier after type at position %d\n",
               *index);
        return NULL;
    }

    ASTNode *node = createNode(NODE_VAR_DECL);
    node->data.var_decl.var_type = typeToken.type;
    node->data.var_decl.var_name = nameToken.value;

    Token nextToken = getNextToken(*source, index);
    if (nextToken.type == TOKEN_ASSIGNATION) {
        node->data.var_decl.initial_value = parseExpression(source, index);
    }

    return node;
}

ASTNode *parseAssignment(const char **source, int *index) {
    Token nameToken = getNextToken(*source, index);

    ASTNode *node = createNode(NODE_ASSIGNMENT);
    node->data.assignment.var_name = nameToken.value;

    node->data.assignment.value = parseExpression(source, index);

    return node;
}

ASTNode *parseExpression(const char **source, int *index) {
    // This is a simplified version that only handles basic arithmetic
    ASTNode *left = parsePrimary(source, index);

    while (1) {
        Token token = getNextToken(*source, index);
        if (token.type != TOKEN_PLUS && token.type != TOKEN_MOINS &&
            token.type != TOKEN_FOIS && token.type != TOKEN_DIVISION &&
            token.type != TOKEN_PUISSANCE && token.type != TOKEN_MODULO) {
            (*index)--;
            return left;
        }

        ASTNode *node = createNode(NODE_EXPRESSION);
        node->data.expression.left = left;
        node->data.expression.operator= token.value;
        node->data.expression.right = parsePrimary(source, index);

        left = node;
    }
}

ASTNode *parsePrimary(const char **source, int *index) {
    Token token = getNextToken(*source, index);

    if (token.type == TOKEN_NOMBRE || token.type == TOKEN_REEL ||
        token.type == TOKEN_STRING || token.type == TOKEN_LETTRE) {
        ASTNode *node = createNode(NODE_EXPRESSION);
        node->data.var_decl.initial_value = NULL;
        node->data.var_decl.var_name = token.value;
        return node;
    }

    if (token.type == TOKEN_IDENT) {
        ASTNode *node = createNode(NODE_EXPRESSION);
        node->data.var_decl.initial_value = NULL;
        node->data.var_decl.var_name = token.value;
        return node;
    }

    if (token.type == TOKEN_PAR_OUVRANTE) {
        ASTNode *node = parseExpression(source, index);
        token = getNextToken(*source, index);
        if (token.type != TOKEN_PAR_FERMANTE) {
            printf("Syntax error: expected ')' at position %d\n", *index);
            return NULL;
        }
        return node;
    }

    printf("Syntax error: unexpected token %s at position %d\n", token.value,
           *index);
    return NULL;
}