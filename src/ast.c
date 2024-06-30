#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

// Function to create a new AST node
ASTNode* create_ast_node(NodeType type) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    return node;
}

// Function to free an AST node
void free_ast_node(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_TYPE_PROGRAM:
            for (int i = 0; i < node->node_program.function_count; ++i) {
                free_ast_node(node->node_program.functions[i]);
            }
            free(node->node_program.functions);
            break;

        case NODE_TYPE_FUNCTION:
            free(node->node_function.name.value);
            for (int i = 0; i < node->node_function.param_count; ++i) {
                free_ast_node(node->node_function.parameters[i]);
            }
            free(node->node_function.parameters);
            free_ast_node(node->node_function.body);
            break;

        case NODE_TYPE_STATEMENT:
            switch (node->node_statement.statement_type) {
                case STATEMENT_IF:
                    free_ast_node(node->node_statement.if_stmt.condition);
                    free_ast_node(node->node_statement.if_stmt.then_branch);
                    // free_ast_node(node->node_statement.if_stmt.else_branch);
                    break;

                case STATEMENT_WHILE:
                    free_ast_node(node->node_statement.while_stmt.condition);
                    free_ast_node(node->node_statement.while_stmt.body);
                    break;

                case STATEMENT_FOR:
                    free_ast_node(node->node_statement.for_stmt.init);
                    free_ast_node(node->node_statement.for_stmt.condition);
                    free_ast_node(node->node_statement.for_stmt.update);
                    free_ast_node(node->node_statement.for_stmt.body);
                    break;

                case STATEMENT_RETURN:
                    free_ast_node(node->node_statement.return_stmt.value);
                    break;

                case STATEMENT_EXPRESSION:
                    free_ast_node(node->node_statement.expression_stmt.expression);
                    break;
            }
            break;

        case NODE_TYPE_EXPRESSION:
            switch (node->node_expression.expression_type) {
                case EXPRESSION_BINARY:
                    free_ast_node(node->node_expression.binary_expr.left);
                    free_ast_node(node->node_expression.binary_expr.right);
                    break;

                case EXPRESSION_UNARY:
                    free_ast_node(node->node_expression.unary_expr.operand);
                    break;

                case EXPRESSION_LITERAL:
                    free(node->node_expression.literal_expr.value.value);
                    break;

                case EXPRESSION_VARIABLE:
                    free(node->node_expression.variable_expr.name.value);
                    break;

                case EXPRESSION_ASSIGNMENT:
                    free_ast_node(node->node_expression.assignment_expr.left);
                    free_ast_node(node->node_expression.assignment_expr.right);
                    break;

                case EXPRESSION_FUNCTION_CALL:
                    free(node->node_expression.function_call_expr.function_name.value);
                    for (int i = 0; i < node->node_expression.function_call_expr.arg_count; ++i) {
                        free_ast_node(node->node_expression.function_call_expr.arguments[i]);
                    }
                    free(node->node_expression.function_call_expr.arguments);
                    break;
            }
            break;
    }
    free(node);
}

// Function to print the AST nodes
void print_ast_node(ASTNode *node, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; ++i) {
        printf("  ");
    }

    switch (node->type) {
        case NODE_TYPE_PROGRAM:
            printf("Program Node\n");
            for (int i = 0; i < node->node_program.function_count; ++i) {
                print_ast_node(node->node_program.functions[i], indent + 1);
            }
            break;

        case NODE_TYPE_FUNCTION:
            printf("Function Node: %s\n", node->node_function.name.value);
            for (int i = 0; i < node->node_function.param_count; ++i) {
                print_ast_node(node->node_function.parameters[i], indent + 1);
            }
            print_ast_node(node->node_function.body, indent + 1);
            break;

        case NODE_TYPE_STATEMENT:
            switch (node->node_statement.statement_type) {
                case STATEMENT_IF:
                    printf("If Statement\n");
                    print_ast_node(node->node_statement.if_stmt.condition, indent + 1);
                    print_ast_node(node->node_statement.if_stmt.then_branch, indent + 1);
                    // print_ast_node(node->node_statement.if_stmt.else_branch, indent + 1);
                    break;

                case STATEMENT_WHILE:
                    printf("While Statement\n");
                    print_ast_node(node->node_statement.while_stmt.condition, indent + 1);
                    print_ast_node(node->node_statement.while_stmt.body, indent + 1);
                    break;

                case STATEMENT_FOR:
                    printf("For Statement\n");
                    print_ast_node(node->node_statement.for_stmt.init, indent + 1);
                    print_ast_node(node->node_statement.for_stmt.condition, indent + 1);
                    print_ast_node(node->node_statement.for_stmt.update, indent + 1);
                    print_ast_node(node->node_statement.for_stmt.body, indent + 1);
                    break;

                case STATEMENT_RETURN:
                    printf("Return Statement\n");
                    print_ast_node(node->node_statement.return_stmt.value, indent + 1);
                    break;

                case STATEMENT_EXPRESSION:
                    printf("Expression Statement\n");
                    print_ast_node(node->node_statement.expression_stmt.expression, indent + 1);
                    break;
            }
            break;

        case NODE_TYPE_EXPRESSION:
            switch (node->node_expression.expression_type) {
                case EXPRESSION_BINARY:
                    printf("Binary Expression: %d\n", node->node_expression.binary_expr.op);
                    print_ast_node(node->node_expression.binary_expr.left, indent + 1);
                    print_ast_node(node->node_expression.binary_expr.right, indent + 1);
                    break;

                case EXPRESSION_UNARY:
                    printf("Unary Expression: %d\n", node->node_expression.unary_expr.op);
                    print_ast_node(node->node_expression.unary_expr.operand, indent + 1);
                    break;

                case EXPRESSION_LITERAL:
                    printf("Literal Expression: %s\n", node->node_expression.literal_expr.value.value);
                    break;

                case EXPRESSION_VARIABLE:
                    printf("Variable Expression: %s\n", node->node_expression.variable_expr.name.value);
                    break;

                case EXPRESSION_ASSIGNMENT:
                    printf("Assignment Expression\n");
                    print_ast_node(node->node_expression.assignment_expr.left, indent + 1);
                    print_ast_node(node->node_expression.assignment_expr.right, indent + 1);
                    break;

                case EXPRESSION_FUNCTION_CALL:
                    printf("Function Call Expression: %s\n", node->node_expression.function_call_expr.function_name.value);
                    for (int i = 0; i < node->node_expression.function_call_expr.arg_count; ++i) {
                        print_ast_node(node->node_expression.function_call_expr.arguments[i], indent + 1);
                    }
                    break;
            }
            break;
    }
}
