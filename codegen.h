#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"

int generate_c_code(ASTNode *root, const char *input_path);

#endif
