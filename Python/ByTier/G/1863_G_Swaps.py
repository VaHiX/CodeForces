# Problem: CF 1863 G - Swaps
# https://codeforces.com/contest/1863/problem/G

"""
Algorithm/Techniques: 
- Graph decomposition into trees and cycles
- BFS to identify nodes that are not part of cycles
- For each cycle, compute valid permutations using inclusion-exclusion principle
- Modular exponentiation for efficient power calculation
- Time Complexity: O(n)
- Space Complexity: O(n)

This code solves the problem of counting distinct arrays obtainable by swapping elements at positions i and a[i].
It builds a directed graph where each node points to a[i]. Then it separates the graph into:
1. Trees (nodes not part of cycles)
2. Cycles (nodes forming cycles)

For each component, it calculates the number of valid operations:
- For trees, it multiplies by (deg[i] + 1) 
- For cycles, it uses inclusion-exclusion to count valid permutations
"""

import threading


def solve():
    import sys

    data = sys.stdin.buffer.read().split()
    MOD = 10**9 + 7
    it = iter(data)
    n = int(next(it))
    A = [0] * (n + 1)
    ind = [0] * (n + 1)
    deg = [0] * (n + 1)
    for i in range(1, n + 1):
        ai = int(next(it))
        A[i] = ai
        ind[ai] += 1
        deg[ai] += 1
    nc = [False] * (n + 1)
    from collections import deque

    q = deque()
    for i in range(1, n + 1):
        if ind[i] == 0:
            q.append(i)
    while q:
        u = q.popleft()
        nc[u] = True
        v = A[u]
        ind[v] -= 1
        if ind[v] == 0:
            q.append(v)

    def modpow(x, e):
        r = 1
        x %= MOD
        while e:
            if e & 1:
                r = r * x % MOD
            x = x * x % MOD
            e >>= 1
        return r

    res = 1
    for i in range(1, n + 1):
        if nc[i]:
            res = res * (deg[i] + 1) % MOD
    for i in range(1, n + 1):
        if nc[i]:
            continue
        cycle_nodes = []
        x = i
        while not nc[x]:
            nc[x] = True
            cycle_nodes.append(x)
            x = A[x]
        m = len(cycle_nodes)
        if m == 1:
            continue
        b = [deg[node] for node in cycle_nodes]
        mul1 = 1
        for bj in b:
            mul1 = mul1 * (bj + 1) % MOD
        sum_b_minus1 = sum(bj - 1 for bj in b) % MOD
        mul2 = modpow(2, m)
        z = mul1
        z = (z - mul2) % MOD
        z = (z - sum_b_minus1) % MOD
        z = (z + mul2) % MOD
        z = (z - m) % MOD
        res = res * z % MOD
    print(res)


if __name__ == "__main__":
    threading.Thread(target=solve).start()


# https://github.com/VaHiX/CodeForces/