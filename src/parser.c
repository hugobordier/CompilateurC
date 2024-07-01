#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

Parser *create_parser(Token *tokens, int count) {
    Parser *parser = (Parser *)malloc(sizeof(Parser));
    parser->tokens = tokens;
    parser->current = 0;
    parser->count = count;
    return parser;
}

void free_parser(Parser *parser) {
    free(parser->tokens);
    free(parser);
}

Token *advance(Parser *parser) {
    if (parser->current < parser->count) {
        return &parser->tokens[parser->current++];
    }
    return NULL;
}

Token *peek(Parser *parser) {
    if (parser->current < parser->count) {
        return &parser->tokens[parser->current];
    }
    return NULL;
}

int match(Parser *parser, TokenType type) {
    if (peek(parser)->type == type) {
        advance(parser);
        return 1;
    }
    return 0;
}

ASTNode *parse_statement(Parser *parser);
ASTNode *parse_expression(Parser *parser);

ASTNode *parse_program(Parser *parser) {
    ASTNode *node = create_ast_node(NODE_TYPE_PROGRAM);
    node->node_program.function_count = 0;
    node->node_program.functions = NULL;

    while (parser->current < parser->count && peek(parser)->type != TOKEN_EOF) {
        ASTNode *function = parse_statement(parser);
        node->node_program.function_count++;
        node->node_program.functions =
            realloc(node->node_program.functions,
                    sizeof(ASTNode *) * node->node_program.function_count);
        node->node_program.functions[node->node_program.function_count - 1] =
            function;
    }

    return node;
}

ASTNode *parse_function(Parser *parser) {
    if (!match(parser, TOKEN_FONCTION)) {
        fprintf(stderr, "Expected 'fonction' keyword\n");
        exit(EXIT_FAILURE);
    }

    Token *name = advance(parser);
    if (name->type != TOKEN_IDENT) {
        fprintf(stderr, "Expected function name\n");
        exit(EXIT_FAILURE);
    }

    if (!match(parser, TOKEN_PAR_OUVRANTE)) {
        fprintf(stderr, "Expected '('\n");
        exit(EXIT_FAILURE);
    }

    ASTNode *node = create_ast_node(NODE_TYPE_FUNCTION);
    node->node_function.name = *name;
    node->node_function.param_count = 0;
    node->node_function.parameters = NULL;

    while (!match(parser, TOKEN_PAR_FERMANTE)) {
        if (node->node_function.param_count > 0) {
            if (!match(parser, TOKEN_COMMA)) {
                fprintf(stderr, "Expected ',' between parameters\n");
                exit(EXIT_FAILURE);
            }
        }

        Token *param = advance(parser);
        if (param->type != TOKEN_IDENT) {
            fprintf(stderr, "Expected parameter name\n");
            exit(EXIT_FAILURE);
        }

        node->node_function.param_count++;
        node->node_function.parameters =
            realloc(node->node_function.parameters,
                    sizeof(ASTNode *) * node->node_function.param_count);
        node->node_function.parameters[node->node_function.param_count - 1] =
            create_ast_node(NODE_TYPE_EXPRESSION);
        node->node_function.parameters[node->node_function.param_count - 1]
            ->node_expression.expression_type = EXPRESSION_VARIABLE;
        node->node_function.parameters[node->node_function.param_count - 1]
            ->node_expression.variable_expr.name = *param;
    }

    node->node_function.body = parse_statement(parser);
    return node;
}

ASTNode *parse_statement(Parser *parser) {
    if (match(parser, TOKEN_IF)) {
        ASTNode *node = create_ast_node(NODE_TYPE_STATEMENT);
        node->node_statement.statement_type = STATEMENT_IF;

        if (!match(parser, TOKEN_PAR_OUVRANTE)) {
            fprintf(stderr, "Expected '('\n");
            exit(EXIT_FAILURE);
        }

        node->node_statement.if_stmt.condition = parse_expression(parser);

        if (!match(parser, TOKEN_PAR_FERMANTE)) {
            fprintf(stderr, "Expected ')'\n");
            exit(EXIT_FAILURE);
        }

        node->node_statement.if_stmt.then_branch = parse_statement(parser);
        // Handle optional else branch
        return node;
    }

    if (match(parser, TOKEN_WHILE)) {
        ASTNode *node = create_ast_node(NODE_TYPE_STATEMENT);
        node->node_statement.statement_type = STATEMENT_WHILE;

        if (!match(parser, TOKEN_PAR_OUVRANTE)) {
            fprintf(stderr, "Expected '('\n");
            exit(EXIT_FAILURE);
        }

        node->node_statement.while_stmt.condition = parse_expression(parser);

        if (!match(parser, TOKEN_PAR_FERMANTE)) {
            fprintf(stderr, "Expected ')'\n");
            exit(EXIT_FAILURE);
        }

        node->node_statement.while_stmt.body = parse_statement(parser);
        return node;
    }

    if (match(parser, TOKEN_FOR)) {
        ASTNode *node = create_ast_node(NODE_TYPE_STATEMENT);
        node->node_statement.statement_type = STATEMENT_FOR;

        if (!match(parser, TOKEN_PAR_OUVRANTE)) {
            fprintf(stderr, "Expected '('\n");
            exit(EXIT_FAILURE);
        }

        node->node_statement.for_stmt.init = parse_expression(parser);
        if (!match(parser, TOKEN_SEMICOLON)) {
            fprintf(stderr, "Expected ';'\n");
            exit(EXIT_FAILURE);
        }

        node->node_statement.for_stmt.condition = parse_expression(parser);
        if (!match(parser, TOKEN_SEMICOLON)) {
            fprintf(stderr, "Expected ';'\n");
            exit(EXIT_FAILURE);
        }

        node->node_statement.for_stmt.update = parse_expression(parser);

        if (!match(parser, TOKEN_PAR_FERMANTE)) {
            fprintf(stderr, "Expected ')'\n");
            exit(EXIT_FAILURE);
        }

        node->node_statement.for_stmt.body = parse_statement(parser);
        return node;
    }

    if (match(parser, TOKEN_RETURN)) {
        ASTNode *node = create_ast_node(NODE_TYPE_STATEMENT);
        node->node_statement.statement_type = STATEMENT_RETURN;
        node->node_statement.return_stmt.value = parse_expression(parser);
        if (!match(parser, TOKEN_SEMICOLON)) {
            fprintf(stderr, "Expected ';'\n");
            exit(EXIT_FAILURE);
        }
        return node;
    }

    ASTNode *expression_stmt = create_ast_node(NODE_TYPE_STATEMENT);
    expression_stmt->node_statement.statement_type = STATEMENT_EXPRESSION;
    expression_stmt->node_statement.expression_stmt.expression =
        parse_expression(parser);
    if (!match(parser, TOKEN_SEMICOLON)) {
        fprintf(stderr, "Expected ';'\n");
        exit(EXIT_FAILURE);
    }
    return expression_stmt;
}

ASTNode *parse_expression(Parser *parser) {
    // Implement expression parsing (similar to parse_binary_expression, etc.)
    // This is a placeholder and needs to be expanded with actual logic
    ASTNode *node = create_ast_node(NODE_TYPE_EXPRESSION);
    node->node_expression.expression_type = EXPRESSION_LITERAL;
    node->node_expression.literal_expr.value = *advance(parser);
    return node;
}

void print_ast(ASTNode *node, int indent) { print_ast_node(node, indent); }
