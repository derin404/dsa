/* Approach 2: expression tree (build, traversals, evaluation) */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef struct Node { char val; struct Node *l, *r; } Node;

int ops_tree = 0, nodes = 0;

int apply(char op, int a, int b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

Node *build(const char *s) {
    Node *st[100]; int top = -1;
    nodes = 0;
    for (; *s; s++) {
        if (isspace((unsigned char)*s)) continue;
        Node *n = malloc(sizeof(Node));
        n->val = *s; n->l = n->r = NULL; nodes++;
        if (!isdigit((unsigned char)*s)) { n->r = st[top--]; n->l = st[top--]; }
        st[++top] = n;
    }
    return st[top];
}

int eval_tree(Node *n, int verbose) {
    if (isdigit((unsigned char)n->val)) return n->val - '0';
    int a = eval_tree(n->l, verbose), b = eval_tree(n->r, verbose);
    int r = apply(n->val, a, b);
    ops_tree++;
    if (verbose) printf("  node '%c': %d %c %d = %d\n", n->val, a, n->val, b, r);
    return r;
}

void inorder(Node *n) {
    if (!n) return;
    if (!isdigit((unsigned char)n->val)) printf("(");
    inorder(n->l); printf("%c", n->val); inorder(n->r);
    if (!isdigit((unsigned char)n->val)) printf(")");
}
void preorder(Node *n)  { if (n) { printf("%c ", n->val); preorder(n->l); preorder(n->r); } }
void postorder(Node *n) { if (n) { postorder(n->l); postorder(n->r); printf("%c ", n->val); } }

void show(Node *n, int d) {             /* rotated 90 degrees: right subtree on top */
    if (!n) return;
    show(n->r, d + 1);
    printf("%*s%c\n", d * 6, "", n->val);
    show(n->l, d + 1);
}
void freetree(Node *n) { if (n) { freetree(n->l); freetree(n->r); free(n); } }

int main(void) {
    char buf[256];
    FILE *f = fopen("input.txt", "r");
    if (!f || !fgets(buf, sizeof buf, f)) { fprintf(stderr, "Cannot read input.txt\n"); return 1; }
    fclose(f);

    printf("Postfix: %s\n", buf);
    Node *root = build(buf);
    printf("=== Expression Tree ===\n");
    show(root, 0);
    printf("\nInorder   : "); inorder(root);
    printf("\nPreorder  : "); preorder(root);
    printf("\nPostorder : "); postorder(root);
    printf("\n\n=== Tree evaluation trace (postorder) ===\n");
    int r = eval_tree(root, 1);
    printf("Result = %d\n", r);
    printf("Arithmetic operations = %d\n", ops_tree);
    printf("Tree nodes created    = %d (each %zu bytes)\n\n", nodes, sizeof(Node));

    const int N = 2000000;
    volatile int sink = 0;
    clock_t t = clock();
    for (int i = 0; i < N; i++) sink = eval_tree(root, 0);
    printf("Tree eval only       (%d runs): %.4f s\n", N, (double)(clock() - t) / CLOCKS_PER_SEC);

    t = clock();
    for (int i = 0; i < N; i++) { Node *x = build(buf); sink = eval_tree(x, 0); freetree(x); }
    printf("Tree build+eval+free (%d runs): %.4f s\n", N, (double)(clock() - t) / CLOCKS_PER_SEC);

    freetree(root);
    return 0;
}
