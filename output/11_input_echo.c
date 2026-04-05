#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX_HISTORY 10
typedef struct NebHistory {
    const char *name;
    int values[MAX_HISTORY];
    int head;
    int count;
    struct NebHistory *next;
} NebHistory;
static NebHistory *neb_history_table = NULL;
static NebHistory *neb_get_history(const char *name) {
    NebHistory *curr = neb_history_table;
    if (!name || !name[0]) return NULL;
    while (curr) {
        if (strcmp(curr->name, name) == 0) return curr;
        curr = curr->next;
    }
    curr = (NebHistory *)calloc(1, sizeof(NebHistory));
    if (!curr) return NULL;
    curr->name = name;
    curr->head = -1;
    curr->count = 0;
    curr->next = neb_history_table;
    neb_history_table = curr;
    return curr;
}
static void neb_add_value(const char *name, int value) {
    NebHistory *h = neb_get_history(name);
    if (!h) return;
    h->head = (h->head + 1) % MAX_HISTORY;
    h->values[h->head] = value;
    if (h->count < MAX_HISTORY) h->count++;
}
static int nebula_observe_current(const char *name, int steps_back) {
    int idx;
    NebHistory *h = neb_get_history(name);
    if (!h || h->count == 0 || steps_back < 0 || steps_back >= h->count) return 0;
    idx = (h->head - steps_back + MAX_HISTORY) % MAX_HISTORY;
    return h->values[idx];
}
static double neb_sin_deg(double x) { return sin(x * 3.14159265358979323846 / 180.0); }
static double neb_cos_deg(double x) { return cos(x * 3.14159265358979323846 / 180.0); }
static double neb_tan_deg(double x) { return tan(x * 3.14159265358979323846 / 180.0); }
static int even(int x) { return (x % 2) == 0; }
static int odd(int x) { return (x % 2) != 0; }
static int factorial(int n) { int i, f = 1; if (n < 0) return 0; for (i = 2; i <= n; i++) f *= i; return f; }
static int prime(int n) { int i; if (n < 2) return 0; for (i = 2; i * i <= n; i++) if (n % i == 0) return 0; return 1; }
static int palindrome_int(int n) { int x = n, rev = 0; if (n < 0) return 0; while (x > 0) { rev = rev * 10 + (x % 10); x /= 10; } return n == rev; }
static int palindrome_str(const char *s) { int l = 0; int r = (int)strlen(s) - 1; while (l < r) { if (s[l] != s[r]) return 0; l++; r--; } return 1; }
#define palindrome(x) _Generic((x), char*: palindrome_str, const char*: palindrome_str, default: palindrome_int)(x)
static int leap_year(int y) { return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)); }
static double power(double base, double expv) { return pow(base, expv); }

int main(void) {
    int v;
    printf("%s", "enter a number:");
    printf("\n");
    scanf("%d", &v);
    neb_add_value("v", v);
    printf("%s", "you entered:");
    printf("\n");
    printf("%d", (int)v);
    printf("\n");
    return 0;
}
