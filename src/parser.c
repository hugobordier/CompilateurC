#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declarations
ASTNode *parseExpression(const char *source, int *index);
ASTNode *parseArguments(const char *source, int *index);
ASTNode *parseStatement(const char *source, int *index);
ASTNode *parseBlock(const char *source, int *index);

ASTNode *createNode(NodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;
    node->next = NULL;
    return node;
}

ASTNode *parse(const char *source) {
    int index = 0;
    Token token = getNextToken(source, &index);
    ASTNode *root = createNode(NODE_BLOCK); // Root node is a block containing all statements
    ASTNode *current = root;

    while (token.type != TOKEN_EOF) {
        ASTNode *stmt = parseStatement(source, &index);
        if (stmt) {
            current->next = stmt;
            current = stmt;
        }
        token = getNextToken(source, &index);
    }

    return root;
}

ASTNode *parseStatement(const char *source, int *index) {
    Token token = getNextToken(source, index);

    if (token.type == TOKEN_IDENT) {
        Token next_token = getNextToken(source, index);

        if (next_token.type == TOKEN_IDENT) {
            // Variable or array declaration
            Token next_next_token = getNextToken(source, index);
            if (next_next_token.type == TOKEN_CROCHET_OUVRANT) {
                // Array declaration
                ASTNode *node = createNode(NODE_ARRAY_DECL);
                node->data.array_decl.array_name = token.value;
                node->data.array_decl.elem_type = next_token.type;  // Assuming next_token.value is a string representing the type

                // Check for array size
                next_token = getNextToken(source, index);
                if (next_token.type == TOKEN_NOMBRE) {
                    node->data.array_decl.size = parseExpression(source, index);
                    next_token = getNextToken(source, index); // Expecting closing bracket
                }

                if (next_token.type == TOKEN_CROCHET_FERMANT) {
                    // Successfully parsed array declaration
                    return node;
                }
            } else {
                // Variable declaration
                ASTNode *node = createNode(NODE_VAR_DECL);
                node->data.var_decl.var_name = token.value;
                node->data.var_decl.var_type = next_token.type;
                return node;
            }
        } else if (next_token.type == TOKEN_ASSIGNATION) {
            // Variable assignment
            ASTNode *node = createNode(NODE_ASSIGN);
            node->data.assign.var_name = token.value;
            node->data.assign.value = parseExpression(source, index);
            return node;
        } else if (next_token.type == TOKEN_CROCHET_OUVRANT) {
            // Array element access
            ASTNode *node = createNode(NODE_ARRAY_CALL);
            node->data.array_access.array_name = token.value;
            node->data.array_access.index = parseExpression(source, index); // Parse the index expression

            next_token = getNextToken(source, index); // Expecting closing bracket
            if (next_token.type == TOKEN_CROCHET_FERMANT) {
                // Successfully parsed array access
                return node;
            }
        }
    } else if (token.type == TOKEN_FONCTION) {
        // Function declaration
        ASTNode *node = createNode(NODE_FUNC_DECL);
        node->data.func_decl.func_name = getNextToken(source, index).value;

        // Parse function arguments
        node->data.func_decl.params = parseArguments(source, index);

        // Parse function body
        node->data.func_decl.body = parseBlock(source, index);

        return node;
    }

    return NULL; // Unsupported statement
}

ASTNode *parseArguments(const char *source, int *index) {
    Token token = getNextToken(source, index);
    ASTNode *arg_list = NULL;
    ASTNode **current = &arg_list;

    while (token.type != TOKEN_PAR_FERMANTE && token.type != TOKEN_EOF) {
        if (token.type == TOKEN_IDENT) {
            Token next_token = getNextToken(source, index);
            if (next_token.type == TOKEN_IDENT) {
                ASTNode *arg = createNode(NODE_VAR_DECL);
                arg->data.var_decl.var_name = token.value;
                arg->data.var_decl.var_type = next_token.type;
                *current = arg;
                current = &arg->next;
            }
        }
        token = getNextToken(source, index);
    }

    return arg_list;
}

ASTNode *parseBlock(const char *source, int *index) {
    ASTNode *block = createNode(NODE_BLOCK);
    ASTNode *current = block;

    Token token = getNextToken(source, index);
    while (token.type != TOKEN_ACCO_FERMANTE && token.type != TOKEN_EOF) {
        ASTNode *stmt = parseStatement(source, index);
        if (stmt) {
            current->next = stmt;
            current = stmt;
        }
        token = getNextToken(source, index);
    }

    return block;
}

ASTNode *parseExpression(const char *source, int *index) {
    // Implement the logic to parse expressions
    // This is just a placeholder to demonstrate the structure

    Token token = getNextToken(source, index);
    ASTNode *node = NULL;

    if (token.type == TOKEN_NOMBRE || token.type == TOKEN_REEL || token.type == TOKEN_STRING || token.type == TOKEN_LETTRE) {
        // Literal
        node = createNode(NODE_LITERAL);
        node->data.literal.value = token;
    } else if (token.type == TOKEN_IDENT) {
        // Variable or function call
        Token next_token = getNextToken(source, index);
        if (next_token.type == TOKEN_PAR_OUVRANTE) {
            // Function call
            node = createNode(NODE_FUNC_CALL);
            node->data.func_call.func_name = token.value;
            node->data.func_call.args = parseArguments(source, index);
        } else if (next_token.type == TOKEN_CROCHET_OUVRANT) {
            // Array access
            node = createNode(NODE_ARRAY_CALL);
            node->data.array_access.array_name = token.value;
            node->data.array_access.index = parseExpression(source, index); // Parse the index expression
            getNextToken(source, index); // Expecting closing bracket
        } else {
            // Variable reference
            node = createNode(NODE_VAR_DECL);
            node->data.var_decl.var_name = token.value;
        }
    }

    return node;
}
