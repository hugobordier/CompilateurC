#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printAST(ASTNode *node, int indent);

void printIndent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
}

void printBinaryExpr(ASTNode *node, int indent) {
    printIndent(indent);
    printf("Binary Expression: %s\n", node->data.binary_expr.operation);
    printAST(node->data.binary_expr.left, indent + 1);
    printAST(node->data.binary_expr.right, indent + 1);
}

void printUnaryExpr(ASTNode *node, int indent) {
    printIndent(indent);
    printf("Unary Expression: %s\n", node->data.unary_expr.operation);
    printAST(node->data.unary_expr.operand, indent + 1);
}

void printFunctionDecl(ASTNode *node, int indent) {
    printIndent(indent);
    printf("Function Declaration: %s\n", node->data.function_decl.name);
    for (int i = 0; i < node->data.function_decl.parameter_count; i++) {
        printAST(node->data.function_decl.parameters[i], indent + 1);
    }
    printAST(node->data.function_decl.body, indent + 1);
}

void printCompoundStmt(ASTNode *node, int indent) {
    printIndent(indent);
    printf("Compound Statement:\n");
    for (int i = 0; i < node->data.compound_stmt.statement_count; i++) {
        printAST(node->data.compound_stmt.statements[i], indent + 1);
    }
}

void printConditionalStmt(ASTNode *node, int indent) {
    printIndent(indent);
    printf("Conditional Statement:\n");
    printIndent(indent + 1);
    printf("Condition:\n");
    printAST(node->data.conditional_stmt.condition, indent + 2);
    printIndent(indent + 1);
    printf("Then Branch:\n");
    printAST(node->data.conditional_stmt.then_branch, indent + 2);
    if (node->data.conditional_stmt.else_branch) {
        printIndent(indent + 1);
        printf("Else Branch:\n");
        printAST(node->data.conditional_stmt.else_branch, indent + 2);
    }
}

void printLoopStmt(ASTNode *node, int indent) {
    printIndent(indent);
    printf("Loop Statement:\n");
    printIndent(indent + 1);
    printf("Condition:\n");
    printAST(node->data.loop_stmt.condition, indent + 2);
    printIndent(indent + 1);
    printf("Body:\n");
    printAST(node->data.loop_stmt.body, indent + 2);
}

void printReturnStmt(ASTNode *node, int indent) {
    printIndent(indent);
    printf("Return Statement:\n");
    printAST(node->data.return_stmt.value, indent + 1);
}

void printVariableDefinition(ASTNode *node, int indent) {
    printIndent(indent);
    printf("Variable Definition: %s\n", node->data.variable_definition.name);
    if (node->data.variable_definition.initializer) {
        printAST(node->data.variable_definition.initializer, indent + 1);
    }
}

void printExpressionStmt(ASTNode *node, int indent) {
    printIndent(indent);
    printf("Expression Statement:\n");
    printAST(node->data.expression_stmt.expression, indent + 1);
}

void printIntegerLiteralExpr(ASTNode *node, int indent) {
    printIndent(indent);
    printf("Integer Literal: %d\n", node->data.integer_literal_expr.value);
}

void printStringLiteralExpr(ASTNode *node, int indent) {
    printIndent(indent);
    printf("String Literal: %s\n", node->data.string_literal_expr.value);
}

void printIdentifierExpr(ASTNode *node, int indent) {
    printIndent(indent);
    printf("Identifier: %s\n", node->data.identifier_expr.name);
}

void printIndexingExpr(ASTNode *node, int indent) {
    printIndent(indent);
    printf("Indexing Expression:\n");
    printAST(node->data.indexing_expr.array, indent + 1);
    printAST(node->data.indexing_expr.index, indent + 1);
}

void printFunctionCallExpr(ASTNode *node, int indent) {
    printIndent(indent);
    printf("Function Call: %s\n", node->data.function_call_expr.name);
    for (int i = 0; i < node->data.function_call_expr.argument_count; i++) {
        printAST(node->data.function_call_expr.arguments[i], indent + 1);
    }
}

void printAST(ASTNode *node, int indent) {
    if (!node) return;

    switch (node->type) {
        case NODE_BINARY_EXPRESSION:
            printBinaryExpr(node, indent);
            break;
        case NODE_UNARY_EXPRESSION:
            printUnaryExpr(node, indent);
            break;
        case NODE_FUNCTION_DECL_PROGRAM:
            printFunctionDecl(node, indent);
            break;
        case NODE_COMPOUND_STMT:
            printCompoundStmt(node, indent);
            break;
        case NODE_CONDITIONAL_STMT:
            printConditionalStmt(node, indent);
            break;
        case NODE_LOOP_STMT:
            printLoopStmt(node, indent);
            break;
        case NODE_RETURN_STMT:
            printReturnStmt(node, indent);
            break;
        case NODE_VARIABLE_DEFINITION:
            printVariableDefinition(node, indent);
            break;
        case NODE_EXPRESSION_STMT:
            printExpressionStmt(node, indent);
            break;
        case NODE_INTEGER_LITERAL_EXPRESSION:
            printIntegerLiteralExpr(node, indent);
            break;
        case NODE_STRING_LITERAL_EXPRESSION:
            printStringLiteralExpr(node, indent);
            break;
        case NODE_IDENTIFIER_EXPRESSION:
            printIdentifierExpr(node, indent);
            break;
        case NODE_INDEXING_EXPRESSION:
            printIndexingExpr(node, indent);
            break;
        case NODE_FUNCTION_CALL_EXPRESSION:
            printFunctionCallExpr(node, indent);
            break;
        case NODE_NOOP_STMT:
            printIndent(indent);
            printf("No-op Statement\n");
            break;
        default:
            printIndent(indent);
            printf("Unknown node type\n");
            break;
    }
}

int main() {
    // Example usage
    // You would normally build the AST from your parser, but here we'll manually create one for demonstration.

    // Integer literal expression
    ASTNode intLiteral = { .type = NODE_INTEGER_LITERAL_EXPRESSION };
    intLiteral.data.integer_literal_expr.value = 42;

    // Print the AST
    printAST(&intLiteral, 0);

    return 0;
}
