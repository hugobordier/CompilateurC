#include "ast.h"
#include "codegen.h"
#include "lexer.h"
#include "parser.h"
#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>

char *readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *content = malloc(length + 1);
    if (!content) {
        fprintf(stderr, "Could not allocate memory\n");
        exit(1);
    }

    fread(content, 1, length, file);
    content[length] = '\0';
    fclose(file);
    return content;
}

int main() {
    const char *source = "nombre a = 10; a = a /1;";
    // const char *source = readFile("tests/test1.txt");
    printf("Lexing:\n");
    printLexer(source);

    ASTNode *ast = parse(source);

    printf("AST:\n");
    printASTNode(ast);

    printf("\nSemantic Analysis:\n");
    // analyzeSemantics(ast);

    printf("\nGenerated Code:\n");
    // generateCode(ast);

    return 0;
}
