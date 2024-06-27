#include "parser.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode *parse_expression(Parser *parser);
ASTNode *parse_term(Parser *parser);
ASTNode *parse_factor(Parser *parser);

// Fonction pour créer un parser
Parser createParser(const char *source) {
    Parser parser;
    parser.tokens = tokenize(
        source); // Supposons que cette fonction tokenize utilise le lexer
    parser.currentTokenIndex = 0;
    return parser;
}

// Fonction pour détruire le parser et libérer les ressources
void destroyParser(Parser *parser) {
    free(parser->tokens); // Libérer la mémoire allouée pour les tokens
}

// Fonction pour récupérer le token courant
Token getCurrentToken(Parser *parser) {
    return parser->tokens[parser->currentTokenIndex];
}

// Fonction pour avancer vers le prochain token
void advance(Parser *parser) { parser->currentTokenIndex++; }

// Fonction principale pour démarrer l'analyse syntaxique et créer l'AST
ASTNode *parse(Parser *parser) {
    return parse_expression(parser); // On commence par analyser une expression
}

// Fonction pour créer un nœud AST avec un type spécifié
ASTNode *createASTNode(ASTNodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;
    node->children = NULL;
    node->childrenCount = 0;
    return node;
}

// Fonction pour ajouter un enfant à un nœud AST
void addASTChild(ASTNode *parent, ASTNode *child) {
    parent->children = (ASTNode **)realloc(
        parent->children, sizeof(ASTNode *) * (parent->childrenCount + 1));
    parent->children[parent->childrenCount++] = child;
}

// Fonction pour détruire un nœud AST et libérer la mémoire récursivement
void destroyAST(ASTNode *node) {
    if (node) {
        for (int i = 0; i < node->childrenCount; i++) {
            destroyAST(node->children[i]);
        }
        free(node->children);
        free(node);
    }
}

// Fonction pour imprimer l'arbre syntaxique abstrait
void printAST(ASTNode *node, int level) {
    if (node) {
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        switch (node->type) {
        case AST_IDENTIFIER:
            printf("Identifier: %s\n", node->data.identifier);
            break;
        case AST_CONSTANT:
            printf("Constant: %f\n", node->data.constant);
            break;
        case AST_STRING_LITERAL:
            printf("String Literal: %s\n", node->data.string_literal);
            break;
        case AST_UNARY_OPERATION:
            printf("Unary Operation\n");
            printAST(node->data.unary_expr, level + 1);
            break;
        case AST_BINARY_OPERATION:
            printf("Binary Operation\n");
            printAST(node->data.binary_expr.left, level + 1);
            printAST(node->data.binary_expr.right, level + 1);
            break;
        case AST_CONDITIONAL:
            printf("Conditional\n");
            printAST(node->data.conditional.condition, level + 1);
            printf("True Branch:\n");
            printAST(node->data.conditional.true_branch, level + 2);
            printf("False Branch:\n");
            printAST(node->data.conditional.false_branch, level + 2);
            break;
        case AST_FUNCTION_CALL:
            printf("Function Call: %s\n", node->data.function_call.name);
            for (int i = 0; i < node->data.function_call.num_args; i++) {
                printf("Argument %d:\n", i + 1);
                printAST(node->data.function_call.args[i], level + 1);
            }
            break;
        case AST_ASSIGNMENT:
            printf("Assignment: %s\n", node->data.assignment.name);
            printAST(node->data.assignment.value, level + 1);
            break;
        case AST_TYPE:
            printf("Type: %s\n", node->data.type.name);
            break;
        // Ajoute d'autres cas selon les types de nœuds nécessaires
        default:
            printf("Unknown Node Type\n");
            break;
        }
        for (int i = 0; i < node->childrenCount; i++) {
            printAST(node->children[i], level + 1);
        }
    }
}

// Fonction pour analyser une expression
ASTNode *parse_expression(Parser *parser) {
    ASTNode *left = parse_term(parser);

    while (getCurrentToken(parser).type == TOKEN_PLUS ||
           getCurrentToken(parser).type == TOKEN_MOINS) {
        TokenType op_type = getCurrentToken(parser).type;
        advance(parser);
        ASTNode *right = parse_term(parser);

        ASTNode *binary_expr = createASTNode(AST_BINARY_OPERATION);
        binary_expr->data.binary_expr.left = left;
        binary_expr->data.binary_expr.right = right;

        switch (op_type) {
        case TOKEN_PLUS:
            binary_expr->data.binary_expr.operation = '+';
            break;
        case TOKEN_MOINS:
            binary_expr->data.binary_expr.operation = '-';
            break;
        // Ajoute d'autres opérations selon les types de tokens nécessaires
        default:
            fprintf(stderr, "Unexpected token in expression\n");
            destroyAST(binary_expr);
            return NULL;
        }

        left = binary_expr;
    }

    return left;
}

// Fonction pour analyser un terme
ASTNode *parse_term(Parser *parser) {
    ASTNode *left = parse_factor(parser);

    while (getCurrentToken(parser).type == TOKEN_FOIS ||
           getCurrentToken(parser).type == TOKEN_DIVISION) {
        TokenType op_type = getCurrentToken(parser).type;
        advance(parser);
        ASTNode *right = parse_factor(parser);

        ASTNode *binary_expr = createASTNode(AST_BINARY_OPERATION);
        binary_expr->data.binary_expr.left = left;
        binary_expr->data.binary_expr.right = right;

        switch (op_type) {
        case TOKEN_FOIS:
            binary_expr->data.binary_expr.operation = '*';
            break;
        case TOKEN_DIVISION:
            binary_expr->data.binary_expr.operation = '/';
            break;
        // Ajoute d'autres opérations selon les types de tokens nécessaires
        default:
            fprintf(stderr, "Unexpected token in term\n");
            destroyAST(binary_expr);
            return NULL;
        }

        left = binary_expr;
    }

    return left;
}

// Fonction pour analyser un facteur
ASTNode *parse_factor(Parser *parser) {
    Token current_token = getCurrentToken(parser);
    advance(parser);

    if (current_token.type == TOKEN_NOMBRE ||
        current_token.type == TOKEN_REEL) {
        double value = atof(current_token.value);
        ASTNode *constant_node = createASTNode(AST_CONSTANT);
        constant_node->data.constant = value;
        return constant_node;
    } else if (current_token.type == TOKEN_IDENT) {
        ASTNode *identifier_node = createASTNode(AST_IDENTIFIER);
        identifier_node->data.identifier = strdup(current_token.value);
        return identifier_node;
    } else if (current_token.type == TOKEN_PAR_OUVRANTE) {
        ASTNode *expression_node = parse_expression(parser);
        if (getCurrentToken(parser).type != TOKEN_PAR_FERMANTE) {
            fprintf(stderr, "Expected closing parenthesis\n");
            destroyAST(expression_node);
            return NULL;
        }
        advance(parser);
        return expression_node;
    } else {
        fprintf(stderr, "Unexpected token in factor\n");
        return NULL;
    }
}
