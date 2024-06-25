#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "semantic.h"
#include "codegen.h"

int main() {
    const char *source = "nombre a = 10 // test;fonction(nombre varA){varA = varA + 1}; si (a == 10) { fonction(a); };";

    printf("Lexing:\n");
    printLexer(source);

    ASTNode *ast = parse(source);

    printf("AST:\n");
    printAST(ast);

    printf("\nSemantic Analysis:\n");
    analyzeSemantics(ast);

    printf("\nGenerated Code:\n");
    generateCode(ast);

    return 0;
}
