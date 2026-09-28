/* Approach 1: stack-based postfix evaluation */
#include <stdio.h>
#include <ctype.h>
#include <time.h>

int apply(char op, int a, int b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int ops_stack = 0;

int eval_stack(const char *s, int verbose) {
    int st[100], top = -1;              /* array-based stack; -1 = empty */
    ops_stack = 0;
    for (; *s; s++) {
        if (isspace((unsigned char)*s)) continue;
        if (isdigit((unsigned char)*s)) {
            st[++top] = *s - '0';       /* operand: PUSH */
            if (verbose) printf("  push %c\n", *s);
        } else {
            int b = st[top--], a = st[top--];   /* operator: POP two */
            int r = apply(*s, a, b);
            st[++top] = r;                      /* PUSH result */
            ops_stack++;
            if (verbose) printf("  '%c': pop %d, %d -> %d %c %d = %d, push %d\n",
                                *s, b, a, a, *s, b, r, r);
        }
    }
    return st[top];
}

int main(void) {
    char buf[256];
    FILE *f = fopen("input.txt", "r");
    if (!f || !fgets(buf, sizeof buf, f)) { fprintf(stderr, "Cannot read input.txt\n"); return 1; }
    fclose(f);

    printf("Postfix: %s\n", buf);
    printf("=== Stack-based evaluation trace ===\n");
    int r = eval_stack(buf, 1);
    printf("Result = %d\n", r);
    printf("Arithmetic operations = %d\n\n", ops_stack);

    const int N = 2000000;
    volatile int sink = 0;
    clock_t t = clock();
    for (int i = 0; i < N; i++) sink = eval_stack(buf, 0);
    printf("Stack eval (%d runs): %.4f s\n", N, (double)(clock() - t) / CLOCKS_PER_SEC);
    return 0;
}
