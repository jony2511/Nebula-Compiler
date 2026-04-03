#ifndef NEBULA_SEMANTIC_H
#define NEBULA_SEMANTIC_H

#include "ast.h"

extern int semantic_error_count;

void semantic_reset(void);
const char *type_name(NebulaType t);
void semantic_error(int line, const char *fmt, ...);

void enter_scope(void);
void exit_scope(void);
void declare_variable(const char *name, NebulaType type, int line);
NebulaType resolve_identifier_type(const char *name, int line);

int is_assignment_compatible(NebulaType lhs, NebulaType rhs);
NebulaType arithmetic_result_type(NebulaType lhs, NebulaType rhs, const char *op, int line);
NebulaType equality_result_type(NebulaType lhs, NebulaType rhs, const char *op, int line);
NebulaType relational_result_type(NebulaType lhs, NebulaType rhs, const char *op, int line);
NebulaType logical_result_type(NebulaType lhs, NebulaType rhs, const char *op, int line);
NebulaType bitwise_result_type(NebulaType lhs, NebulaType rhs, const char *op, int line);
NebulaType unary_plus_minus_type(NebulaType t, const char *op, int line);
NebulaType unary_not_type(NebulaType t, int line);
NebulaType unary_bitnot_type(NebulaType t, int line);
NebulaType incdec_type(NebulaType t, const char *op, int line);
void check_condition_type(NebulaType cond_type, int line, const char *kw);

#endif
