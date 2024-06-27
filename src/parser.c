#include "parser.h"
#include "lexer.h"
#include "ast.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode *parseExpression(const char *source, int *index);
ASTNode **parseArguments(const char *source, int *index, int *arg_count);
ASTNode *parseStatement(const char *source, int *index);
ASTNode *parseBlock(const char *source, int *index);

ASTNode *createNode(ASTNodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;
    node->next = NULL;
    return node;
}

ASTNode *parse(const char *source) {
    int index = 0;
    ASTNode *root = NULL;
    ASTNode *current = NULL;

    while (source[index] != '\0') {
        ASTNode *stmt = parseStatement(source, &index);
        if (stmt) {
            if (root == NULL) {
                root = stmt;
            } else {
                current->next = stmt;
            }
            current = stmt;
        } else {
            break;
        }
    }

    return root;
}

ASTNode *parseStatement(const char *source, int *index) {
    Token token = getNextToken(source, index);

    if (token.type == TOKEN_TYPE_NOMBRE || token.type == TOKEN_TYPE_REEL ||
        token.type == TOKEN_TYPE_LETTRES || token.type == TOKEN_TYPE_LETTRE ||
        token.type == TOKEN_TYPE_BOOLEAN) {

        Token next_token = getNextToken(source, index);

        if (next_token.type == TOKEN_IDENT) {
            ASTNode *node = createNode(NODE_VAR_DECL);
            node->data.var_decl.var_type = token.type;
            node->data.var_decl.var_name = next_token.value;

            Token next = getNextToken(source, index);
            if (next.type == TOKEN_ASSIGNATION) {
                node->data.var_decl.initial_value = parseExpression(source, index);
            }

            return node;
        } else {
            fprintf(stderr, "Error: Expected identifier after type declaration\n");
            exit(1);
        }
    }

    if (token.type == TOKEN_IDENT) {
        Token next_token = getNextToken(source, index);
        if (next_token.type == TOKEN_ASSIGNATION) {
            ASTNode *node = createNode(NODE_ASSIGNMENT);
            node->data.assignment.var_name = token.value;
            node->data.assignment.value = parseExpression(source, index);
            return node;
        } else if (next_token.type == TOKEN_PAR_OUVRANTE) {
            // Function call
            ASTNode *node = createNode(NODE_FUNCTION_CALL);
            node->data.function_call.function_name = token.value;
            node->data.function_call.arguments = parseArguments(source, index, &node->data.function_call.arg_count);
            return node;
        } else {
            fprintf(stderr, "Error: Expected '=' or '(' after identifier\n");
            exit(1);
        }
    }

    // Parsing des instructions conditionnelles
    if (token.type == TOKEN_IF) {
        ASTNode *node = createNode(NODE_IF_STATEMENT);
        node->data.if_statement.condition = parseExpression(source, index);
        node->data.if_statement.then_branch = parseBlock(source, index);
        
        Token next_token = getNextToken(source, index);
        if (next_token.type == TOKEN_ELSE) {
            node->data.if_statement.else_branch = parseBlock(source, index);
        } else {
            (*index)--;
        }
        
        return node;
    }

    // Ajoutez d'autres cas de parsing d'instructions ici (while, for, etc.)

    return NULL;
}

ASTNode **parseArguments(const char *source, int *index, int *arg_count) {
    Token token = getNextToken(source, index);
    ASTNode **arg_list = NULL;
    *arg_count = 0;

    if (token.type != TOKEN_PAR_OUVRANTE) {
        fprintf(stderr, "Error: Expected '('\n");
        exit(1);
    }

    token = getNextToken(source, index);
    while (token.type != TOKEN_PAR_FERMANTE && token.type != TOKEN_EOF) {
        if (token.type == TOKEN_IDENT) {
            Token next_token = getNextToken(source, index);
            if (next_token.type == TOKEN_IDENT) {
                ASTNode *arg = createNode(NODE_VAR_DECL);
                arg->data.var_decl.var_name = token.value;
                arg->data.var_decl.var_type = next_token.type;
                
                arg_list = realloc(arg_list, sizeof(ASTNode *) * (*arg_count + 1));
                arg_list[*arg_count] = arg;
                (*arg_count)++;
            }
        }
        token = getNextToken(source, index);
        if (token.type == TOKEN_COMMA) {
            token = getNextToken(source, index);
        }
    }

    return arg_list;
}

ASTNode *parseExpression(const char *source, int *index) {
    // Ici vous devez implémenter la logique de parsing des expressions
    // Cela peut inclure des nombres, des opérateurs, des appels de fonction, etc.
    // Pour simplifier, supposons que nous avons seulement des nombres pour l'instant

    Token token = getNextToken(source, index);
    if (token.type == TOKEN_NOMBRE || token.type == TOKEN_REEL) {
        ASTNode *node = createNode(NODE_EXPRESSION);
        // Créer un nœud pour la valeur
        ASTNode *value_node = createNode(NODE_EXPRESSION);
        value_node->data.var_decl.var_name = token.value; // Utiliser un champ approprié pour stocker la valeur
        node->data.var_decl.initial_value = value_node; // Assignation correcte
        return node;
    }

    fprintf(stderr, "Error: Expected a number or expression\n");
    exit(1);
}

ASTNode *parseBlock(const char *source, int *index) {
    Token token = getNextToken(source, index);
    if (token.type != TOKEN_ACCO_OUVRANTE) {
        fprintf(stderr, "Error: Expected '{' at the beginning of a block\n");
        exit(1);
    }

    ASTNode *block = NULL;
    ASTNode *current = NULL;

    while (1) {
        token = getNextToken(source, index);
        if (token.type == TOKEN_ACCO_FERMANTE) {
            break;
        }
        (*index)--;

        ASTNode *stmt = parseStatement(source, index);
        if (stmt) {
            if (block == NULL) {
                block = stmt;
            } else {
                current->next = stmt;
            }
            current = stmt;
        } else {
            fprintf(stderr, "Error: Invalid statement in block\n");
            exit(1);
        }
    }

    return block;
}
