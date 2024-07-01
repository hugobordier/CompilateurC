#include "parser.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Parser *create_parser(Token *tokens, int token_count) {
    Parser *parser = malloc(sizeof(Parser));
    parser->tokens = tokens;
    parser->current = 0;
    parser->count = token_count;
    return parser;
}

void free_parser(Parser *parser) {
    free(parser->tokens);
    free(parser);
}

Token *get_current_token(Parser *parser) {
    if (parser->current < parser->count) {
        return &parser->tokens[parser->current];
    }
    return NULL;
}

Token *advance(Parser *parser) {
    if (parser->current < parser->count) {
        return &parser->tokens[parser->current++];
    }
    return NULL;
}

ASTNode *parse_expression(Parser *parser) {
    Token *current_token = get_current_token(parser);
    if (current_token->type == TOKEN_NOMBRE) {
        ASTNode *node = create_ast_node(NODE_TYPE_EXPRESSION);
        node->node_expression.expression_type = EXPRESSION_LITERAL;
        node->node_expression.literal_expr.value = *current_token;
        advance(parser);
        return node;
    }
    // Ajoutez d'autres types d'expressions ici si nécessaire
    return NULL;
}

ASTNode *parse_statement(Parser *parser) {
    Token *current_token = get_current_token(parser);
    if (current_token->type == TOKEN_IDENT &&
        strcmp(current_token->value, "retourne") == 0) {
        advance(parser); // Consommez "retourne"
        ASTNode *value = parse_expression(parser);
        if (value != NULL) {
            ASTNode *node = create_ast_node(NODE_TYPE_STATEMENT);
            node->node_statement.statement_type = STATEMENT_RETURN;
            node->node_statement.return_stmt.value = value;
            return node;
        }
    }
    // Ajoutez d'autres types de statements ici si nécessaire
    return NULL;
}

ASTNode *parse_function(Parser *parser) {
    Token *type_token = advance(parser); // Consommez le type de retour
    if (type_token->type < TOKEN_TYPE_NOMBRE ||
        type_token->type > TOKEN_TYPE_BOOLEAN) {
        fprintf(stderr, "Erreur: Type de retour de fonction invalide.\n");
        exit(EXIT_FAILURE);
    }

    Token *name_token = advance(parser); // Consommez le nom de la fonction
    if (name_token->type != TOKEN_IDENT) {
        fprintf(stderr, "Erreur: Nom de fonction attendu.\n");
        exit(EXIT_FAILURE);
    }

    ASTNode *function = create_ast_node(NODE_TYPE_FUNCTION);
    function->node_function.name = *name_token;
    function->node_function.param_count = 0;
    function->node_function.parameters = NULL;

    advance(parser); // Consommez '('
    // Analysez les paramètres si nécessaire
    advance(parser); // Consommez ')'
    advance(parser); // Consommez '{'

    function->node_function.body = parse_statement(parser);

    advance(parser); // Consommez '}'

    return function;
}

ASTNode *parse_program(Parser *parser) {
    ASTNode *program = create_ast_node(NODE_TYPE_PROGRAM);
    program->node_program.function_count = 0;
    program->node_program.functions = NULL;

    while (parser->current < parser->count - 1) {
        ASTNode *function = parse_function(parser);
        program->node_program.function_count++;
        program->node_program.functions =
            realloc(program->node_program.functions,
                    program->node_program.function_count * sizeof(ASTNode *));
        program->node_program
            .functions[program->node_program.function_count - 1] = function;
    }

    return program;
}
