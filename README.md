# Nebula Programming Language Compiler

A complete educational compiler project for a custom language named Nebula, developed as part of the CSE 3212 (Compiler Design Laboratory) course.

This project demonstrates the full front-end and execution pipeline of a programming language, including lexical analysis, parsing, semantic analysis, AST-based interpretation, and source-to-source code generation to C.

## Project Context

- Course: CSE 3212 - Compiler Design Laboratory
- Department: Computer Science and Engineering
- Institution: Khulna University of Engineering and Technology (KUET)
- Project Author: **Md. Tariful Islam Jony**
- Roll: **2107119**

## Table of Contents

1. [Overview](#overview)
2. [Key Features](#key-features)
3. [Language Design Highlights](#language-design-highlights)
4. [Compiler Architecture](#compiler-architecture)
5. [Project Structure](#project-structure)
6. [Build and Run](#build-and-run)
7. [Generated C Workflow](#generated-c-workflow)
8. [Sample Programs](#sample-programs)
9. [Error Handling](#error-handling)
10. [Learning Outcomes](#learning-outcomes)
11. [Future Improvements](#future-improvements)
12. [Author](#author)

## Overview

Nebula is a C-like language with simplified keywords and beginner-friendly syntax. The project supports:

- Lexical analysis with Flex
- Syntax analysis with Bison
- Semantic checks with scoped symbol tables
- AST construction and runtime interpretation
- Automatic C code generation for valid programs

The compiler accepts Nebula source files (`.nb` and `.neb`), validates and executes them, and generates equivalent C code in the `output/` directory.

## Key Features

- Static type system with `num`, `dec`, `char`, `bool`, and `void`
- Control flow support:
  - `when/otherwise` and `if/else`
  - `switch/case/default`
  - `loop`, `while`, `for`, `do-while`
- Functions with typed parameters and typed return values (`task` or `function`)
- I/O support:
  - Line-based output: `display(...)` / `print(...)`
  - Inline output: `display_inline(...)`, `print_inline(...)`, `write(...)`
  - Input: `input(variable)`
- Built-in library functions:
  - `even`, `odd`, `factorial`, `prime`, `palindrome`, `leap_year`, `power`, `sin`, `cos`, `tan`
- Nebula history primitive:
  - `nebula(variable, steps_back)` for time-history reads on numeric variables
- Source-to-source code generation to C with behavior parity for supported features

## Language Design Highlights

Nebula includes native keywords and compatibility aliases to improve readability:

- Native style:
  - `when`, `otherwise`, `loop`, `give`, `stop`, `display`
- Compatibility aliases:
  - `if`, `else`, `while`, `for`, `return`, `break`, `print`, `task`, `function`

This allows both beginner-friendly syntax and familiar C-like coding style.

## Compiler Architecture

The implementation follows a classic compiler pipeline:

1. Lexer (Flex)
- File: `lexer.l`
- Tokenizes source code into keywords, literals, identifiers, operators, and delimiters.

2. Parser (Bison)
- File: `parser.y`
- Validates grammar and constructs the Abstract Syntax Tree (AST).

3. Semantic Analyzer
- Files: `semantic.c`, `semantic.h`
- Performs type checks, declaration/use validation, and scope-aware symbol resolution.

4. Runtime Interpreter
- File: `ast.c`
- Evaluates AST directly and executes Nebula programs.

5. C Code Generator
- Files: `codegen.c`, `codegen.h`
- Converts valid AST into compilable C source code under `output/`.

## Project Structure

```text
.
|-- ast.c
|-- ast.h
|-- semantic.c
|-- semantic.h
|-- codegen.c
|-- codegen.h
|-- lexer.l
|-- parser.y
|-- parser.tab.c
|-- parser.tab.h
|-- lex.yy.c
|-- tests/
|-- output/
|-- NEBULA_BEGINNER_GUIDE.md
|-- README.md
```

## Build and Run

Build the Nebula compiler executable:

```powershell
gcc -o nebula.exe parser.tab.c lex.yy.c ast.c semantic.c codegen.c -lm
```

Run a Nebula program:

```powershell
.\nebula.exe tests\07_builtins_math.neb
```

If you modify grammar or lexer rules, regenerate parser/lexer sources first:

```powershell
bison -d parser.y
flex lexer.l
```

## Generated C Workflow

On successful parse and semantic validation, C source is generated automatically.

Example:

- Input: `tests/07_builtins_math.neb`
- Generated: `output/07_builtins_math.c`

Compile generated C:

```powershell
gcc -o output\07_builtins_math.exe output\07_builtins_math.c -lm
.\output\07_builtins_math.exe
```

## Sample Programs

The `tests/` directory contains curated examples covering language features:

- Types and arithmetic
- Branching and switch-case
- Loop variants and loop control
- Functions and return paths
- Built-in math and utility calls
- Nebula history behavior
- Inline output behavior
- Semantic negative tests (intentional failures)

A detailed learning/tutorial guide is available here: [Nebula Beginner Guide](NEBULA_BEGINNER_GUIDE.md).

## Error Handling

The compiler reports:

- Lexical errors (invalid tokens)
- Syntax errors (grammar mismatch)
- Semantic errors (type mismatch, undeclared variables, duplicate declarations)

Runtime layer also provides safe behavior for invalid history access in `nebula(...)`.

## Learning Outcomes

This project demonstrates practical understanding of:

- DFA-style lexical analysis
- CFG-driven parsing and AST construction
- Scope-sensitive symbol management
- Static semantic validation
- Runtime interpretation semantics
- Source-to-source translation and backend interoperability (Nebula to C)

## Future Improvements

Potential enhancements for production-grade evolution:

- Full modulo and additional arithmetic operator support
- Richer string type and operations
- Better diagnostics with source spans and suggestions
- Standard library expansion
- Optimization passes before C emission
- Unit/integration test automation for all language features


