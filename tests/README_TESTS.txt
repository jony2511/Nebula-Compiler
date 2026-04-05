Nebula Test Suite (fresh)

Valid feature coverage files:
- 01_types_and_arithmetic.nb
- 02_conditionals_when_if.neb
- 03_switch_case.nb
- 04_loops_all.neb
- 05_break_continue_stop.nb
- 06_functions_return.neb
- 07_builtins_math.neb
- 08_history_nebula.nb
- 09_ternary_logic_bitwise.neb
- 10_unary_incdec.neb
- 11_input_echo.nb  (interactive)
- 14_inline_output.nb

Intentional semantic-negative files:
- 12_semantic_type_mismatch.neb
- 13_semantic_undeclared.nb

Generated C output location:
- output/

Build compiler:
  gcc -o nebula.exe parser.tab.c lex.yy.c ast.c semantic.c codegen.c -lm

Run one sample:
  .\nebula.exe tests\07_builtins_math.neb

Compile generated C from output folder:
  gcc -o output\07_builtins_math.exe output\07_builtins_math.c -lm
  .\output\07_builtins_math.exe
