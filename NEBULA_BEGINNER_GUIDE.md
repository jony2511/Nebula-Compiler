# Nebula Language Learning Guide

This is a complete beginner-to-advanced Nebula tutorial, organized step by step.

It is written to match the current Nebula implementation in this repository, so every syntax example is practical and runnable.

## Table of Contents

1. [Getting Started](#1-getting-started)
2. [Nebula at a Glance](#2-nebula-at-a-glance)
3. [Variables and Data Types](#3-variables-and-data-types)
4. [Output and Input](#4-output-and-input)
5. [Expressions and Operators](#5-expressions-and-operators)
6. [Conditions and Branching](#6-conditions-and-branching)
7. [Loops](#7-loops)
8. [Functions](#8-functions)
9. [Built-in Functions](#9-built-in-functions)
10. [Time-History with nebula(variable, steps_back)](#10-time-history-with-nebulavariable-steps_back)
11. [Inline Output (No Newline)](#11-inline-output-no-newline)
12. [Mini Projects](#12-mini-projects)
13. [Practice Exercises with Click-to-Show Output](#13-practice-exercises-with-click-to-show-output)
14. [Common Errors and How to Fix Them](#14-common-errors-and-how-to-fix-them)
15. [Quick Reference](#15-quick-reference)

---

## 1) Getting Started

### 1.1 Build the compiler

~~~powershell
gcc -o nebula.exe parser.tab.c lex.yy.c ast.c semantic.c codegen.c -lm
~~~

### 1.2 Run a Nebula source file

~~~powershell
.\nebula.exe tests\01_types_and_arithmetic.nb
~~~

### 1.3 Generated C output location

Generated C files are now written into output with the same base filename as the source.

Example:

- Source: tests/07_builtins_math.neb
- Generated C: output/07_builtins_math.c

Compile and run generated C:

~~~powershell
gcc -o output\07_builtins_math.exe output\07_builtins_math.c -lm
.\output\07_builtins_math.exe
~~~

---

## 2) Nebula at a Glance

Nebula is a C-like language with simpler keywords and a built-in history feature.

### 2.1 Core style

- Type-first variable declarations
- Braces for code blocks
- Semicolon-terminated statements
- Familiar control flow (if/else, switch, while/for/do)

### 2.2 Nebula-native keywords and aliases

- display and print (same behavior)
- when and otherwise (if/else style)
- loop keyword (plus while/for/do)
- give and return (same behavior)
- stop and break (same behavior)
- task and function (same behavior)

This means beginners can write Nebula-style code, while C-like users can still use familiar aliases.

---

## 3) Variables and Data Types

Nebula supports:

- num: integer
- dec: decimal (floating point)
- char: character
- bool: boolean
- void: function return-only type

### 3.1 Declare and initialize

~~~nebula
num age = 21;
dec pi = 3.14;
char grade = 'A';
bool passed = true;
~~~

### 3.2 Declare first, assign later

~~~nebula
num count;
count = 10;
~~~

### 3.3 Type compatibility (important)

Current semantic rules allow:

- same type assignment
- num to dec assignment

Current semantic rules reject:

- dec to num assignment

Example rejected by semantic analyzer:

~~~nebula
num n = 10;
dec d = 2.5;
n = d;
~~~

---

## 4) Output and Input

### 4.1 Standard output

Use display or print.

~~~nebula
display("Hello");
print("World");
~~~

Both add a newline at the end.

### 4.2 Read from input

~~~nebula
num x;
display("Enter x:");
input(x);
display(x);
~~~

Input must target a declared variable.

---

## 5) Expressions and Operators

### 5.1 Arithmetic

Supported:

- + - * /

~~~nebula
num a = 10;
num b = 3;
num c = a + b * 2;
display(c);
~~~

Important:

- Modulo (%) is not supported in current grammar.

### 5.2 Comparison

Supported:

- < > <= >= == !=

Result type: bool

### 5.3 Logical

Supported:

- && || !

### 5.4 Bitwise (num only)

Supported:

- & | ^ ~ << >>

### 5.5 Increment and decrement

Supported:

- ++x, x++, --x, x--

### 5.6 Ternary expression

Supported syntax:

- condition ? expr1 : expr2

~~~nebula
num x = 5;
num y = 8;
num maxv = (x > y) ? x : y;
display(maxv);
~~~

---

## 6) Conditions and Branching

### 6.1 when / otherwise

~~~nebula
num n = 12;

when (even(n))
{
    display("even");
}
otherwise
{
    display("odd");
}
~~~

### 6.2 if / else alias

~~~nebula
if (n > 10)
{
    display("greater than 10");
}
else
{
    display("10 or less");
}
~~~

### 6.3 switch / case / default

~~~nebula
num code = 2;

switch (code)
{
    case 1:
        display("one");
        break;
    case 2:
        display("two");
        break;
    default:
        display("other");
}
~~~

---

## 7) Loops

Nebula supports all major loop styles.

### 7.1 while loop

~~~nebula
num i = 1;
num sum = 0;

while (i <= 5)
{
    sum = sum + i;
    i = i + 1;
}

display(sum);
~~~

### 7.2 for loop

~~~nebula
num k = 1;
num sum_for = 0;

for (k = 1; k <= 4; k = k + 1)
{
    sum_for = sum_for + k;
}

display(sum_for);
~~~

### 7.3 do-while loop

~~~nebula
num j = 0;
do
{
    display(j);
    j = j + 1;
}
while (j < 3);
~~~

### 7.4 loop keyword

Condition style:

~~~nebula
num t = 0;
loop (t < 3)
{
    display(t);
    t = t + 1;
}
~~~

For-like style:

~~~nebula
num i;
loop (i = 0; i <= 5; i++)
{
    display(i);
}
~~~

### 7.5 stop or break, continue

~~~nebula
num i = 0;

for (i = 0; i < 10; i = i + 1)
{
    if (i == 2)
    {
        continue;
    }

    if (i == 7)
    {
        stop;
    }

    display(i);
}
~~~

---

## 8) Functions

### 8.1 Define functions

You can use function or task.

~~~nebula
function num add(num x, num y)
{
    give x + y;
}
~~~

Equivalent style:

~~~nebula
task num add(num x, num y)
{
    return x + y;
}
~~~

### 8.2 Call functions

~~~nebula
num s = add(10, 5);
display(s);
~~~

### 8.3 Parameters and return type

Function signature has:

- keyword (function or task)
- return type
- function name
- typed parameters

Example with dec:

~~~nebula
task dec avg3(dec a, dec b, dec c)
{
    return (a + b + c) / 3;
}
~~~

---

## 9) Built-in Functions

Available built-ins:

- even(x) -> bool
- odd(x) -> bool
- factorial(n) -> num
- prime(n) -> bool
- palindrome(x) -> bool
- leap_year(y) -> bool
- power(base, exp) -> dec
- sin(x) -> dec
- cos(x) -> dec
- tan(x) -> dec
- nebula(variable, steps_back) -> num

Trigonometry note:

- sin, cos, tan interpret input as degrees.

~~~nebula
display(even(10));
display(prime(29));
display(palindrome("level"));
display(power(3, 4));

dec angle = 30;
display(sin(angle));
display(cos(angle));
display(tan(angle));
~~~

---

## 10) Time-History with nebula(variable, steps_back)

Nebula tracks previous values for num variables.

### 10.1 Signature

~~~text
nebula(variable, steps_back)
~~~

### 10.2 Meaning

- 0 means current value
- 1 means previous value
- 2 means two updates back

### 10.3 Rules

- First argument must be a variable name (identifier).
- History tracking is for num variables.
- History buffer size is 10 values.

~~~nebula
num a = 10;
a = a + 5;
a = a * 2;

display(nebula(a, 0));
display(nebula(a, 1));
display(nebula(a, 2));
~~~

Expected:

~~~text
30
15
10
~~~

---

## 11) Inline Output (No Newline)

Use these when you do not want automatic newline:

- display_inline(...)
- print_inline(...)
- write(...)

~~~nebula
num i;
num n = 5;

loop (i = 0; i <= n; i++)
{
    display_inline('*');
}

display("");
display("done");
~~~

Output:

~~~text
******
done
~~~

---

## 12) Mini Projects

### Project A: Number classifier

Goal:

- Read one number
- Print if even/odd
- Print if prime/not prime

### Project B: History tracker demo

Goal:

- Update variable several times
- Print last three states using nebula

### Project C: Pattern printer

Goal:

- Print stars in one line and multi-line forms
- Use display_inline and display

---

## 13) Practice Exercises with Click-to-Show Output

Use these as W3Schools-style practice items.

### Exercise 1: Variables and output

~~~nebula
num score = 95;
dec ratio = 1.25;
char letter = 'A';
bool passed = true;

display(score);
display(ratio);
display(letter);
display(passed);
~~~

<details>
<summary>Show output</summary>

~~~text
95
1.25
A
true
~~~

</details>

### Exercise 2: Arithmetic and precedence

~~~nebula
num a = 10;
num b = 3;
num c = a + b * 2;
display(c);
~~~

<details>
<summary>Show output</summary>

~~~text
16
~~~

</details>

### Exercise 3: Branching

~~~nebula
num x = 17;

when (x < 10)
{
    display("small");
}
otherwise
{
    display("big");
}
~~~

<details>
<summary>Show output</summary>

~~~text
big
~~~

</details>

### Exercise 4: for loop sum

~~~nebula
num i = 1;
num sum = 0;

for (i = 1; i <= 5; i = i + 1)
{
    sum = sum + i;
}

display(sum);
~~~

<details>
<summary>Show output</summary>

~~~text
15
~~~

</details>

### Exercise 5: Functions

~~~nebula
task num square(num n)
{
    return n * n;
}

display(square(9));
~~~

<details>
<summary>Show output</summary>

~~~text
81
~~~

</details>

### Exercise 6: Built-ins

~~~nebula
display(even(10));
display(odd(10));
display(factorial(5));
display(prime(29));
~~~

<details>
<summary>Show output</summary>

~~~text
true
false
120
true
~~~

</details>

### Exercise 7: History feature

~~~nebula
num a = 10;
a = a + 5;
a = a * 2;

display(nebula(a, 0));
display(nebula(a, 1));
display(nebula(a, 2));
~~~

<details>
<summary>Show output</summary>

~~~text
30
15
10
~~~

</details>

### Exercise 8: Inline output

~~~nebula
num i;
for (i = 0; i < 5; i = i + 1)
{
    display_inline('#');
}
display("");
~~~

<details>
<summary>Show output</summary>

~~~text
#####
~~~

</details>

---

## 14) Common Errors and How to Fix Them

### Error A: Variable used before declaration

Message pattern:

- Variable name used before declaration

Fix:

- Declare first, use later.

### Error B: Type mismatch in assignment

~~~nebula
num n = 10;
dec d = 2.5;
n = d;
~~~

Fix:

- Keep assignment compatible with current semantic rules.

### Error C: Unsupported operator

Example:

- % modulo not supported by current grammar.

Fix:

- Redesign logic with supported operators or built-ins.

### Error D: Wrong nebula first argument

Wrong:

~~~nebula
display(nebula(a + 1, 1));
~~~

Correct:

~~~nebula
display(nebula(a, 1));
~~~

---

## 15) Quick Reference

### Types

- num, dec, char, bool, void

### Control flow

- when/otherwise
- if/else
- switch/case/default
- loop, while, for, do-while
- stop or break, continue

### Functions

- task or function
- give or return

### I/O

- display(...), print(...)
- display_inline(...), print_inline(...), write(...)
- input(variable)

### Built-ins

- even, odd, factorial, prime, palindrome, leap_year, power, sin, cos, tan, nebula

### File extensions

- preferred: .nb
- supported: .neb

---

## Suggested Study Path

1. Learn sections 2 to 5 and run small snippets.
2. Practice branching and loops in sections 6 and 7.
3. Learn reusable code with functions in section 8.
4. Use built-ins and history in sections 9 and 10.
5. Master formatting with inline output in section 11.
6. Solve all exercises in section 13 before checking outputs.
