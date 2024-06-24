#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "semantic.h"
#include "codegen.h"

int main() {
    const char *source = "nombre a = 10; si (a == 10) { a = a + 1; }";
    ASTNode *ast = parse(source);

    printf("AST:\n");
    printAST(ast);

    printf("\nSemantic Analysis:\n");
    analyzeSemantics(ast);

    printf("\nGenerated Code:\n");
    generateCode(ast);

    // Libérer l'AST
    // TODO: Implémenter la libération de la mémoire de l'AST

    return 0;
}
