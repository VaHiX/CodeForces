# Problem: CF 1707 D - Partial Virtual Trees
# https://codeforces.com/contest/1707/problem/D

"""
Code Purpose:
This code solves the problem of counting the number of ways to reduce a rooted tree's vertex set to just the root 
( vertex 1 ) by performing exactly k operations, where each operation chooses a partial virtual tree of the current set.

The solution uses dynamic programming with tree decomposition:
1. It computes for each node the contribution of its subtree to the partial virtual tree count
2. It uses generating functions and inclusion-exclusion principle to compute the final result
3. Modular arithmetic and precomputed factorials are used for combinatorial calculations

Algorithms/Techniques:
- Tree decomposition with dynamic programming
- Generating functions
- Inclusion-exclusion principle
- Modular arithmetic and combinatorics
- Lowest Common Ancestor (LCA) concept in tree structure

Time Complexity: O(n^3) 
Space Complexity: O(n^3)
"""

from sys import setrecursionlimit

setrecursionlimit(2000)
n, M = [int(e) for e in input().split()]
R = 2000


def hyp(x):
    # Modular inverse using Fermat's little theorem
    return pow(x, M - 2, M)


# Precompute factorials and their modular inverses
Fact = [1] * (R + 1)
for i in range(2, R + 1):
    Fact[i] = (i * Fact[i - 1]) % M
Facthyp = [1] * (R + 1)
Facthyp[R] = hyp(Fact[R])
for i in range(R - 1, 1, -1):
    Facthyp[i] = ((i + 1) * Facthyp[i + 1]) % M


def C(n, k):
    # Compute binomial coefficient C(n, k) mod M
    if min(n, k, n - k) < 0:
        return 0
    return (Fact[n] * Facthyp[k] * Facthyp[n - k]) % M


# Build adjacency list representation of the tree
a = [set() for i in range(n)]
F = [[0] * n for x in range(n)]
S = [[0] * n for x in range(n)]
for _ in range(n - 1):
    x, y = [int(e) - 1 for e in input().split()]
    a[x].add(y)
    a[y].add(x)


def prp(x):
    # Convert set of neighbors to list and remove parent links to build tree structure
    for y in a[x]:
        a[y].remove(x)
        prp(y)
    a[x] = list(a[x])


prp(0)
# D[x][i][j]: contribution from node x's subtree for choosing j elements from i elements
D = [[[0] * n for i in range(len(a[x]) + 1)] for x in range(n)]
# P[x][i][j]: prefix sum of D[x][i][j] 
P = [[[0] * n for y in a[x]] for x in range(n)]


def f(x):
    # Recursive function to compute F[x][i] 
    for y in a[x]:
        f(y)
    # Compute the contribution from children of x
    for i in range(1, n):
        p = 1
        for I in range(len(a[x]) + 1):
            D[x][I][i] = p
            if I == len(a[x]):
                break
            p = (p * S[a[x][I]][i]) % M
        p = 1
        for I in range(len(a[x]) - 1, -1, -1):
            D[x][I][i] = (D[x][I][i] * p) % M
            p = (p * S[a[x][I]][i]) % M

    # Compute prefix sums P from computed values D
    for I in range(len(a[x])):
        for i in range(1, n):
            P[x][I][i] = (P[x][I][i - 1] + D[x][I][i - 1]) % M

    # Initialize F[x][1] = 1
    F[x][1] = 1
    if not x:
        # For root, F[x][i] = D[x][len(a[x])-1][i] 
        for i in range(2, n):
            F[x][i] = D[x][-1][i]
        return
    # For non-root nodes, use recurrence relation
    for i in range(2, n):
        F[x][i] = D[x][-1][i]
        for I in range(len(a[x])):
            F[x][i] = (F[x][i] + F[a[x][I]][i] * P[x][I][i]) % M
    # Accumulate S[x][i] = S[x][i-1] + F[x][i]
    for i in range(n):
        S[x][i] = ((S[x][i - 1] if i else 0) + F[x][i]) % M


f(0)
# Y[i]: final answer for k=i operations
Y = [0] * n
for i in range(1, n):
    # Apply inclusion-exclusion principle
    Y[i] = (F[0][i] - sum(C(i, j) * Y[j] for j in range(i))) % M
print(*Y[1:])


# https://github.com/VaHiX/CodeForces/