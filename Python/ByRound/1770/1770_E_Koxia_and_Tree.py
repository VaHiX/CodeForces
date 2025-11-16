# Problem: CF 1770 E - Koxia and Tree
# https://codeforces.com/contest/1770/problem/E

"""
Code Purpose:
This code computes the expected distance between two randomly chosen butterflies on a tree,
after a random orientation of edges and butterflies moving according to certain rules.

Algorithms/Techniques:
1. Tree traversal to compute subtree sizes and parent relationships.
2. Dynamic programming on tree to efficiently calculate probabilities of butterfly positions.
3. Modular arithmetic for handling large numbers and modular inverse.

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm processes each edge of the tree once to calculate the expected distance between
two butterflies, and uses dynamic programming to propagate the influence of butterfly placements
and edge orientations.
"""

f = lambda: map(int, input().split())
n, k = f()
B = list(f())
E = [list(f()) for _ in range(n - 1)]
g = [[] for _ in range(n + 1)]
for a, b in E:
    g[a].append(b)
    g[b].append(a)
S = [0] * (n + 1)
I = [0] * (n + 1)
p = [0] * (n + 1)
for e in B:
    p[e] = 1


def F(u, f):
    S[u] += p[u]
    for v in g[u]:
        if v == f:
            continue
        F(v, u)
        S[u] += S[v]
        I[v] = u


F(1, 0)
R = 0
M = 998244353
J = pow(2, M - 2, M)  # Modular inverse of 2
L = pow(2, n, M)     # 2^n mod M

for u, v in E:
    if I[u] != v:  # Ensure u is parent of v
        u, v = v, u
    # Contribution to expected distance from this edge
    R += L * (
        S[u] * (k - S[u])  # Term for butterflies not moving out of u
        + J
        * (
            p[u] * (1 - p[v]) * (2 * S[u] - k - 1)  # Term for u moving to v
            + p[v] * (1 - p[u]) * (k - 2 * S[u] - 1)  # Term for v moving to u
        )
    )
    R %= M
    # Update positions (propagate butterfly counts)
    p[u] = p[v] = ((p[u] + p[v]) * J) % M

# Multiply by inverse of total number of pairs (k choose 2) * 2^n
R *= pow(k * (k - 1) // 2 * L, M - 2, M)
print(R % M)


# https://github.com/VaHiX/CodeForces/