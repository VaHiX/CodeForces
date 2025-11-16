# Problem: CF 1867 D - Cyclic Operations
# https://codeforces.com/contest/1867/problem/D

"""
Algorithm: Cyclic Operations
Purpose: Determine if an array B can be obtained from an initial array of zeros using a specific cyclic operation.

The operation allows choosing a subsequence of length k and updating elements in a cyclic pattern:
a[l_i] = l_((i % k) + 1) where l is the chosen subsequence.

This problem reduces to checking whether the given array B can be constructed through valid cyclic operations.

Approach:
- For k = 1, the array B must match indices 0, 1, ..., n-1 (0-indexed).
- For k > 1, we model the problem using graph traversal:
    - Build a directed graph where each node i points to B[i].
    - Identify all cycles in the graph.
    - Check that the length of each cycle is exactly k.
    - If any cycle has length != k, return "NO".

Time Complexity: O(n)
Space Complexity: O(n)

"""

import sys

input = sys.stdin.readline


def solve():
    n, k = map(int, input().split())
    B = [int(x) - 1 for x in input().split()]  # Convert to 0-indexed

    if k == 1:
        # For k=1, each element must be at its own index
        if all(b == i for i, b in enumerate(B)):
            return "YES"
        else:
            return "NO"

    col = [-1] * n  # -1: unvisited, 0: visiting, 1: visited
    for i in range(n):
        if col[i] != -1:
            continue

        stack = [i]
        beg_cycle = end_cycle = -1
        cycles = []
        while stack:
            u = stack.pop()
            if u >= 0:
                col[u] = 0
                stack.append(~u)  # Push ~u (negative) to mark end of DFS
                v = B[u]
                if col[v] == -1:
                    stack.append(v)
                elif col[v] == 0:
                    # Back edge found, cycle detected
                    cycles.append((v, u))

            else:
                col[~u] = 1  # Mark visiting node as done

        for u, end_cycle in cycles:
            sz = 1
            while u != end_cycle:
                u = B[u]
                sz += 1

            if sz != k:
                return "NO"

    return "YES"


T = int(input())
out = [solve() for _ in range(T)]
print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/