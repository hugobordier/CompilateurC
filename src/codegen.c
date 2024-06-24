#include "codegen.h"
#include <stdio.h>

void generateCode(ASTNode *root) {
    // TODO: Implémenter la génération de code
    while (root) {
        switch (root->type) {
            case NODE_VAR_DECL:
                // Générer le code pour la déclaration de variable
                break;
            case NODE_ASSIGN:
                // Générer le code pour l'affectation
                break;
            case NODE_FUNC_CALL:
                // Générer le code pour l'appel de fonction
                break;
            // ... autres types de nœuds
            default:
                break;
        }
        root = root->next;
    }
}
