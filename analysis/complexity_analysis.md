# Complexity Analysis

## 1. Expression Tree

### Construction

The postfix expression is scanned once. Each operand and operator
is processed exactly once.

**Time Complexity: O(n)**

### Evaluation

Every node in the expression tree is visited once.

**Time Complexity: O(n)**

### Space

The expression tree contains O(n) nodes. The construction stack
may also require O(n) space.

**Space Complexity: O(n)**

---

## 2. Stack-Based Postfix Evaluation

Each token is scanned exactly once.

**Time Complexity: O(n)**

The operand stack can contain up to O(n) elements.

**Space Complexity: O(n)**

---

## Overall Complexity

| Method | Time | Space |
|---|---|---|
| Expression Tree | O(n) | O(n) |
| Stack-Based Postfix | O(n) | O(n) |

Where `n` represents the number of tokens in the expression.
