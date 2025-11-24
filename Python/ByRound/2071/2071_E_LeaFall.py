# Problem: CF 2071 E - LeaFall
# https://codeforces.com/contest/2071/problem/E

"""
E. LeaFall
Time Complexity: O(n^2) per test case
Space Complexity: O(n) per test case

This problem involves computing the expected number of unordered pairs of distinct vertices that become leaves in a tree after randomly removing nodes based on their probabilities.

Approach:
1. For each node i, compute:
   - p[i]: probability that node i falls (p[i]/q[i])
   - _p[i]: (1/p[i] - 1) mod 998244353
2. Precompute for each node the product of probabilities of neighbors falling and sum of _p values
3. Compute contributions to expected value using linearity of expectation
4. Apply inclusion-exclusion to correct counts for overlapping cases

The algorithm uses dynamic programming and tree traversal techniques.
"""

from sys import stdin

input = lambda: stdin.readline().rstrip()
mod = 998244353


def solve():
    n = int(input())
    p = [0] * n
    _p = [0] * n
    for i in range(n):
        x, y = map(int, input().split())
        p[i] = x * pow(y, -1, mod) % mod  # Compute p[i] = x/y mod 998244353
        _p[i] = (pow(p[i], -1, mod) - 1) % mod  # Compute (1/p[i] - 1) mod 998244353

    l = []
    g = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v = map(int, input().split())
        u -= 1
        v -= 1
        g[u].append(v)
        g[v].append(u)
        l.append((u, v))

    p0 = [0] * n      # Product of probabilities of neighbors falling
    p00 = [0] * n     # Sum of _p values of neighbors
    p1 = [0] * n      # Contribution to expected value for single node

    for i in range(n):
        resp = 1     # Product of p[j] for all neighbors j
        ress = 0     # Sum of _p[j] for all neighbors j
        for j in g[i]:
            resp = (resp * p[j]) % mod   # Multiply by neighbor probability
            ress = (ress + _p[j]) % mod  # Add neighbor _p value
        p0[i] = resp
        p00[i] = ress
        p1[i] = resp * ress * (1 - p[i]) % mod  # Contribution factor for node i

    ans1 = 0   # Sum of p1 values
    ans2 = 0   # Sum of squares of p1 values
    for x in p1:
        ans1 = (ans1 + x) % mod
        ans2 = (ans2 + x**2) % mod

    # Compute initial answer using variance formula
    ans = (ans1**2 - ans2) * pow(2, -1, mod) % mod

    # Subtract edge contributions (remove overcounting)
    for u, v in l:
        ans -= p1[u] * p1[v]
        ans += p0[u] * p0[v] * _p[u] * _p[v]
        ans %= mod

    # Apply corrections using node-wise DP
    for i in range(n):
        ans1 = 0   # Sum of p1[j] for neighbors j of node i
        ans2 = 0   # Sum of squares of p1[j] for neighbors j of node i
        for j in g[i]:
            x = p1[j]
            ans1 = (ans1 + x) % mod
            ans2 = (ans2 + x**2) % mod
        # Remove contribution of subtree rooted at i
        ans = (ans - (ans1**2 - ans2) * pow(2, -1, mod)) % mod

        ans1 = 0   # Sum of p0[j]*(1-p[j]) for neighbors j of node i
        ans2 = 0   # Sum of squares of p0[j]*(1-p[j]) for neighbors j of node i
        for j in g[i]:
            x = p0[j] * (1 - p[j]) % mod   # Contribution of neighbor j
            ans1 = (ans1 + x) % mod
            ans2 = (ans2 + x**2) % mod
        # Add corrected contribution accounting for node i
        ans += (ans1**2 - ans2) * pow(2, -1, mod) * (1 - p[i]) * pow(p[i], -2, mod)
        ans %= mod

        ans1 = 0   # Sum of p0[j]*(p00[j]-_p[i])*(1-p[j]) for neighbors j of node i
        ans2 = 0   # Sum of squares of above values
        for j in g[i]:
            x = p0[j] * (p00[j] - _p[i]) * (1 - p[j]) % mod
            ans1 = (ans1 + x) % mod
            ans2 = (ans2 + x**2) % mod
        # Add final correction for node i
        ans += (ans1**2 - ans2) * pow(2, -1, mod) * pow(p[i], -1, mod)
        ans %= mod

    return ans


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/codeForces/