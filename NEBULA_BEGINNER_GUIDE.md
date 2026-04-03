# Nebula Beginner Guide (with C Comparison)

## 1. Syntax Diff First: Nebula vs C

If you know basic C, this is the fastest way to start Nebula.

| Concept | C | Nebula | What Changed |
|---|---|---|---|
| Integer type | `int` | `num` | Keyword changed |
| Decimal type | `float` / `double` | `dec` | Nebula uses one decimal keyword |
| Character type | `char` | `char` | Same |
| Boolean type | `_Bool` / `bool` | `bool` | Same keyword idea |
| If | `if (...)` | `when (...)` (or `if (...)`) | Nebula native style is `when` |
| Else | `else` | `otherwise` (or `else`) | Nebula native style is `otherwise` |
| Loop | `for`, `while` | `loop (...)` (also supports `for`, `while`) | Nebula native style is `loop` |
| Return | `return expr;` | `give expr;` (also supports `return`) | Nebula native style is `give` |
| Print | `printf(...)` | `display(...)` or `print(...)` | `display` is preferred alias |
| Input | `scanf(...)` | `input(var);` | Simpler built-in input |
| Function declaration | `int add(int a,int b){...}` | `task num add(num a, num b){...}` or `function ...` | `task` is preferred alias |

### Important differences from C in this project implementation

- Use `display(...)` and `input(...)` (legacy `print(...)` also works), not `printf/scanf`.
- Use `num` and `dec` instead of `int/float/double` in Nebula style.
- Use `when/otherwise` and `loop` for native Nebula syntax.
- Preferred file extension is `.nb` (legacy `.neb` still works).
- Modulo `%` is not currently supported in your Nebula grammar.

---

## 2. What Feels the Same as C

- Statements end with `;`
- Blocks use `{ ... }`
- Arithmetic operators: `+ - * /`
- Comparisons: `== != < > <= >=`
- Assignment: `=`
- Expressions and precedence are C-like

---

## 3. Your First Nebula Program

```nebula
print("Hello, Nebula");
```

---

## 4. Variables and Types

```nebula
num age = 21;
dec pi = 3.14;
char grade = 'A';
bool ok = true;

print(age);
print(pi);
print(grade);
print(ok);
```

### C comparison

C:

```c
int age = 21;
double pi = 3.14;
char grade = 'A';
_Bool ok = 1;
```

Nebula just changes type keywords and booleans are directly `true/false`.

---

## 5. Input and Output

```nebula
num x;
print("Enter x:");
input(x);
print(x);
```

### C comparison

C:

```c
int x;
printf("Enter x: ");
scanf("%d", &x);
printf("%d\n", x);
```

Nebula removes format specifiers and pointer syntax for beginner-friendly input/output.

---

## 6. Expressions and Assignment

```nebula
num a = 10;
num b = 5;
num c;

c = (a + b) * 2;
print(c);
```

---

## 7. Conditionals

### Native Nebula style

```nebula
num marks = 72;

when (marks >= 50) {
    print("Pass");
} otherwise {
    print("Fail");
}
```

### Also accepted (C-style alias)

```nebula
if (marks >= 50) {
    print("Pass");
} else {
    print("Fail");
}
```

---

## 8. Loops

### A) Nebula condition loop

```nebula
num i = 1;
loop (i <= 3) {
    print(i);
    i = i + 1;
}
```

### B) C-like loop form also supported

```nebula
num j;
loop (j = 0; j < 3; j = j + 1) {
    print(j);
}
```

---

## 9. Functions

```nebula
function num add(num x, num y) {
    give x + y;
}

num ans = add(10, 5);
print(ans);
```

### C comparison

C:

```c
int add(int x, int y) {
    return x + y;
}
```

Nebula uses `function` and `give` for native style.

---

## 10. Full Beginner Example

```nebula
num sum = 0;
num i = 1;

loop (i <= 5) {
    sum = sum + i;
    i = i + 1;
}

print(sum);
```

Expected output:

```text
15
```

---

## 11. Common Beginner Mistakes

1. Missing semicolon:
- Wrong: `print("hi")`
- Correct: `print("hi");`

2. Using variable before declaration:
- Wrong: `x = 5; num x;`
- Correct: `num x; x = 5;`

3. Type mismatch:
- Example: adding `num` and unsupported/non-numeric types in arithmetic.

4. Writing C I/O directly:
- Wrong: `printf`, `scanf`
- Correct: `print`, `input`

5. Using unsupported operators in this grammar (like `%`).

---

## 12. Practice Tasks

1. Write a program to input 2 numbers and print the larger one.
2. Write a loop program to print 1 to 10.
3. Write a function `square(num x)` and print `square(7)`.
4. Write a Celsius-to-Fahrenheit converter using `dec`.

---

## 13. Quick Cheat Sheet

```text
Types: num dec char bool
I/O: print(...), input(var)
Condition: when (...) { ... } otherwise { ... }
Loop: loop (condition) { ... }
Function: function type name(params) { give expr; }
```
